#include "queue_performance.h"

#include <moodycamel/concurrentqueue.h>
#include <moodycamel/readerwriterqueue.h>

#include <thread>
#include <vector>

int main(int argc_, char** argv_)
{
	namespace qp = queue_performance;
	const auto config = qp::_parse_config(queue_performance::_set_options(), argc_, argv_);
	auto data = new qp::static_data_t<qp::Len>[config.count];

	moodycamel::ReaderWriterQueue<qp::static_data_t<qp::Len>> queue {};

	auto producer = [&queue, &config, &data]() {
		for (unsigned long i = 0; i < config.count; i++)
			queue.enqueue(data[i]);
	};

	auto consumer = [&queue, &config]() {
		qp::static_data_t<qp::Len> rx_d;
		auto start = std::chrono::high_resolution_clock::now();

		for (unsigned long i = 0; i < config.count; i++)
			while (!queue.try_dequeue(rx_d)) { }

		std::cout << qp::output_line("mc", qp::Len, qp::secs_since(start), config.count);
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();

	return 0;
}
