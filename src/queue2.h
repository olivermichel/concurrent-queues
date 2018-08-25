//
// jetstream network analytics
// (c) Oliver Michel 2018
//

#ifndef JETSTREAM_QUEUE_PERFORMANCE_QUEUE2_H
#define JETSTREAM_QUEUE_PERFORMANCE_QUEUE2_H

#include "queue_performance.h"

#include <mutex>
#include <condition_variable>

namespace queue_performance {

	template<typename T>
	class queue2 : public _wait_free_queue<T>
	{
	public:
		explicit queue2(unsigned initial_capacity_ = 32)
			: _buf(new typename _wait_free_queue<T>::_element[initial_capacity_]),
			  _capacity(initial_capacity_),
			  _mutex(),
			  _cond()
		{ }

		bool enqueue(const T& item_, signal signal_ = signal::proceed)
		{
			if (_size == _capacity)
				_resize(_capacity * 2);

			std::unique_lock<std::mutex> lock(_mutex);

			_buf[_back]._signal = signal_;
			_buf[_back]._item   = item_;
			_size++;

			lock.unlock();
			_cond.notify_one();

			return true;
		}

		bool dequeue(T& item_, signal& signal_)
		{
			std::unique_lock<std::mutex> lock(_mutex);

			if (this->empty())
				return false;

			signal_ = _buf[_front]._signal;
			item_   = _buf[_front]._item;
			_front = (_front == _capacity - 1) ? 0 : _front + 1;
			_size -= 1;
			lock.unlock();

			return true;
		}

		inline bool empty() const
		{
			return _size == 0;
		}

	private:
		void _resize(unsigned new_capacity_)
		{
			auto new_buf = new typename _wait_free_queue<T>::_element[new_capacity_];

			for (auto i = 0; i < _capacity; i++)
				new_buf[i] = _buf[i];

			_back = _capacity;
			_capacity = new_capacity_;
			delete[] _buf;
			_buf = new_buf;
		}

		typename _wait_free_queue<T>::_element* _buf;
		unsigned  _capacity;

		unsigned _size  = 0;
		unsigned _front = 0;
		unsigned _back  = 0;

		std::mutex _mutex;
		std::condition_variable _cond;
	};
}

#endif
