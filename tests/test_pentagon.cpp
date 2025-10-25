#include <gtest/gtest.h>
#include "../include/pentagon.h"
#include "../include/point.h"

TEST(PentagonTest, ConstructionAndPoints) {
    Point p1(0, 1), p2(0.951, 0.309), p3(0.587, -0.809), p4(-0.587, -0.809), p5(-0.951, 0.309);
    Pentagon pentagon(p1, p2, p3, p4, p5, "Test Pentagon");
    
    // Вычисляем реальную длину стороны
    double side_length = distance(p1, p2);
    double expected_area = 1.72 * side_length * side_length;
    
    EXPECT_NEAR(pentagon.square(), expected_area, 1e-6);
}

TEST(PentagonTest, GeometricCenter) {
    Point p1(0, 1), p2(0.951, 0.309), p3(0.587, -0.809), p4(-0.587, -0.809), p5(-0.951, 0.309);
    Pentagon pentagon(p1, p2, p3, p4, p5, "Test Pentagon");
    
    Point center = pentagon.geometric_center();
    EXPECT_NEAR(center.get_x(), 0.0, 1e-3);
    EXPECT_NEAR(center.get_y(), 0.0, 1e-3);
}

TEST(PentagonTest, ComparisonOperators) {
    Point p1(0, 1), p2(0.951, 0.309), p3(0.587, -0.809), p4(-0.587, -0.809), p5(-0.951, 0.309);
    Pentagon pentagon1(p1, p2, p3, p4, p5, "Pentagon 1");
    Pentagon pentagon2(p1, p2, p3, p4, p5, "Pentagon 2");
    
    EXPECT_TRUE(pentagon1 == pentagon2);
    EXPECT_EQ(pentagon1 <=> pentagon2, std::partial_ordering::equivalent);
}

TEST(PentagonTest, Clone) {
    Point p1(0, 1), p2(0.951, 0.309), p3(0.587, -0.809), p4(-0.587, -0.809), p5(-0.951, 0.309);
    Pentagon pentagon(p1, p2, p3, p4, p5, "Test Pentagon");
    
    Figure* cloned = pentagon.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(pentagon.square(), cloned->square());
    delete cloned;
}