#include "../include/pentagon.h"
#include "../include/point.h"
#include <stdexcept>

Pentagon::Pentagon(const Point& p1, 
                    const Point& p2, 
                    const Point& p3, 
                    const Point& p4, 
                    const Point& p5, 
                    std::string description)
    :Figure(description)
    {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    }

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Pentagon::Pentagon(const Pentagon& other){
    for (int i = 0; i < 5; ++i){
        points[i] = other.points[i];
    }
}

// Перегрузка копирования.
Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        for (int i = 0; i < 5; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Pentagon::Pentagon(Pentagon&& other) noexcept {
    for (int i = 0; i < 5; ++i) {
        points[i] = std::move(other.points[i]);
    }
}
// Перегрузка перемещения.
Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 5; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Pentagon::operator==(const Pentagon& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
std::partial_ordering Pentagon::operator<=>(const Pentagon& other) const {
    return this->square() <=> other.square();
}

Point Pentagon::geometric_center() const {
    double center_x = (points[0].get_x() + points[1].get_x() + points[2].get_x() + points[3].get_x() + points[4].get_x()) / 5.0;
    double center_y = (points[0].get_y() + points[1].get_y() + points[2].get_y() + points[3].get_y() + points[4].get_y()) / 5.0;
    return Point(center_x, center_y);
}

double Pentagon::square() const {
    double l = distance(points[0], points[1]);
    double area = 1.72 * l * l;
    return area;
}

double Pentagon::perimeter() const {
    double l = distance(points[0], points[1]);
    return (l * 5);
}

Pentagon::operator double() const {
    return this->square();
}

void Pentagon::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Pentagon::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Pentagon::clone() const {
    return new Pentagon(this->points[0], 
        this->points[1], 
        this->points[2], 
        this->points[3], 
        this->points[4]);
}