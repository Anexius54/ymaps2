#pragma once
#include <iostream>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>


template<typename T>
using point_t = std::pair<T, T>;

template<typename T>
using route_t = std::vector<point_t<T>>;

class Parser
{
	std::string html_data;

	route_t<double> coordinates;
	int coordinates_count;
	
	std::vector<std::string> split(const std::string, const std::string);
	route_t<double> split_point(const std::vector<std::string>, const std::string);

public:
	Parser(const std::string);
	~Parser();
	int parse();
	route_t<double> get_coordinates();
};

