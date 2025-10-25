#pragma once
#include <compare>
#include <string>
#include "point.h"
#include "figure.h"

class Octagon: public Figure{
    public:
        // Конструктор по умолчанию
        Octagon(): Figure("octagon") {};

        // Конструктор точками
        Octagon(const Point& p1,
            const Point& p2, 
            const Point& p3, 
            const Point& p4, 
            const Point& p5, 
            const Point& p6, 
            const Point& p7, 
            const Point& p8, std::string decription = "Octagon");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Octagon(const Octagon& other);
        Octagon& operator=(const Octagon& other);
        // Конструктор перемещения.
        Octagon(Octagon&& other) noexcept;
        Octagon& operator=(Octagon&& other) noexcept;

        // Перегрузка оператора сравниния ==.
        bool operator==(const Octagon& other) const;
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Octagon& other) const;

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
        Point points[8];
};