#include <fstream>
#include <iostream>
#include <tuple>
#include <optional>
#include <string>

std::tuple<std::string, int> create_person()
{
	return { "David", 44 };
}

std::optional<std::string> read_file_as_string(const std::string& filepath)
{
	if(std::ifstream stream(filepath); stream)
	{
		//read file
		std::string result;
		std::getline(stream, result);
		stream.close();
		return result;
	}

	return {};
}

int main()
{
	// structured bindings -> tuple - lesson 75
	auto [name, age] = create_person();
	std::cout << "Name: " << name << " Age: " << age << std::endl;

	// how to deal with optional data
	const auto data = read_file_as_string("data.txt");
	const auto result = data.value_or("File could not be opened!\n");
	std::cout << result << std::endl;

	std::cin.get();
}
