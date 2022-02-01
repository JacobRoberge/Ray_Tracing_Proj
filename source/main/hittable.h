
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    cv::Vec3f p;
    cv::Vec3f normal;
    double t;
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif