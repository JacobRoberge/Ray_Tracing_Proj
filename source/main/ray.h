#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


class ray
{
private:
	cv::Vec3f orig;
	cv::Vec3f dir;

public:
	ray() = default;
	ray(const cv::Vec3f& orig, const cv::Vec3f& dir)
	{
		this->orig = orig;
		this->dir = dir;
	}
	cv::Vec3f origin() const { return orig; }
	cv::Vec3f direction() const { return dir; }
	cv::Vec3f at(const double t) const
	{
		return orig + t * dir;
	}

};