//
// jetstream network analytics
// (c) Oliver Michel 2018
//

#ifndef JETSTREAM_QUEUE_PERFORMANCE_QUEUE4_H
#define JETSTREAM_QUEUE_PERFORMANCE_QUEUE4_H

#include <atomic>
#include "queue_performance.h"

namespace queue_performance {

	template <typename T>
	class queue4 : public _wait_free_queue<T>
	{
	public:

		explicit queue4(unsigned long capacity_ = 524288)
			: _buf(new typename _wait_free_queue<T>::_element[capacity_]),
			  _head(0),
			  _tail(0),
			  _capacity(capacity_) { }

		bool enqueue(const T& item_, signal signal_ = signal::proceed)
		{
			auto curr_tail = _tail.load(_mod_load_mem_order);
			auto next_tail = _increment(curr_tail);

			if (next_tail != _head.load(_lku_load_mem_order)) {
				_buf[curr_tail]._item = item_;
				_buf[curr_tail]._signal = signal_;
				_tail.store(next_tail, _store_mem_order);
				return true;
			}

			return false;
		}

		bool enqueue(T&& item_, signal signal_ = signal::proceed)
		{
			auto curr_tail = _tail.load(_mod_load_mem_order);
			auto next_tail = _increment(curr_tail);

			if (next_tail != _head.load(_lku_load_mem_order)) {
				_buf[curr_tail]._item = std::move(item_);
				_buf[curr_tail]._signal = signal_;
				_tail.store(next_tail, _store_mem_order);
				return true;
			}

			return false;
		}

		void enqueue_wait(const T& item_, signal signal_ = signal::proceed)
		{
			while (!enqueue(item_, signal_)) { }
		}

		void enqueue_wait(T&& item_, signal signal_ = signal::proceed)
		{
			while(!enqueue(std::move(item_), signal_)) { }
		}

		void send(signal signal_)
		{
			while (!enqueue(T(), signal_)) { }
		}

		bool dequeue(T& item_, signal& signal_)
		{
			const auto curr_head = _head.load(_mod_load_mem_order);

			if (curr_head == _tail.load(_lku_load_mem_order))
				return false;

			item_ = std::move(_buf[curr_head]._item);
			signal_ = _buf[curr_head]._signal;
			_head.store(_increment(curr_head), _store_mem_order);
			return true;
		}

		void dequeue_wait(T& item_, signal& signal_)
		{
			while (!dequeue(item_, signal_)) { }
		}

		bool empty() const
		{
			return (_head.load(_mod_load_mem_order) == _tail.load(_mod_load_mem_order));
		}

		virtual ~queue4()
		{
			delete[] _buf;
		}

	private:

		inline unsigned long _increment(unsigned long i_) const
		{
			return (i_ + 1) % _capacity;
		}

		typename _wait_free_queue<T>::_element* _buf;
		std::atomic<unsigned long> _head;
		std::atomic<unsigned long> _tail;
		unsigned long _capacity;

		/*
		const std::memory_order _mod_load_mem_order = std::memory_order::memory_order_relaxed;
		const std::memory_order _lku_load_mem_order = std::memory_order::memory_order_acquire;
		const std::memory_order _store_mem_order    = std::memory_order::memory_order_release;
		*/

		const std::memory_order _mod_load_mem_order = std::memory_order::memory_order_seq_cst;
		const std::memory_order _lku_load_mem_order = std::memory_order::memory_order_seq_cst;
		const std::memory_order _store_mem_order    = std::memory_order::memory_order_seq_cst;
	};
}

#endif
