//
//  main.cpp
//  Dynamic_array
//
//  Created by Den Fedorov on 03.10.2022.
//

#include <iostream>
#include <string>

void clear()
{
#if defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}

void check(int & value)
{
	while (!(std::cin >> value))
	{
		std::cin.clear();
		while (std::cin.get() != '\n') { continue; }
		std::cout << "Please enter an integer value: ";
	}
}

void print_dynamic_array(const int * const arr, int logical_size, int actual_size)
{
	if (arr == nullptr)
	{
		std::cout << "Array is empty!\n";
	}
	else
	{
		for (int i{ 0 }; i < actual_size; ++i)
		{
			i < logical_size ? std::cout << *(arr + i) : std::cout << '_';
			std::cout << (i < actual_size - 1 ? ' ' : '\n');
		}
	}

	std::cout << '\n';
}

void append_to_dynamic_array(int *& arr, int & logical_size, int & actual_size, int value)
{
	if (arr == nullptr)
	{
		if (actual_size == 0) {	actual_size = 5; }
		arr = new int[actual_size];
		*(arr + logical_size) = value;
		++logical_size;
	}
	else if (logical_size == actual_size)
	{
		int new_actual_size{ actual_size * 2 };
		int * new_arr{ new int[new_actual_size] };

		for (int i{ 0 }; i < actual_size; ++i)
		{
			*(new_arr + i) = *(arr + i);
		}

		actual_size = new_actual_size;
		*(new_arr + logical_size) = value;
		++logical_size;
		delete[] arr;
		arr = new_arr;
	}
	else
	{
		*(arr + logical_size) = value;
		++logical_size;
	}
}

void remove_dynamic_array_head(int *& arr, int & logical_size, int & actual_size)
{
	if (logical_size == 1)
	{
		--logical_size;
		delete[] arr;
		arr = nullptr;
	}
	else if (logical_size - 1 <= actual_size / 3)
	{
		int new_actual_size{ actual_size / 3 };
		int * new_arr{ new int[new_actual_size] };
		--logical_size;

		for (int i{ 0 }; i < logical_size; ++i)
		{
			*(new_arr + i) = *(arr + i + 1);
		}

		actual_size = new_actual_size;
		delete[] arr;
		arr = new_arr;
	}
	else
	{
		for (int i{ 0 }; i < logical_size; ++i)
		{
			*(arr + i) = *(arr + i + 1);
		}

		--logical_size;
	}
}

int main()
{
//	clear();
	int logical_size{ 0 };
	int actual_size{ 0 };

	while (true)
	{
		std::cout << "Enter logical size of array: ";
		check(logical_size);
		std::cout << "Enter actual size of array: ";
		check(actual_size);

		if (logical_size > actual_size)
		{
			clear();
			std::cout << "Logical size must be equal or less than actual size!\n";
			continue;
		}
		else if (logical_size < 0 || actual_size < 0)
		{
			clear();
			std::cout << "Size must be positive!\n";
			continue;
		}
		else
		{
			break;
		}
	}

	clear();
	int * arr{ new int[actual_size]() };
	std::cout << "Fill array:\n";

	for (std::size_t i{ 0 }; i < logical_size; ++i)
	{
		std::cout << "Array[" << i + 1 << "] = ";
		check(*(arr + i));
	}

	clear();
	std::cin.get();
	int value{ 0 };
	std::string input;
	std::string message("'R' to remove element, 'X' to leave");

	while (true)
	{
		if (message.empty())
		{
			std::cout << "Logical size: " << logical_size;
			std::cout << " Actual size: " << actual_size << '\n' << '\n';
		}
		else
		{
			std::cout << message << '\n' << '\n';
		}

		print_dynamic_array(arr, logical_size, actual_size);
		std::cout << "Add new element: ";
		std::getline(std::cin, input);
		message.clear();

		if (input.empty())
		{
			clear();
			message = "Empty input.";
			continue;
		}

		switch (input.front())
		{
			case 'r':
			case 'R':
			{
				if (arr == nullptr)
				{
					clear();
					message = "You cannot remove elements from an empty array!";
					continue;
				}
				else
				{
					clear();
					remove_dynamic_array_head(arr, logical_size, actual_size);
					continue;
				}
			}
			case 'x':
			case 'X':
			{
				clear();
				break;
			}
			default:
			{
				clear();

				try
				{
					value = std::stoi(input);
				}
				catch (const std::out_of_range & ex)
				{
					message = "Value is too huge!";
					continue;
				}
				catch (const std::invalid_argument & ex)
				{
					message = "Invalid argument passed!";
					continue;
				}

				append_to_dynamic_array(arr, logical_size, actual_size, value);
				continue;
			}
		}

		break;
	}

	delete[] arr;
	std::cout << "See you later!\n";
	return 0;
}