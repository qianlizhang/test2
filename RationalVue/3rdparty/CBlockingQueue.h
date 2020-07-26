#pragma once

//****************************************************************
//	name		:	CBlockingQueue
//	brief		:	ͬ�����У������������������߲���ͬʱ��д������
//	author		:	XF_Shaw
//	version		:	1.0.2015
//****************************************************************

#include "CAtomicInteger.h"
#include <QWaitCondition>


/**
 *@brief	��������ڵ�
 */
template<typename T>
struct Node {
	T item;
	Node *next;
};


/**
 *@brief	ͬ������
 */
template<typename T>
class CBlockingQueue {
private:
	//��������
	const int m_nCapacity;

	//����Ԫ������
	//CAtomicInteger *m_pCount;

	//����ͷβ�ڵ�
	::Node<T> *m_pHead;
	::Node<T> *m_pLast;

	QMutex m_iPutLock;
	QMutex m_iTakeLock;

	QWaitCondition m_iNotFull;
	QWaitCondition m_iNotEmpty;

public:
	//����Ԫ������
	CAtomicInteger *m_pCount;
	/**
	 *@brief		���캯��
	 *
	 *@param[in] cap	����������ȱʡΪ50, jai���ͼƬ���������Լ60����
	 */
	CBlockingQueue(int cap = 64);

	/**
	 * @brief		�����
	 *
	 * @param[in] v		���Ԫ��
	 */
	void Put(T &v);

	/**
	 * @brief		������
	 *
	 * @return		���ض�βԪ��
	 */
	T Take();

	/**
	 * @brief		�ı���д�С��Ŀǰֻʵ���˶��е�����
	 *				���д�С�ļ�С����Ҫ������Ǩ�ƣ���Ҫ�õ�ʱ����ʵ��
	 * @param		���д�С
	*/
	bool Resize(int cap);

private:
	void __Enqueue(::Node<T> *node);
	T __Dequeue();
	void __SignalNotEmpty();
	void __SignalNotFull();
};



/*******************************
**********CBlockingQueue*********
********************************/
template<typename T>
CBlockingQueue<T>::CBlockingQueue(int cap) : m_nCapacity(cap)
{
	m_pCount = new CAtomicInteger;
	m_pHead = new ::Node<T>;
	//	m_pHead->item = 0;
	m_pHead->next = nullptr;
	m_pLast = m_pHead;
}


template<typename T>
void CBlockingQueue<T>::__Enqueue(::Node<T> *node) {
	m_pLast->next = node;
	m_pLast = node;
}


template<typename T>
T CBlockingQueue<T>::__Dequeue()
{
	::Node<T> *pH = m_pHead;
	::Node<T> *pFirst = pH->next;
	pH->next = pH;
	m_pHead = pFirst;
	delete pH;
	//	T x = first->item.clone();
	T x = pFirst->item;
	//    first->item = 0;
	return x;
}


template<typename T>
void CBlockingQueue<T>::__SignalNotEmpty()
{
	this->m_iTakeLock.lock();
	this->m_iNotEmpty.wakeOne();
	this->m_iTakeLock.unlock();
}


template<typename T>
void CBlockingQueue<T>::__SignalNotFull()
{
	this->m_iPutLock.lock();
	this->m_iNotFull.wakeOne();
	this->m_iPutLock.unlock();
}


template<typename T>
void CBlockingQueue<T>::Put(T &v)
{
	/*
	if(v == NULL)
		return;
	*/
	int c = -1;
	::Node<T> *pNode = new ::Node<T>;
	//node->item = v;
	// ��֪����opencv��Mat���������ﱻ�����ˣ�����ʹ�������=ʱ�����ֻ�е���clone�����������ƻ��˷�װ�����ͨ����
	// �˴����뻺��������Ϊԭֵ�Ŀ������Է������������ݱ�����������
	pNode->item = v.clone();
	m_iPutLock.lock();
	try {
		while (m_pCount->getValue() == m_nCapacity)
		{
			m_iNotFull.wait(&m_iPutLock);
		}
		__Enqueue(pNode);
		c = m_pCount->getAndIncrement();
		//qDebug() <<"Size: "<< c << endl;
		if (c < m_nCapacity)
			m_iNotFull.wakeAll();
	}
	catch (...) {
		m_iPutLock.unlock();
	}
	m_iPutLock.unlock();

	if (c == 1)
		__SignalNotEmpty();
}


template<typename T>
T CBlockingQueue<T>::Take()
{
	T x;
	int c = -1;
	m_iTakeLock.lock();
	try {
		while (m_pCount->getValue() == 0) {
			m_iNotEmpty.wait(&m_iTakeLock);
		}
		x = __Dequeue();
		c = m_pCount->getAndDecrement();
		if (c > 0)
			m_iNotEmpty.wakeAll();
	}
	catch (...) {
		m_iTakeLock.unlock();
	}

	m_iTakeLock.unlock();

	if (c == m_nCapacity - 1)
		__SignalNotFull();
	return x;
}


template<typename T>
bool CBlockingQueue<T>::Resize(int cap)
{
	m_nCapacity = cap;
	return true;
}