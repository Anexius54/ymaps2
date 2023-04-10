#include <iostream>
#include <fstream>
#include <vector>

#include "parser.h"

#define C_ALL(X) cbegin(X), cend(X)

std::string readAll(const std::string &fileName)
{
	std::ifstream ifs;
	ifs.open(fileName);
	ifs.seekg(0, std::ios::end);
	size_t length = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	std::string buff(length, 0);
	ifs.read(&buff[0], length);
	ifs.close();

	return buff;
}

int main()
{
	std::string data = readAll("ymaps_html.txt");
	std::cout << "asd\n";
	std::regex expr(R"("coordinates":\[(\[\d+\.\d+,\d+\.\d+\],?)+\])"); //fix regex

	std::vector<std::string> full_match{
		std::sregex_token_iterator{C_ALL(data), expr, 0},
		std::sregex_token_iterator{}
	};
	std::cout << "size: " << full_match.size() << std::endl;
	for  (auto x : full_match)
	{
		std::cout << x << std::endl;
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
