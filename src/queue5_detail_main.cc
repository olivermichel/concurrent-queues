
#include "queue_performance.h"
#include "queue5.h"

#include <thread>
#include <vector>
#include <fstream>

int main(int argc_, char** argv_)
{
	namespace qp = queue_performance;
	const auto config = qp::_parse_config(queue_performance::_set_options(), argc_, argv_);

	std::vector<qp::data_t> data(config.count, qp::data_t(config.bytes));

	qp::queue5<qp::data_t> queue;

	std::vector<unsigned long> sizes { };

	auto producer = [&queue, &config, &data, &sizes]() {

		for (unsigned long i = 0; i < config.count; i++) {
			while(!queue.enqueue(std::move(data[i])));
			sizes.push_back(queue.size());
		}
	};

	auto consumer = [&queue, &config]() {
		qp::data_t rx_d;
		queue_performance::signal sig;

		auto start = std::chrono::high_resolution_clock::now();

		for (unsigned long i = 0; i < config.count; i++)
			while(!queue.dequeue(rx_d, sig));
//
//		// count, time, throughput
//		std::cout << config.count << ", " << qp::secs_since(start) << ", "
//				  << config.count / qp::secs_since(start) / 1000000 << std::endl;
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();

	std::fstream fs("out/queue5_detail.csv", std::ios::out);

	for (auto i : sizes)
		fs << i << std::endl;

	fs.close();
	
	return 0;
}
