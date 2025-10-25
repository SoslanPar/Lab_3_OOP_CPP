#include <gtest/gtest.h>
#include "../include/octagon.h"
#include "../include/point.h"

TEST(OctagonTest, ConstructionAndPoints) {
    Point p1(1, 0), p2(0.707, 0.707), p3(0, 1), p4(-0.707, 0.707),
          p5(-1, 0), p6(-0.707, -0.707), p7(0, -1), p8(0.707, -0.707);
    Octagon octagon(p1, p2, p3, p4, p5, p6, p7, p8, "Test Octagon");
    
    // Вычисляем реальную длину стороны
    double side_length = distance(p1, p2);
    double expected_area = 4.828 * side_length * side_length;
    
    EXPECT_NEAR(octagon.square(), expected_area, 1e-6);
}

TEST(OctagonTest, GeometricCenter) {
    Point p1(1, 0), p2(0.707, 0.707), p3(0, 1), p4(-0.707, 0.707),
          p5(-1, 0), p6(-0.707, -0.707), p7(0, -1), p8(0.707, -0.707);
    Octagon octagon(p1, p2, p3, p4, p5, p6, p7, p8, "Test Octagon");
    
    Point center = octagon.geometric_center();
    EXPECT_NEAR(center.get_x(), 0.0, 1e-3);
    EXPECT_NEAR(center.get_y(), 0.0, 1e-3);
}

TEST(OctagonTest, ComparisonOperators) {
    Point p1(1, 0), p2(0.707, 0.707), p3(0, 1), p4(-0.707, 0.707),
          p5(-1, 0), p6(-0.707, -0.707), p7(0, -1), p8(0.707, -0.707);
    Octagon octagon1(p1, p2, p3, p4, p5, p6, p7, p8, "Octagon 1");
    Octagon octagon2(p1, p2, p3, p4, p5, p6, p7, p8, "Octagon 2");
    
    EXPECT_TRUE(octagon1 == octagon2);
    EXPECT_EQ(octagon1 <=> octagon2, std::partial_ordering::equivalent);
}

TEST(OctagonTest, Clone) {
    Point p1(1, 0), p2(0.707, 0.707), p3(0, 1), p4(-0.707, 0.707),
          p5(-1, 0), p6(-0.707, -0.707), p7(0, -1), p8(0.707, -0.707);
    Octagon octagon(p1, p2, p3, p4, p5, p6, p7, p8, "Test Octagon");
    
    Figure* cloned = octagon.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(octagon.square(), cloned->square());
    delete cloned;
}