#include "route.h"

double Route::get_distance_between_point_and_line_segment(
		const line_segment_t<double>& line_segment,
		const point_t<double>& point) noexcept
{
	const double x = std::get<X_COORDINATE>(point);
	const double y = std::get<Y_COORDINATE>(point);

	const double x1 = std::get<X_COORDINATE>(line_segment.first);
	const double y1 = std::get<Y_COORDINATE>(line_segment.first);

	const double x2 = std::get<X_COORDINATE>(line_segment.second);
	const double y2 = std::get<Y_COORDINATE>(line_segment.second);

	const double double_area = abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
	const double line_segment_length = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	if (line_segment_length != 0.0)
		return double_area / line_segment_length;
	else
		return 0.0;
}

void Route::simplify_points(
		const  route_t<double>& src_points, 
		route_t<double>& dest_points, 
		std::size_t begin, std::size_t end)
{
	if (begin + 1 == end)
		return;

	double max_distance = -1.0;
	std::size_t max_index = 0;
	for (std::size_t i = begin + 1; i < end; i++)
	{
		const point_t<double>& cur_point = src_points.at(i);
		const point_t<double>& start_point = src_points.at(begin);
		const point_t<double>& end_point = src_points.at(end);
		const double distance = get_distance_between_point_and_line_segment({ start_point, end_point }, cur_point);
		if (distance > max_distance)
		{
			max_distance = distance;
			max_index = i;
		}
	}

	if (max_distance > tolerance)
	{
		simplify_points(src_points, dest_points, begin, max_index);
		dest_points.push_back(src_points.at(max_index));
		simplify_points(src_points, dest_points, max_index, end);
	}
}

Route::Route(const route_t<double>& coords)
{
	unpack_route = coords;
	yandex_route_size = coords.size();
}

Route::~Route()
{
}

void Route::douglas_peucker() noexcept
{
	zip_route.push_back(unpack_route.front());
	simplify_points(unpack_route, zip_route, 0, unpack_route.size() - 1);
	zip_route.push_back(unpack_route.back());
	zip_route_size = zip_route.size();
}

route_t<double> Route::get_route()
{
	return zip_route;
}

int Route::get_yandex_route_size()
{
	return yandex_route_size;
}

int Route::get_zip_route_size()
{
	return zip_route_size;
}
