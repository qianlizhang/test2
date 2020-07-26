#pragma once

//****************************************************************
//	name		:	CBlockingQueue
//	brief		:	同步队列，解决多个生产者消费者不能同时读写的问题
//	author		:	XF_Shaw
//	version		:	1.0.2015
//****************************************************************

#include "CAtomicInteger.h"
#include <QWaitCondition>


/**
 *@brief	队列链表节点
 */
template<typename T>
struct Node {
	T item;
	Node *next;
};


/**
 *@brief	同步队列
 */
template<typename T>
class CBlockingQueue {
private:
	//队列容量
	const int m_nCapacity;

	//队列元素数量
	//CAtomicInteger *m_pCount;

	//队列头尾节点
	::Node<T> *m_pHead;
	::Node<T> *m_pLast;

	QMutex m_iPutLock;
	QMutex m_iTakeLock;

	QWaitCondition m_iNotFull;
	QWaitCondition m_iNotEmpty;

public:
	//队列元素数量
	CAtomicInteger *m_pCount;
	/**
	 *@brief		构造函数
	 *
	 *@param[in] cap	队列容量，缺省为50, jai相机图片缓冲区最大约60左右
	 */
	CBlockingQueue(int cap = 64);

	/**
	 * @brief		入队列
	 *
	 * @param[in] v		入队元素
	 */
	void Put(T &v);

	/**
	 * @brief		出队列
	 *
	 * @return		返回队尾元素
	 */
	T Take();

	/**
	 * @brief		改变队列大小，目前只实现了队列的扩充
	 *				队列大小的减小，需要做数据迁移，需要用的时候再实现
	 * @param		队列大小
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
	// 不知对于opencv的Mat类型在哪里被销毁了，导致使用运算符=时会出错，只有调用clone函数。无奈破坏了封装此类的通用性
	// 此处放入缓冲区的需为原值的拷贝，以防缓冲区中数据被无意中销毁
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