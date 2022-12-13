//
//  main.cpp
//  Algo_count_string_hash
//
//  Created by Den Fedorov on 05.10.2022.
//

#include <cmath>
#include <regex>
#include <string>
#include <iostream>
#include <string_view>

void clear()
{
#if defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}

unsigned int simple_string_hash(const std::string_view & sv)
{
	if (sv.empty())
	{
		return 0;
	}
	else
	{
		unsigned int sum{ 0 };
		for (auto ch : sv)
		{
			sum += static_cast<unsigned int>(ch);
		}
		return sum;
	}
}

unsigned int real_string_hash(const std::string_view & sv, int prime, int value)
{
	if (sv.empty())
	{
		return 0;
	}
	else
	{
		unsigned int sum{ 0 };
		for (int i{ 0 }; i < sv.size(); ++i)
		{
			sum += static_cast<unsigned int>(sv[i]) * pow(prime, i);
		}
		return sum % value;
	}
}

bool is_prime(int n)
{
	for (int i = 2; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

void check(int & n)
{
	while (!(std::cin >> n) || (n <= 0))
	{
		std::cin.clear();
		while (std::cin.get() != '\n')
		{
			continue;
		}
		std::cout << "Please enter a positive value: ";
	}
}

int main()
{
//	clear();
	std::string input;
	const std::regex exit{ "\\s*?([E|e]xit)\\s*$" };
	std::cout << "\"exit\" to end\n";

	while (!std::regex_match(input, exit))
	{
		std::cout << ": ";
		std::getline(std::cin, input);
		std::cout << "Hash of \"" << input << "\" is " << simple_string_hash(input) << '\n';
	}

	input.clear();
	int prime{ 0 };
	int value{ 0 };

	clear();
	std::cout << "Enter a prime number: ";
	check(prime);

	while (!is_prime(prime))
	{
		std::cout << "\"" << prime << "\" is not a prime number. Try again: ";
		check(prime);
	}

	std::cout << "One more number: ";
	check(value);
	std::cin.get();
	clear();
	std::cout << "\"exit\" to end\n";

	while (!std::regex_match(input, exit))
	{
		std::cout << ": ";
		std::getline(std::cin, input);
		std::cout << "Hash of \"" << input << "\" is " << real_string_hash(input, prime, value) << '\n';
	}

	clear();
	std::cout << "Bye!\n";
	return 0;
}