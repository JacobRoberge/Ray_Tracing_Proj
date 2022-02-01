#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <filesystem>
#include <algorithm>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include<Windows.h>

#include "main/ray.h"


void test_image()
{
    // Image


    const int image_width = 256;
    const int image_height = 256;

    cv::Mat img = cv::Mat(image_width, image_height, CV_8UC3);

    // Render

    auto a = cv::Vec3b(1, 2, 3);
    auto b = cv::Vec3b(1, 2, 3);

    std::cout << "test: " << float(a.dot(b)) << std::endl;
    //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //for (int j = image_height-1; j >= 0; --j) {
    for (int j = 0; j < image_height; ++j) {
        std::cerr << "\rScanlines remaining: " << j / double(image_height) << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {
            //for (int i = image_width - 1; i >= 0; --i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            //auto g = .25;
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);



            img.at<cv::Vec3b>(cv::Point(j,  i)) = cv::Vec3b(ir, ig, ib);
            //cv::flip(img, 1);


        }
    }
    cv::cvtColor(img, img, cv::COLOR_RGB2BGR);
    cv::imshow("test", img);
    cv::waitKey(0);

}
double hit_sphere(const cv::Vec3f& center, double radius, const ray& ray)
{
    cv::Vec3f oc = ray.origin() - center;
    //auto a = ray.direction().dot(ray.direction());
    //auto b = 2.0 * oc.dot(ray.direction());
    //auto c = oc.dot(oc) - radius * radius;

    auto a = cv::norm(ray.direction(), cv::NORM_L2SQR);
    auto half_b = oc.dot(ray.direction());
    auto c = cv::norm(oc,cv::NORM_L2SQR) - radius * radius;
    auto discriminant = half_b * half_b - a * c;


    if(discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }

}

cv::Vec3f ray_color(const ray& line)
{
    auto ret_hit = hit_sphere(cv::Vec3f(0, 0, -1), 0.5, line);
    if(ret_hit > 0.0)
    {
        auto N = line.at(ret_hit) - cv::Vec3f(0, 0, -1);
        N = N / cv::norm(N, cv::NORM_L2);
        return 0.5 * cv::Vec3f(N[0] + 1, N[1] + 1, N[2] + 1);

    }
    cv::Vec3f unit_dir = line.direction() / cv::norm(line.direction(), cv::NORM_L2);
    auto t = 0.5 * (unit_dir[1] + 1.0);
    return (1.0 - t) * cv::Vec3f(1.0, 1.0, 1.0) + t * cv::Vec3f(0.5, 0.7, 1.0);
}
void test_ray_render()
{
    // Image


    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1000;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    cv::Mat img = cv::Mat(image_height, image_width, CV_8UC3);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = cv::Vec3f(0, 0, 0);
    auto horizontal = cv::Vec3f(viewport_width, 0, 0);
    auto vertical = cv::Vec3f(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - cv::Vec3f(0, 0, focal_length);

    //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::cerr << "\rScanlines remaining: " << j / double(image_height) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {

            auto u = double(i) / (image_width - 1);
            auto v = double(image_height - 1 -j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            cv::Vec3f pixel_color = ray_color(r);



            img.at<cv::Vec3b>(cv::Point(i, j)) = pixel_color*255.9999;
            //cv::flip(img, 1);


        }
    }
    cv::cvtColor(img, img, cv::COLOR_RGB2BGR);
    cv::imshow("test", img);
    cv::waitKey(0);

}

int main()
{
    //auto vec = cv::Vec3f(1, 2, 3);
    //std::cout << "norm: " << cv::norm(vec,cv::NORM_L2SQR);
    test_ray_render();
    //test_image();
}
