#include <iostream>

template<typename T, size_t S>
class stack_array
{
public:
	constexpr size_t size() { return S; }

	T& operator[](size_t index) { return data_[index]; }
	const T& operator[](size_t index) const { return data_[index]; }

	T* data() { return data_; }
	[[nodiscard]] const T* data() const { return data_; }

private:
	T data_[S];
};

// writing custom vector class - dynamic array
template<typename T>
class my_vector
{
public:
	my_vector()
	{
		// allocate memory for 2 elements
		re_alloc(2);
	}

	void push_back(const T& value)
	{
		if(size_ >= capacity_)
		{
			// increase capacity by half
			re_alloc(capacity_ + capacity_ / 2);
		}

		data_[size_] = value;
		size_++;
	}

	T& operator[](size_t index) const
	{
		return data_[index];
	}

	T& operator[](size_t index)
	{
		return data_[index];
	}

	[[nodiscard]] size_t size() const { return size_; }
private:
	void re_alloc(const size_t new_capacity)
	{
		// 1. allocate a new block of memory
		// 2. copy/move old elements into a new block
		// 3. delete

		T* new_block = new T[new_capacity];

		if (new_capacity < size_)
			size_ = new_capacity;

		for (size_t i = 0; i < size_; i++)
			new_block[i] = data_[i];

		delete[] data_;
		data_ = new_block;
		capacity_ = new_capacity;
	}
private:
	T* data_ = nullptr;

	size_t size_ = 0;
	size_t capacity_ = 0;
};

template<typename T>
void print_vector(const my_vector<T>& vector)
{
	for (size_t i = 0; i < vector.size(); ++i)
		std::cout << vector[i] << std::endl;

	std::cout << "----------------------------------\n";
}

int main()
{
	constexpr int size = 5;
	stack_array<int, size> data;
	std::cout << "data size: " << data.size() << std::endl;
	data[0] = 1;
	std::cout  << data[0] << std::endl;

	const auto& array_reference = data;
	for (size_t i = 0; i < data.size(); ++i)
	{
		data[i] = 2;
		std::cout << "data size: " << array_reference[i] << std::endl;
	}

	memset(data.data(), 0, data.size() * sizeof(int));
	data[1] = 5;
	data[3] = 8;
	for (size_t i = 0; i < data.size(); ++i)
	{
		std::cout << "data  " << data[i] << std::endl;
	}

	std::cout << "\n my custom vector\n----------------------------------\n";

	// my vector implementation
	my_vector<std::string> vector;
	vector.push_back("David");
	vector.push_back("C++");
	vector.push_back("Vector");

	print_vector(vector);
}