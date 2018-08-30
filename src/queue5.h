
#ifndef CONCURRENT_QUEUES_QUEUE5_H
#define CONCURRENT_QUEUES_QUEUE5_H

#include "queue_performance.h"

#include <atomic>
#include <stdexcept>

namespace queue_performance {
	template <typename T>
	class queue5 : public _wait_free_queue<T>
	{
		using index_t = unsigned long;
	public:

		explicit queue5(index_t capacity_ = 524288)
			: _capacity(_power2_check(capacity_)),
			  _buf(new typename _wait_free_queue<T>::_element[capacity_]),
			  _head(0),
			  _tail(0) { }

		bool enqueue(const T& e_, signal signal_ = signal::proceed)
		{
			if (full()) return false;
			const auto t = _tail.load(_mod_load_order);
			_buf[_mask(t)]._item = e_;
			_buf[_mask(t)]._signal = signal_;
			_tail.store(t + 1, _store_order);
			return true;
		}

		bool enqueue(T&& e_, signal signal_ = signal::proceed)
		{
			if (full()) return false;
			const auto t = _tail.load(_mod_load_order);
			_buf[_mask(t)]._item = std::move(e_);
			_buf[_mask(t)]._signal = signal_;
			_tail.store(t + 1, _store_order);
			return true;
		}

		bool dequeue(T& e_, signal& signal_)
		{
			if (empty()) return false;
			const auto h = _head.load(_mod_load_order);
			e_ = std::move(_buf[_mask(h)]._item);
			signal_ = _buf[_mask(h)]._signal;
			_head.store(h + 1, _store_order);
			return true;
		}

		inline bool full() const
		{
			return (_tail.load(_mod_load_order) - _head.load(_mod_load_order)) == _capacity;
		}

		inline bool empty() const
		{
			return _head.load(_mod_load_order) == _tail.load(_mod_load_order);
		}

		inline index_t size() const
		{
			return _tail.load(_mod_load_order) - _head.load(_mod_load_order);
		}

		~queue5()
		{
			delete[] _buf;
		}

	private:

		index_t  _capacity;
		typename _wait_free_queue<T>::_element* _buf;
		std::atomic<index_t> _head, _tail;

		// equivalent to i_ % _capacity
		inline index_t _mask(const index_t i_) const
		{
			return i_ & _capacity - 1;
		}

		index_t _power2_check(index_t x_)
		{
			if (x_ && !(x_ & (x_-1)))
				return x_;
			throw std::invalid_argument("must be power of 2");
		}

//		const std::memory_order _mod_load_order = std::memory_order::memory_order_seq_cst;
//	const std::memory_order _lku_load_order = std::memory_order::memory_order_seq_cst;
//		const std::memory_order _store_order    = std::memory_order::memory_order_seq_cst;

	const std::memory_order _mod_load_order = std::memory_order::memory_order_relaxed;
//	const std::memory_order _lku_load_order = std::memory_order::memory_order_acquire;
	const std::memory_order _store_order    = std::memory_order::memory_order_release;

	};
}

#endif
