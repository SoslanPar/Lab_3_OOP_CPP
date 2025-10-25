#pragma once
#include <compare>
#include <string>
#include "point.h"
#include "figure.h"

class Pentagon: public Figure{
    public:
        // Конструктор по умолчанию
        Pentagon(): Figure("pentagon") {};

        // Конструктор точками
        Pentagon(const Point& p1,
             const Point& p2, 
             const Point& p3, 
             const Point& p4, 
             const Point& p5, 
             std::string decription = "pentagon");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Pentagon(const Pentagon& other);
        Pentagon& operator=(const Pentagon& other);
        // Конструктор перемещения.
        Pentagon(Pentagon&& other) noexcept;
        Pentagon& operator=(Pentagon&& other) noexcept;

        // Перегрузка оператора сравниния ==.
        bool operator==(const Pentagon& other) const;
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Pentagon& other) const;

        // Переопределение виртуальных методов базового класса.
        Point geometric_center() const override;
        double square() const override;
        double perimeter() const override;

        // Функция для нахождения площади фигуры через перегрузку оператора double().
        // Возвращает площадь фигуры.
        // Мы не используем explicit здесь, чтобы позволить неявное преобразование к double. (можно без static_cast)
        operator double() const override;

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override;
        void read(std::istream& is) override;

        // Функция для клонирования фигуры.
        Figure* clone() const override;

    private:
        Point points[5];

};
