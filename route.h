#pragma once
#include <vector>
#include <string>
#include <iostream>

#define X_COORDINATE 0
#define Y_COORDINATE 1


template<typename T>
using point_t = std::pair<T, T>;

template<typename T>
using route_t = std::vector<point_t<T>>;

template<typename T>
using line_segment_t = std::pair<point_t<T>, point_t<T>>;

class Route
{
	double get_distance_between_point_and_line_segment(
		const line_segment_t<double>& line_segment, 
		const point_t<double>& point) noexcept;

	void simplify_points(
		const route_t<double>& src_points, 
		route_t<double>& dest_points, 
		std::size_t begin, std::size_t end);

	route_t<double> unpack_route;
	route_t<double> zip_route;
	int yandex_route_size;
	int zip_route_size;
	double tolerance = 0.0001;

public:
	Route(const route_t<double>&);
	~Route();

	void douglas_peucker() noexcept;

	route_t<double> get_route();
	
	int get_yandex_route_size();
	int get_zip_route_size();

};

