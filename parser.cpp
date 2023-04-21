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

route_t<double> Parser::split_point(const std::vector<std::string> point_coords_str, const std::string delimiter)
{
	/*coordinates format: vector[pair{x0, y0}, ... , pair{xn, yn}]*/
	route_t<double> res;

	for (size_t i = 0; i < point_coords_str.size(); i++)
	{
		size_t last = 0;
		size_t next = point_coords_str[i].find(delimiter, last);
		std::cout.precision(8);
		using boost::lexical_cast;
		point_t<double> point_tmp = std::make_pair(
										lexical_cast<double>(point_coords_str[i].substr(next + 1)),
										lexical_cast<double>(point_coords_str[i].substr(last, next - last)));
		res.push_back(point_tmp);
	}
	return res;
}


int Parser::parse()
{
	/*todo: validate .html to contain <script "state-view">*/
	std::string validate = "<script type=\"application/json\" class=\"state-view\">";
	auto validate_res = html_data.find(validate);
	if (validate_res == std::string::npos)
		return 0; // no match

	const boost::regex expr(R"("coordinates":\[(\[\d+\.\d+,\d+\.\d+\],?)+\])");

	boost::sregex_iterator xIt(html_data.begin(), html_data.end(), expr);
	boost::sregex_iterator xInvalidIt;

	std::string buffer = (*xIt).str();
	buffer = buffer.substr(16, buffer.size() - 18); // '"coordinates":[[' -- 16 chars + ']]' 2 chars
	std::vector<std::string> point_coords_str = split(buffer, "],[");
	coordinates = split_point(point_coords_str, ",");
	
	return 1;
}

route_t<double> Parser::get_coordinates()
{
	return coordinates;
}
