//
// jetstream network analytics
// (c) Oliver Michel 2018
//

#ifndef JETSTREAM_QUEUE_PERFORMANCE_QUEUE3_H
#define JETSTREAM_QUEUE_PERFORMANCE_QUEUE3_H

#include <atomic>

namespace queue_performance {

	template<typename T>
	class queue3
	{
	public:
		queue3() : _head(new node), _tail(_head.load()) { }

	private:

		struct node
		{
			std::shared_ptr<T> data;
			node* next;
			node() : data(nullptr), next(nullptr) { }
		};

		std::atomic<node*> _head;
		std::atomic<node*> _tail;

		node* pop_head()
		{
			node* const old_head = _head.load();

			if (old_head == _tail.load())
				return nullptr;

			_head.store(old_head->next);
			return old_head;
		}

	public:
		void enqueue(T&& new_value)
		{
			std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
			auto p = new node;
			node* const old_tail = _tail.load();
			old_tail->data.swap(new_data);
			old_tail->next = p;
			_tail.store(p);
		}

		std::shared_ptr<T> dequeue()
		{
			node* old_head = pop_head();

			if (!old_head)
				return std::shared_ptr<T>();

			std::shared_ptr<T> const res(old_head->data);
			delete old_head;
			return res;
		}
	};
}
#endif
