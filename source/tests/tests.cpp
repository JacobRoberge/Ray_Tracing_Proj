#include <gtest/gtest.h>
#include <memory>

#include "../main/Ray.h"
#include <opencv2/core.hpp>

using namespace std;
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
	
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(RAY_TESTS, ray_at)
{
	auto test_ray = std::make_unique<Ray>(cv::Vec3f(1, 1, 1), cv::Vec3f(1, 1, 1));
	EXPECT_EQ(cv::Vec3f(3, 3, 3), test_ray->at(2));

}
