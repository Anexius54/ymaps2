#pragma once

#include <iostream>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>

class Parser
{
	std::string html_data;
	std::vector<std::pair<double, double>> points_coordinates;
	int coordinates_count;
	
	std::vector<std::string> split(const std::string, const std::string);
	std::vector<std::pair<double, double>> split_point(const std::vector<std::string>, const std::string);

public:
	Parser(const std::string);
	~Parser();
	int parse();
};

