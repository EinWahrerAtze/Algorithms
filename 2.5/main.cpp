//
//  main.cpp
//  Pyramids
//
//  Created by Den Fedorov on 28.09.2022.
//

#include <algorithm>
#include <iostream>
#include <array>
#include <cmath>

void clear()
{
#if defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}

template<typename T, std::size_t S>
void display(const std::array<T, S> & array)
{
	std::cout << "Array: ";
	for (int i : array)
	{
		std::cout << i << ' ';
	}
	std::cout << "\nPyramid:\n";
	std::cout << "0 root: " << '\t' << array[0] << '\n';
	std::size_t level {1};
	for (std::size_t i {1}; i != S; ++i)
	{
		level = static_cast<std::size_t>(log(i + 1) / log(2));
		if (i % 2 == 0)
		{
			std::cout << level << " right [";
		}
		else
		{
			std::cout << level << " left  [";
		}
		std::cout << array[(i - 1) / 2] << ']';
		std::cout << '\t' << array[i] << '\n';
	}
	std::cout << '\n';
}

template<typename T, std::size_t S>
void display(const std::array<T, S> & array, std::size_t index)
{
	std::size_t level {static_cast<std::size_t>(log(index + 1) / log(2))};
	std::cout << "You are here: ";
	if (index == 0)
	{
		std::cout << level << " root " << array[index] << '\n';
	}
	else
	{
		std::cout << level;
		std::cout << (index % 2 == 0 ? " right [" : " left  [");
		std::cout << array[(index - 1) / 2] << ']';
		std::cout << '\t' << array[index] << '\n';
	}
}

template<typename T, std::size_t S>
void explore(const std::array<T, S> & array)
{
	char ch {};
	bool quit {false};
	std::size_t index {};
	std::size_t previous {};
	display(array);
	std::cout << "Begin your journey!\n'W' to go up, 'A' to go left, 'D' to go right, 'C' to clear screen\n\n";
	display(array, index);
	while (!quit)
	{
		std::cout << ": ";
		std::cin >> ch;
		std::cin.ignore(10000, '\n');
		previous = index;
		switch (ch)
		{
			case 'a':
			case 'A':
			{
				index = index * 2 + 1;
				break;
			}
			case 'd':
			case 'D':
			{
				index = index * 2 + 2;
				break;
			}
			case 'w':
			case 'W':
			{
				if (index == 0)
				{
					std::cout << "You are at the root of the pyramid!\n";
				}
				else
				{
					index = (index - 1) / 2;
					display(array, index);
				}
				continue;
			}
			case 'c':
			case 'C':
			{
				clear();
				std::cout << "'W' to go up, 'A' to go left, 'D' to go right, 'C' to clear screen\n\n";
				display(array);
				display(array, index);
				continue;
			}
			case 'x':
			case 'X':
			{
				clear();
				std::cout << "You got lost. Farewell!\n";
				quit = true;
			}
			default:
			{
				continue;
			}
		}
		if (index > array.size() - 1)
		{
			std::cout << "Deadlock!\n";
			index = previous;
		}
		else
		{
			display(array, index);
		}
	}
}

int main(int argc, const char * argv[])
{
//	clear();
	std::array<int, 6> array_one {1, 3, 6, 5, 9, 8};
	const std::size_t S {19};
	std::array<int, S> array_two {};
	display(array_one);
	std::time(0);
	std::generate(std::begin(array_two), std::end(array_two), []() -> int
	{
		return rand() % 100 + 1;
	});
	std::sort(std::begin(array_two), std::end(array_two), [](int one, int two) -> bool
	{
		return one < two;
	});
	explore(array_one);
//	explore(array_two);
	return 0;
}
