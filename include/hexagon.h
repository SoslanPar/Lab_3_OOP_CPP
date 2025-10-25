#pragma once
#include <compare>
#include <string>
#include "point.h"
#include "figure.h"

class Hexagon: public Figure{
    public:
        // Конструктор по умолчанию
        Hexagon(): Figure("hexagon") {};

        // Конструктор точками
        Hexagon(const Point& p1, 
            const Point& p2, 
            const Point& p3, 
            const Point& p4, 
            const Point& p5,
            const Point& p6, 
            std::string decription = "Hexagon");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Hexagon(const Hexagon& other);
        Hexagon& operator=(const Hexagon& other);
        // Конструктор перемещения.
        Hexagon(Hexagon&& other) noexcept;
        Hexagon& operator=(Hexagon&& other) noexcept;

        // Перегрузка оператора сравниния ==.
        bool operator==(const Hexagon& other) const;
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Hexagon& other) const;

        // Переопределение виртуальных методов базового класса.
        Point geometric_center() const override;
        double square() const override;
        double perimeter() const override;

        // Функция для нахождения площади фигуры через перегрузку оператора double().
        // Возвращает площадь фигуры.
        // Мы не используем explicit здесь, чтобы позволить неявное преобразование к double.
        operator double() const override;

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override;
        void read(std::istream& is) override;

        // Функция для клонирования фигуры.
        Figure* clone() const override;

    private:
        Point points[6];
};