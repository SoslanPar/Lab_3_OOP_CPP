#include <gtest/gtest.h>
#include "../include/hexagon.h"
#include "../include/point.h"

TEST(HexagonTest, ConstructionAndPoints) {
    Point p1(1, 0), p2(0.5, 0.866), p3(-0.5, 0.866), p4(-1, 0), p5(-0.5, -0.866), p6(0.5, -0.866);
    Hexagon hexagon(p1, p2, p3, p4, p5, p6, "Test Hexagon");
    
    // Вычисляем реальную длину стороны
    double side_length = distance(p1, p2);
    double expected_area = 2.598 * side_length * side_length;
    
    EXPECT_NEAR(hexagon.square(), expected_area, 1e-6);
}

TEST(HexagonTest, GeometricCenter) {
    Point p1(1, 0), p2(0.5, 0.866), p3(-0.5, 0.866), p4(-1, 0), p5(-0.5, -0.866), p6(0.5, -0.866);
    Hexagon hexagon(p1, p2, p3, p4, p5, p6, "Test Hexagon");
    
    Point center = hexagon.geometric_center();
    EXPECT_NEAR(center.get_x(), 0.0, 1e-3);
    EXPECT_NEAR(center.get_y(), 0.0, 1e-3);
}

TEST(HexagonTest, ComparisonOperators) {
    Point p1(1, 0), p2(0.5, 0.866), p3(-0.5, 0.866), p4(-1, 0), p5(-0.5, -0.866), p6(0.5, -0.866);
    Hexagon hexagon1(p1, p2, p3, p4, p5, p6, "Hexagon 1");
    Hexagon hexagon2(p1, p2, p3, p4, p5, p6, "Hexagon 2");
    
    EXPECT_TRUE(hexagon1 == hexagon2);
    EXPECT_EQ(hexagon1 <=> hexagon2, std::partial_ordering::equivalent);
}

TEST(HexagonTest, Clone) {
    Point p1(1, 0), p2(0.5, 0.866), p3(-0.5, 0.866), p4(-1, 0), p5(-0.5, -0.866), p6(0.5, -0.866);
    Hexagon hexagon(p1, p2, p3, p4, p5, p6, "Test Hexagon");
    
    Figure* cloned = hexagon.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(hexagon.square(), cloned->square());
    delete cloned;
}