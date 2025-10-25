#include "../include/hexagon.h"
#include "../include/point.h"
#include <stdexcept>

Hexagon::Hexagon(const Point& p1,
                const Point& p2,
                const Point& p3,
                const Point& p4,
                const Point& p5,
                const Point& p6,
                std::string description)
    :Figure(description)
    {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    points[5] = p6;
    }

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Hexagon::Hexagon(const Hexagon& other){
    for (int i = 0; i < 6; ++i){
        points[i] = other.points[i];
    }
}

// Перегрузка копирования.
Hexagon& Hexagon::operator=(const Hexagon& other) {
    if (this != &other) {
        for (int i = 0; i < 6; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Hexagon::Hexagon(Hexagon&& other) noexcept {
    for (int i = 0; i < 6; ++i) {
        points[i] = std::move(other.points[i]);
    }
}
// Перегрузка перемещения.
Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 6; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Hexagon::operator==(const Hexagon& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
std::partial_ordering Hexagon::operator<=>(const Hexagon& other) const {
    return this->square() <=> other.square();
}

Point Hexagon::geometric_center() const {
    double center_x = (points[0].get_x() + points[1].get_x() + points[2].get_x() + points[3].get_x() + points[4].get_x() + points[5].get_x()) / 6.0;
    double center_y = (points[0].get_y() + points[1].get_y() + points[2].get_y() + points[3].get_y() + points[4].get_y() + points[5].get_y()) / 6.0;
    return Point(center_x, center_y);
}

double Hexagon::square() const {
    double l = distance(points[0], points[1]);
    double area = 2.598 * l * l; // 2.598 = 3*sqrt(3)/2
    return area;
}

double Hexagon::perimeter() const {
    double l = distance(points[0], points[1]);
    return (l * 6);
}

Hexagon::operator double() const {
    return this->square();
}

void Hexagon::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Hexagon::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Hexagon::clone() const {
    return new Hexagon(this->points[0],
                        this->points[1], 
                        this->points[2], 
                        this->points[3], 
                        this->points[4], 
                        this->points[5]);
}