
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

//	std::vector<unsigned long> sizes { };
	unsigned long enqueue_wait = 0, dequeue_wait = 0;
	unsigned long enqueue_count = 0, dequeue_count = 0;
	unsigned long max_enqueue_size = 0, max_dequeue_size = 0;


	auto producer = [&queue, &config, &data, &enqueue_wait, &enqueue_count, &max_enqueue_size]() {

		for (unsigned long i = 0; i < config.count; i++) {
			while(!queue.enqueue(std::move(data[i]))) {
				enqueue_wait++;
			}
			max_enqueue_size = queue.size() > max_enqueue_size ? queue.size() : max_enqueue_size;
			enqueue_count++;
		}
	};

	auto consumer = [&queue, &config, &dequeue_wait, &dequeue_count, &enqueue_count, &enqueue_wait,
				  &max_enqueue_size, &max_dequeue_size]() {
		qp::data_t rx_d;
		queue_performance::signal sig;

		auto start = std::chrono::high_resolution_clock::now();

		for (unsigned long i = 0; i < config.count; i++) {
			while(!queue.dequeue(rx_d, sig)) {
				dequeue_wait++;
			}
			max_dequeue_size = queue.size() > max_dequeue_size ? queue.size() : max_dequeue_size;
			dequeue_count++;
		}

		auto time_s = qp::secs_since(start);
		std::cout << config.count << ", " << enqueue_count << ", " << dequeue_count << ", "
			<< (double) enqueue_wait / (double) enqueue_count << ", "
			<< (double) dequeue_wait / (double) dequeue_count << ", "
			<< max_enqueue_size << ", " << max_dequeue_size << ", " << time_s << ", "
			<< dequeue_count / time_s / 1000000 << std::endl;
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();
/*
	std::fstream fs("data/queue5_detail.csv", std::ios::data);

	for (auto i : sizes)
		fs << i << std::endl;

	fs.close();
*/
	return 0;
}
