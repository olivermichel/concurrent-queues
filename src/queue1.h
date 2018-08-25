//
// jetstream network analytics
// (c) Oliver Michel 2018
//

#ifndef JETSTREAM_QUEUE_PERFORMANCE_QUEUE1_H
#define JETSTREAM_QUEUE_PERFORMANCE_QUEUE1_H

#include "queue_performance.h"

#include <queue>
#include <mutex>
#include <condition_variable>

namespace queue_performance {

	template <typename T>
	class queue1 : public _wait_free_queue<T>
	{
	public:

		bool enqueue(const T& item_, signal signal_ = signal::proceed)
		{
			std::unique_lock<std::mutex> lock(_mutex);

			typename _wait_free_queue<T>::_element e;
			e._signal = signal_;
			e._item   = item_;
			_queue.push(e);

			lock.unlock();
			_cond.notify_one();
			return true;
		}

		bool dequeue(T& item_, signal& signal_)
		{
			std::unique_lock<std::mutex> lock(_mutex);

			while (_queue.empty())
				_cond.wait(lock);

			auto e = _queue.front();
			item_  = e._item;
			signal_ = e._signal;
			_queue.pop();
			return true;
		}

		bool empty() const
		{
			return _queue.empty();
		}

	private:
		std::queue<typename _wait_free_queue<T>::_element> _queue;
		std::mutex                                    _mutex;
		std::condition_variable                       _cond;
	};
}

#endif
