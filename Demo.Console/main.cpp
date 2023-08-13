#include <future>
#include <iostream>

#include "Instrumentor.h"

// chrome://tracing/ => results.json

#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) instrumentation_timer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_FUNCTION()
#endif

void function_1(const int value)
{
	PROFILE_FUNCTION();
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	std::cout << "function_1 finished, value: " << value << std::endl;
}

void function_2()
{
	PROFILE_FUNCTION();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "function_2 finished\n";
}

void function_3()
{
	PROFILE_FUNCTION();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << "function_3 finished\n";
}

void run_benchmarks()
{
	PROFILE_FUNCTION();
	std::cout << "Running Benchmarks...\n";
	std::thread thread1([] {function_1(2); });
	std::thread thread2([] {function_3(); });
	std::thread thread3([] {function_2(); });

	thread1.join();
	thread2.join();
	thread3.join();
}

int main()
{
	instrumentor::get().begin_session("Profile");
	run_benchmarks();
	instrumentor::get().end_session();
}