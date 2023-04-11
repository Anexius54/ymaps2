#include "parser.h"
#include "parser.h"



Parser::Parser(const std::string html_data)
{
	this->html_data = html_data;
}




Parser::~Parser()
{
}


std::vector<std::string> Parser::split(const std::string s,const std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

std::vector<std::pair<double, double>> Parser::split_point(const std::vector<std::string> point_coords_str, const std::string delimiter)
{
	std::vector<std::pair<double, double>> res;

	for (size_t i = 0; i < point_coords_str.size(); i++)
	{
		size_t last = 0;
		size_t next = point_coords_str[i].find(delimiter, last);
		std::cout.precision(7);
		using boost::lexical_cast;
		auto point_tmp = std::make_pair(lexical_cast<double>(point_coords_str[i].substr(last, next - last)), lexical_cast<double>(point_coords_str[i].substr(next + 1)));
		res.push_back(point_tmp);
	}
	return res;
}

int Parser::parse()
{
	const boost::regex expr(R"("coordinates":\[(\[\d+\.\d+,\d+\.\d+\],?)+\])");

	boost::sregex_iterator xIt(this->html_data.begin(), this->html_data.end(), expr);
	boost::sregex_iterator xInvalidIt;

	//this->coordinates_count = std::distance(xIt, xInvalidIt) / 2;
	//std::string buffer, result = "";
	//for (int i = 0; i < this->coordinates_count; i++)
	//{
	//	buffer = (*xIt).str();
	//	buffer = buffer.substr(15, buffer.size() - 16); // '"coordinates":[' -- 15 chars + ']' 1 chars
	//	result += buffer;
	//	std::cout << buffer << "\n\n";
	//	*xIt++;
	//}
	//this->coordinates_data = result;


	std::string buffer = (*xIt).str();
	buffer = buffer.substr(16, buffer.size() - 18); // '"coordinates":[[' -- 16 chars + ']]' 2 chars
	std::vector<std::string> point_coords_str = split(buffer, "],[");
	this->points_coordinates = split_point(point_coords_str, ",");
	for (auto x : point_coords_str)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";

	for (auto x : this->points_coordinates)
	{
		std::cout << x.first << " " << x.second << " ";
	}




	return 1;
}
