﻿#pragma once

template<typename TElem, int QSize>
class SPSCQueue
{
public:
	SPSCQueue():m_HeadPos( 0 ), m_TailPos( 0 ) {}
	~SPSCQueue() {}

	/// 성공시 true, 꽉찼을 경우 false
	bool PushBack( const TElem& item );

	/// 성공시 true, 비어있을 경우 false
	bool PopFront( TElem& item );

private:

	std::atomic<int>	m_HeadPos; ///< for pop_front
	std::atomic<int>	m_TailPos; ///< for push_back

	TElem mQueueArray[QSize + 1];

};

template<typename TElem, int QSize>
bool SPSCQueue<TElem, QSize>::PushBack( const TElem& item )
{
	/// 큐의 뒤에다 삽입
	// memory_order_relaxed : 메모리 배치에 관여하지 않음
	// atomic.load() : 원자적으로 값을 검색
	int currTailPos = m_TailPos.load( std::memory_order_relaxed );

	/// 큐의 마지막 원소는 full/empty여부를 가리기 위한 빈 공간으로 해놓기 때문에 QSize+1한다
	int nextTailPos = ( currTailPos + 1 ) % ( QSize + 1 );

	// memory_order_acquire : 메모리 오더링
	if ( nextTailPos == m_HeadPos.load( std::memory_order_acquire ) )
	{
		/// tail+1 == head인 경우이므로 큐 꽉찼다
		return false;
	}

	// 원자적으로 값을 저장
	mQueueArray[currTailPos] = item;
	m_TailPos.store( nextTailPos, std::memory_order_release );

	return true;
}

template<typename TElem, int QSize>
bool SPSCQueue<TElem, QSize>::PopFront( TElem& item )
{
	int currHeadPos = m_HeadPos.load( std::memory_order_relaxed );

	if ( currHeadPos == m_TailPos.load( std::memory_order_acquire ) )
	{
		/// head == tail인 경우이므로 큐에 내용이 없다 
		return false;
	}

	item = mQueueArray[currHeadPos];

	///  push에서와 같은 이유로..  QSize+1 해주는거임
	int nextHeadPos = ( currHeadPos + 1 ) % ( QSize + 1 );

	m_HeadPos.store( nextHeadPos, std::memory_order_release );

	return true;
}
