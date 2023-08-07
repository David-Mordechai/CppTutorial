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
		std::cout << "two dimensional array " << dimension_size << " x " << dimension_size << std::endl;
	}

	// scope 2
	{
		timer timer("one dimensional array");
		int array_size = dimension_size * dimension_size;
		int* arr = new int[array_size];

		for (int y = 0; y < dimension_size; y++)
			for (int x = 0; x < dimension_size; x++)
				arr[x + y * dimension_size] = 2;
		
		delete[] arr;
		std::cout << "one dimensional array " << dimension_size << " * " << dimension_size << std::endl;
	}
}
