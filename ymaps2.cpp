#include <iostream>
#include <fstream>
#include <string>
//
#include "parser.h"
#include "route.h"

std::string readAll(const std::string& fileName)
{
	std::ifstream ifs;
	ifs.open(fileName);
	ifs.seekg(0, std::ios::end);
	int length = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	std::string buff(length, 0);
	ifs.read(&buff[0], length);
	ifs.close();

	return buff;
}


int main()
{
	//const std::string data = readAll("ymaps_html.txt");
	//Parser html_data(data);
	//int i = html_data.parse();

	//route_t<double> coordinates = html_data.get_coordinates();
	///*for (auto x : coordinates)
	//{
	//	std::cout << x.first << " " << x.second << " ";
	//}*/

	//Route route(coordinates);
	//route.douglas_peucker();
	//route_t<double> test = route.get_route();

	//std::cout << "yandex route size: " << route.get_yandex_route_size()
	//	<< "\nour route size: " << route.get_zip_route_size() << "\n";
	//
	//std::ofstream ofs;
	//ofs.open("test_log.txt");

	//ofs.precision(8);
	//for (auto x : test)
	//{
	//	ofs << x.first << ", " << x.second << " ";
	//}
	//ofs.close();

	const char * filename = "test.txt";
	for (auto x : route)
	{
		std::cout << x.first << " " << x.second << " ";
	}

	return 0;
}