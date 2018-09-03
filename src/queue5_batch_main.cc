
#include <thread>
#include <iostream>
#include <cxxopts/cxxopts.h>

#include "queue5.h"
#include "queue_performance.h"

const unsigned long DATA_LEN = 32;

template<size_t Len = 32>
struct data_t
{
	unsigned char buf[Len] = { '\0' };
};

struct config {
	unsigned short batch = 5;
	unsigned long  count = 10 * 1000000;
};

void _print_help(cxxopts::Options& opts_, int exit_code_ = 0)
{
	std::ostream& os = (exit_code_ ? std::cerr : std::cout);
	os << opts_.help({""}) << std::endl;
	exit(exit_code_);
}

cxxopts::Options _set_options()
{
	cxxopts::Options opts("queue_performance", " - ");

	opts.add_options()
		("b,batch", "batch size", cxxopts::value<unsigned short>(), "B")
		("c,count", "element count in millions", cxxopts::value<unsigned long>(), "C")
		("h,help", "print this help message");

	return opts;
}

config _parse_config(cxxopts::Options opts_, int argc_, char** argv_)
{
	config config {};
	auto parsed_opts = opts_.parse(argc_, argv_);

	if (parsed_opts.count("b"))
		config.batch = parsed_opts["b"].as<unsigned short>();

	if (parsed_opts.count("c"))
		config.count = parsed_opts["c"].as<unsigned long>();

	if (parsed_opts.count("h"))
		_print_help(opts_);

	return config;
}

int main(int argc_, char** argv_)
{
	namespace qp = queue_performance;
	const auto config = _parse_config(_set_options(), argc_, argv_);

	qp::queue5<data_t<DATA_LEN>> queue;

	auto adjusted_len = config.count - (config.count % config.batch);
	auto data = new data_t<DATA_LEN>[adjusted_len];

	auto producer = [&queue, &config, &data, &adjusted_len]() {
		for (unsigned long i = 0; i < adjusted_len; i += config.batch)
			while(!queue.enqueue(data + i, config.batch));
	};

	auto consumer = [&queue, &config, &adjusted_len]() {
		data_t<DATA_LEN> rx_d;
		queue_performance::signal sig;

		auto start = std::chrono::high_resolution_clock::now();

		for (unsigned long i = 0; i < adjusted_len; i++)
			while(!queue.dequeue(rx_d, sig));

		// count, time, throughput
		std::cout << adjusted_len << ", " << qp::secs_since(start) << ", "
				  << adjusted_len / qp::secs_since(start) / 1000000 << std::endl;
	};

	std::thread producer_thread(producer);
	std::thread consumer_thread(consumer);

	consumer_thread.join();
	producer_thread.join();

	return 0;
}