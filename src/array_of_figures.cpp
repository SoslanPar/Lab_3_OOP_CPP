#include <initializer_list>
#include <iostream>
#include "../include/array_of_figures.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

// Конструктор с параметром размера массива.
Array_Of_Figures::Array_Of_Figures(size_t cap){
    size = 0;
    capacity = (cap == 0) ? 1 : (cap * 2);
    figures = new Figure*[capacity];
    std::fill_n(figures, capacity, nullptr);
}

// Конструктор с инициализацией из initializer списка в котором фигуры.
Array_Of_Figures::Array_Of_Figures(std::initializer_list<Figure*> list) {
    size = list.size();
    capacity = (size == 0) ? 1 : (size * 2);
    figures = new Figure*[capacity];
    std::fill_n(figures, capacity, nullptr);
    // Глубокое копирование указателей из списка в массив.
    std::transform(list.begin(), list.end(), figures,
                   [](Figure* fig) { return (fig ? fig->clone() : nullptr); });
}

// Конструктор перемещения.
Array_Of_Figures::Array_Of_Figures(Array_Of_Figures&& other) noexcept
    : figures(other.figures), size(other.size), capacity(other.capacity) {
    other.figures = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Конструктор копирования (глубокое копирование).
Array_Of_Figures::Array_Of_Figures(const Array_Of_Figures& other) {
    size = other.size;
    capacity = other.capacity;
    figures = new Figure*[capacity];
    std::fill_n(figures, capacity, nullptr);
    for (size_t i = 0; i < size; ++i) {
        figures[i] = other.figures[i] ? other.figures[i]->clone() : nullptr;
    }
}

// Оператор присваивания.
Array_Of_Figures& Array_Of_Figures::operator=(const Array_Of_Figures& other) {
    if (this == &other) return *this;
    Array_Of_Figures temp(other); // Используем конструктор копирования.
    swap(temp); // Обмениваемся ресурсами с временным объектом.
    return *this;
}

// Оператор перемещения.
Array_Of_Figures& Array_Of_Figures::operator=(Array_Of_Figures&& other) noexcept {
    if (this == &other) return *this;
    // Освобождаем текущие ресурсы.
    for (size_t i = 0; i < size; ++i) {
        delete figures[i];
    }
    delete[] figures;
    // Перемещаем ресурсы из другого объекта.
    figures = other.figures;
    size = other.size;
    capacity = other.capacity;
    // Обнуляем другой объект.
    other.figures = nullptr;
    other.size = 0;
    other.capacity = 0;
    return *this;
}

// Swap метод для обмена ресурсами между двумя объектами.
void Array_Of_Figures::swap(Array_Of_Figures& other) noexcept {
    std::swap(figures, other.figures);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}



// Деструктор.
Array_Of_Figures::~Array_Of_Figures() {
    for (size_t i = 0; i < size; ++i) {
        delete figures[i]; // Освобождение памяти под каждую фигуру.
    }
    delete[] figures; // Освобождение памяти под массив указателей.
}

// Функция для добавления фигуры в массив.
void Array_Of_Figures::add_figure(Figure* figure) {
    if (size >= capacity) {
        resize();
    }
    figures[size++] = figure;
}

// Перегрузка оператора индексации для доступа к фигурам в массиве.
Figure* Array_Of_Figures::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return figures[index];
}

Figure*& Array_Of_Figures::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return figures[index];
}

// Функция для удаления фигуры из массива по индексу.
void Array_Of_Figures::remove_figure(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete figures[index]; // Освобождение памяти под фигуру.
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1]; // Сдвиг элементов влево.
    }
    --size;
    if (size >= 0) figures[size] = nullptr; // Обнуляем последний элемент.
}

// Получение текущего размера массива.
size_t Array_Of_Figures::get_size() const {
    return size;
}

// Получение текущей емкости массива.
size_t Array_Of_Figures::get_capacity() const {
    return capacity;
}

// Функция для вывода всех фигур в массиве.
void Array_Of_Figures::print_figures(std::ostream& os) const {
    for (size_t i = 0; i < size; ++i) {
        if (figures[i]) {
            os << *figures[i] << std::endl;
        } 
    }
}

// Функция для нахождения общей площади всех фигур в массиве.
double Array_Of_Figures::total_square() const {
    double total = 0.0;
    for (size_t i = 0; i < size; ++i) {
        if (figures[i]) {
            // Используется неявное преобразование к double через перегруженный оператор.
            // total += *figures[i]; Так тоже работает(так как при сложении к double происходит неявное(само) преобразование фигуры в double), но ниже будет быолее явно, с помощью функции square().
            total += figures[i]->square();
        }
    }
    return total;
}

// Функция для изменения размера массива.
void Array_Of_Figures::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    Figure** new_figures = new Figure*[capacity];
    std::fill_n(new_figures, capacity, nullptr);
    for (size_t i = 0; i < size; ++i) {
        new_figures[i] = figures[i];
    }
    delete[] figures;
    figures = new_figures;
}