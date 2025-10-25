#pragma once

#include "figure.h"
#include <cstddef>
#include <iostream>

class Array_Of_Figures{
    public:
        // Конструктор по умолчанию.
        Array_Of_Figures() = default;

        // Конструктор с параметром размера массива.
        Array_Of_Figures(size_t capacity);

        // Конструктор с инициализацией из initializer списка в котором фигуры.
        Array_Of_Figures(std::initializer_list<Figure*> list);

        // Конструктор перемещения.
        Array_Of_Figures(Array_Of_Figures&& other) noexcept;

        // Конструктор копирования.
        Array_Of_Figures(const Array_Of_Figures& other);

        // Оператор присваивания.
        Array_Of_Figures& operator=(const Array_Of_Figures& other);
        // Оператор перемещения.
        Array_Of_Figures& operator=(Array_Of_Figures&& other) noexcept;

        // Деструктор.
        ~Array_Of_Figures();

        // Функция для добавления фигуры в массив.
        void add_figure(Figure* figure);

        // Перегрузка оператора индексации для доступа к фигурам в массиве.
        // Необходимо реализовать перегрузку метода для const, и для non-const версий.
        // Возвращаемый тип - указатель на Figure (не const), чтобы можно было изменять фигуры.
        Figure*& operator[](size_t index);
        // Const версия оператора индексации.
        // Возвращает копию указателя на Figure, чтобы предотвратить изменение фигур.
        Figure* operator[](size_t index) const;

        // Функция для удаления фигуры из массива по индексу.
        void remove_figure(size_t index);

        // Получение текущего размера массива.
        size_t get_size() const;

        // Получение текущей емкости массива.
        size_t get_capacity() const;

        // Функция для вывода всех фигур в массиве.
        void print_figures(std::ostream& os) const;

        // Функция для нахождения общей площади всех фигур в массиве.
        double total_square() const;

        private:
            // Динамический массив указателей на фигуры.
            Figure** figures{nullptr};
            // Текущий размер массива.
            size_t size{0};
            // Текущая емкость массива.
            size_t capacity{0};
            // Функция для изменения размера массива.
            void resize();

            // Метод для обмена ресурсами между двумя объектами класса Array_Of_Figures.
            void swap(Array_Of_Figures& other) noexcept;

};