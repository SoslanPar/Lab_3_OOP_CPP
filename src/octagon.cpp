#include "../include/octagon.h"
#include "../include/point.h"
#include <stdexcept>


Octagon::Octagon(const Point& p1,
                const Point& p2,
                const Point& p3,
                const Point& p4,
                const Point& p5,
                const Point& p6,
                const Point& p7,
                const Point& p8,
                std::string description)
    :Figure(description)
    {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    points[5] = p6;
    points[6] = p7;
    points[7] = p8;
    }

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Octagon::Octagon(const Octagon& other){
    for (int i = 0; i < 8; ++i){
        points[i] = other.points[i];
    }
}

// Перегрузка копирования.
Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        for (int i = 0; i < 8; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Octagon::Octagon(Octagon&& other) noexcept {
    for (int i = 0; i < 8; ++i) {
        points[i] = std::move(other.points[i]);
    }
}
// Перегрузка перемещения.
Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 8; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Octagon::operator==(const Octagon& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
std::partial_ordering Octagon::operator<=>(const Octagon& other) const {
    return this->square() <=> other.square();
}

Point Octagon::geometric_center() const {
    double center_x = (points[0].get_x() + points[1].get_x() + points[2].get_x() + points[3].get_x() + points[4].get_x() + points[5].get_x() + points[6].get_x() + points[7].get_x()) / 8.0;
    double center_y = (points[0].get_y() + points[1].get_y() + points[2].get_y() + points[3].get_y() + points[4].get_y() + points[5].get_y() + points[6].get_y() + points[7].get_y()) / 8.0;
    return Point(center_x, center_y);
}

double Octagon::square() const {
    double l = distance(points[0], points[1]);
    double area = 4.828 * l * l; // 4.828 = 2*(1+sqrt(2))
    return area;
}

double Octagon::perimeter() const {
    double l = distance(points[0], points[1]);
    return (l * 8);
}

Octagon::operator double() const {
    return this->square();
}

void Octagon::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Octagon::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Octagon::clone() const {
    return new Octagon(this->points[0],
                        this->points[1], 
                        this->points[2], 
                        this->points[3], 
                        this->points[4], 
                        this->points[5],
                        this->points[6],
                        this->points[7]);
}