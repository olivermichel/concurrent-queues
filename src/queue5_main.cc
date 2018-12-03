
#include "queue_performance.h"
#include "queue5.h"

#include <thread>
#include <vector>

int main(int argc_, char** argv_)
{
	namespace qp = queue_performance;
	const auto config = qp::_parse_config(queue_performance::_set_options(), argc_, argv_);

	std::vector<qp::static_data_t<qp::Len>> data(config.count, qp::static_data_t<qp::Len>());
	qp::queue5<qp::static_data_t<qp::Len>> queue;

	auto producer = [&queue, &config, &data]() {
		for (unsigned long i = 0; i < config.count; i++)
			while(!queue.enqueue(data[i]));
	};

	auto consumer = [&queue, &config]() {
		qp::static_data_t<qp::Len> rx_d;
		queue_performance::signal sig;

		auto start = std::chrono::high_resolution_clock::now();

		for (unsigned long i = 0; i < config.count; i++)
			while(!queue.dequeue(rx_d, sig)) { }

		// count, time, throughput
		std::cout << "q5, " << config.count << ", "
				  << qp::secs_since(start) << ", " << config.count / qp::secs_since(start) / 1000000
				  << std::endl;
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();

	return 0;
}
