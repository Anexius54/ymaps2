#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <vector>

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
	const std::string data = readAll("ymaps_html.txt");

	const boost::regex expr(R"("coordinates":\[(\[\d+\.\d+,\d+\.\d+\],?)+\])");
	boost::smatch m;
	std::cout << "==========================Results============================== \n";
	boost::sregex_iterator xIt(data.begin(), data.end(), expr);
	boost::sregex_iterator xInvalidIt;
	std::cout << "size: " << std::distance(xIt, xInvalidIt) << std::endl;
	while (xIt != xInvalidIt)
		std::cout << *xIt++ << "\n";

	return 0;
}
