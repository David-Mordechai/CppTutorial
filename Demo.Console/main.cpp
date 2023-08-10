#include <chrono>
#include <iostream>
#include <thread>

struct timer
{
private:
	std::string name_;
public:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	explicit timer(std::string name) : name_(std::move(name)), duration(0.0f)
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		const float ms = duration.count() * 1000.0f;
		std::cout << name_ << " - timer took: " << ms << "ms" << std::endl;
	}
};

int main()
{
	constexpr int dimension_size = 10000;

	std::cout << "two dimensional array " << dimension_size << " x " << dimension_size << std::endl;
	std::cout << "##################################################\n";
	// scope 1
	{
		timer timer("two dimensional array");
		const auto a2d = new int* [dimension_size];

		for (int i = 0; i < dimension_size; i++)
			a2d[i] = new int[dimension_size];
	
		for (int y = 0; y < dimension_size; y++)
			for (int x = 0; x < dimension_size; x++)
				a2d[x][y] = 2;
	
		for (int i = 0; i < dimension_size; i++)
			delete[] a2d[i];
		delete[] a2d;
		
	}

	// scope 1.1 better Meir version
	{
		timer timer("better Meir version");
		const auto a2d = new int* [dimension_size];

		for (int i = 0; i < dimension_size; i++)
			a2d[i] = new int[dimension_size];

		for (int x = 0; x < dimension_size; x++)
		{
			auto x_pointer = a2d[x];
			for (int y = 0; y < dimension_size; y++, x_pointer++)
				*x_pointer = 2;
		}

		for (int i = 0; i < dimension_size; i++)
			delete[] a2d[i];
		delete[] a2d;
	}

	std::cout << "\n";
	std::cout << "one dimensional array " << dimension_size << " * " << dimension_size << std::endl;
	std::cout << "##################################################\n";
	// scope 2
	{
		timer timer("one dimensional array");
		constexpr int array_size = dimension_size * dimension_size;
		const auto arr = new int[array_size];

		for (int y = 0; y < dimension_size; y++)
			for (int x = 0; x < dimension_size; x++)
				arr[x + y * dimension_size] = 2;
		
		delete[] arr;
		
	}

	// scope 2.1 better Meir version
	{
		timer timer("better Meir version");
		constexpr int array_size = dimension_size * dimension_size;
		auto arr = new int[array_size];

		auto arr_pointer = arr;
		for (int x = 0; x < array_size; x++, arr_pointer++)
			*arr_pointer = 2;

		delete[] arr;
	}
}
