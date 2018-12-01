#include "queue_performance.h"
#include "queue4.h"

#include <thread>
#include <vector>

int main(int argc_, char** argv_)
{
	namespace qp = queue_performance;
	const auto config = qp::_parse_config(queue_performance::_set_options(), argc_, argv_);

	std::vector<qp::data_t> data(config.count, qp::data_t(config.bytes));

	qp::queue4<qp::data_t> queue;

	auto producer = [&queue, &config, &data]() {
		for (unsigned long i = 0; i < config.count; i++)
			while(!queue.enqueue(config.zero_copy ? std::move(data[i]) : data[i]));
	};

	auto consumer = [&queue, &config]() {
		qp::data_t rx_d;
		queue_performance::signal sig;

		auto start = std::chrono::high_resolution_clock::now();

		for (unsigned long i = 0; i < config.count; i++)
			while(!queue.dequeue(rx_d, sig));

		// count, time, throughput
		std::cout << "q4, " << config.bytes << ", " << config.count << ", "
				  << qp::secs_since(start) << ", " << config.count / qp::secs_since(start) / 1000000
				  << std::endl;
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();

	return 0;
}
