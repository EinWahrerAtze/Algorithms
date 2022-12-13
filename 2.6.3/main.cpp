#include <regex>
#include <string>
#include <iostream>
#include <stdexcept>
#include <string_view>

void clear()
{
#if defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}

int count_hash(std::string_view::const_iterator begin, std::string_view::const_iterator end)
{
	if (begin == end)
	{
		return 0;
	}
	else
	{
		int sum{ 0 };

		while (begin != end)
		{
			sum += static_cast<int>(*begin);
			++begin;
		}

		return sum;
	}
}

int find_substring_light_rabin_karp(const std::string_view & str, const std::string_view & substr)
{
	if (str.size() < substr.size())
	{
		throw std::invalid_argument("substring is greater than given");
	}

	int str_hash{ 0 };
	int substr_hash{ count_hash(substr.cbegin(), substr.cend()) };

	for (std::size_t i{ 0 }; i <= str.size() - substr.size(); ++i)
	{
		if (i == 0)
		{
			str_hash = count_hash(str.cbegin(), str.cbegin() + substr.size());
		}
		else
		{
			str_hash -= static_cast<int>(str[i - 1]);
			str_hash += static_cast<int>(str[i + substr.size() - 1]);
		}

		if (substr_hash == str_hash)
		{
			for (std::size_t j{ 0 }; j < substr.size(); ++j)
			{
				if (str[i + j] == substr[j])
				{
					if (j == substr.size() - 1)
					{
						return static_cast<int>(i);
					}
					else
					{
						continue;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			continue;
		}
	}

	return -1;
}

int main()
{
//	clear();
	int result{ 0 };
	std::string str;
	std::string substr;
	std::string message;
	std::cmatch parts;
	const std::regex leave{ R"x(\s*(E|e)xit\s*)x" };
	const std::regex change{ R"x(\s*((C|c)hange:\s*)(.*)\s*$)x" };

	std::cout << "enter something: ";
	std::getline(std::cin, str);

	while (str.empty())
	{
		std::cout << "please, input some text to play with: ";
		std::getline(std::cin, str);
	}

	while (true)
	{
		clear();

		if (message.empty())
		{
			std::cout << "type \"exit\" to leave or \"change: <sentence>\" to refresh string";
		}
		else
		{
			std::cout << message;
			message.clear();
		}

		std::cout << "\n\"" << str << "\"\n";

		while (true)
		{
			std::cout << "find: ";
			std::getline(std::cin, substr);

			if (substr.empty())
			{
				continue;
			}
			else if (std::regex_match(substr, leave))
			{
				clear();
				std::cout << "bye!\n";
				exit(EXIT_SUCCESS);
			}
			else if (std::regex_match(substr.c_str(), parts, change))
			{
				str = parts[3];

				while (str.empty())
				{
					std::cout << "please enter a new sentence: ";
					std::getline(std::cin, str);
				}

				break;
			}
			else
			{
				try
				{
					result = find_substring_light_rabin_karp(str, substr);

					if (result == -1)
					{
						std::cout << "\"" << substr << "\" not found\n";
					}
					else
					{
						std::cout << "\"" << substr << "\" begins at " << result << '\n';
					}
				}
				catch (const std::invalid_argument & ex)
				{
					clear();
					message = ex.what();
					break;
				}
				catch (...)
				{
					clear();
					message = "something went wrong...\n";
					break;
				}
			}
		}
	}

	return 0;
}