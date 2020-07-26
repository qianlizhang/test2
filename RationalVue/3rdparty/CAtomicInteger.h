#pragma once
#include <qmutex.h>

//==============================================================================
//	@name		:	AtomicInteger
//	@biref		:	多线程下保持int变量的原子操作，此处用来计量和操作队列中成员的数目
//	@author		:	XF_Shaw
//	@version	:	1.0.2015
//===============================================================================

class CAtomicInteger {
public:
	inline CAtomicInteger()
	{
		QMutexLocker locker(&m_iMutex);
		m_nValue = 0;
	}


	inline CAtomicInteger(int n)
	{
		QMutexLocker locker(&m_iMutex);
		m_nValue = n;
	}


	inline int getAndIncrement()
	{
		QMutexLocker locker(&m_iMutex);
		m_nValue++;
		return m_nValue;
	}


	inline int getAndDecrement()
	{
		QMutexLocker locker(&m_iMutex);
		m_nValue--;
		return m_nValue;
	}


	inline int getValue() const
	{
		QMutexLocker locker(&m_iMutex);
		return m_nValue;
	}

private:
	volatile int m_nValue;
	mutable QMutex m_iMutex;
};
