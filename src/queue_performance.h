//
// jetstream network analytics
// (c) Oliver Michel 2018
//

#ifndef JETSTREAM_QUEUE_PERFORMANCE_H
#define JETSTREAM_QUEUE_PERFORMANCE_H

#include <chrono>
#include <cstdint>
#include <cxxopts/cxxopts.h>

namespace queue_performance {

	enum class signal : unsigned char
	{
		proceed = 1,
		stop = 0
	};

	template <typename T>
	class _queue
	{
	public:
		virtual bool empty() const = 0;
	protected:
		struct _element
		{
			_element() : _signal(), _item() {}
			signal _signal;
			T _item;
		};
	};

	template <typename T>
	class _wait_free_queue : public _queue<T>
	{
	public:
		virtual bool enqueue(const T& item_, signal signal_ = signal::proceed) = 0;
		virtual bool dequeue(T& item_, signal& signal_) = 0;
	};

	struct config {
		unsigned short bytes = 8;
		unsigned long  count = 10 * 1000000;
		bool wait_free = false;
		bool zero_copy = false;
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
			("b,bytes", "bytes per element", cxxopts::value<unsigned short>(), "B")
			("c,count", "element count in millions", cxxopts::value<unsigned long>(), "C")
			("w,wait-free", "use wait-free queue access")
			("z,zero-copy", "use zero-copy enqueueing")
			("h,help", "print this help message");

		return opts;
	}

	config _parse_config(cxxopts::Options opts_, int argc_, char** argv_)
	{
		config config {};
		auto parsed_opts = opts_.parse(argc_, argv_);

		if (parsed_opts.count("b"))
			config.bytes = parsed_opts["b"].as<unsigned short>();

		if (parsed_opts.count("c"))
			config.count = parsed_opts["c"].as<unsigned long>();

		if (parsed_opts.count("w"))
			config.wait_free = true;

		if (parsed_opts.count("z"))
			config.zero_copy = true;

		if (parsed_opts.count("h"))
			_print_help(opts_);

		return config;
	}

//	using data_t = unsigned long;

	template <unsigned L>
	class data_t {
	public:
		explicit data_t()
			: _data{}
		{
			std::fill(_data, _data + L, '\0');
		}

//		data_t(const data_t& copy_from_)
//			: /* _l(copy_from_._l), */_data(/*new unsigned char[copy_from_._l]*/)
//		{
//			std::cout << "copy construct" << std::endl;
//			std::memcpy(_data, copy_from_._data, L);
//		}
//
//		data_t& operator=(const data_t& copy_from_)
//		{
////			_l = copy_from_._l;
////			_data = new unsigned char[copy_from_._l];
//			std::memcpy(_data, copy_from_._data, L);
//			return *this;
//		}

//		data_t(data_t&& move_from_) noexcept
//			: _data(move_from_._data)
//		{
////			move_from_._data = nullptr;
//		}

//		data_t& operator=(data_t&& move_from_) noexcept
//		{
////			_l = move_from_._l;
//			_data = move_from_._data;
//			move_from_._data = nullptr;
//			return *this;
//		}

//		virtual ~data_t()
//		{
//			delete[] _data;
//		}

	private:
//		unsigned short _l;

		unsigned char _data[L];

//		unsigned char* _data;
	};

	double secs_since(std::chrono::time_point<std::chrono::high_resolution_clock>& start_)
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);
		double time_s = (double) dur.count() / 1000000;
		return time_s;
	}
}

#endif
