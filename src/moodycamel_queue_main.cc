#include "queue_performance.h"

#include <moodycamel/concurrentqueue.h>

#include <thread>
#include <vector>

int main(int argc_, char** argv_)
{
	namespace qp = queue_performance;
	const auto config = qp::_parse_config(queue_performance::_set_options(), argc_, argv_);

	std::vector<qp::data_t> data(config.count, qp::data_t(config.bytes));

	moodycamel::ConcurrentQueue<qp::data_t> queue;

	auto producer = [&queue, &config, &data]() {

		unsigned long i = 0;

		while (i < config.count)

			if (config.zero_copy)
				i = queue.try_enqueue(std::move(data[i])) ? i + 1 : i;
			else
				i = queue.try_enqueue(data[i]) ? i + 1 : i;
	};

	auto consumer = [&queue, &config]() {

		unsigned long i = 0;
		qp::data_t rx_d;

		auto start = std::chrono::high_resolution_clock::now();

		while (i < config.count)
			i = queue.try_dequeue(rx_d) ? i + 1 : i;

		std::cout << config.count / qp::secs_since(start) / 1000000 << std::endl;
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();

	return 0;
}
