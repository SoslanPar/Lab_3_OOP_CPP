#include <iostream>
#include <sstream>
#include <utility>
#include "include/point.h"
#include "include/figure.h"
#include "include/array_of_figures.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/octagon.h"


int main() {
    using std::cout;
    using std::endl;

    // --- Точки ---
    Point p1(0.0, 0.0);
    Point p2(0.0, 3.0);
    Point p3(2.5, 4.0);
    Point p4(5.0, 3.0);
    Point p5(5.0, 0.0);
    Point p6(2.5, 4.0);
    Point p7(5.0, 3.0);
    Point p8(5.0, 0.0);

    cout << "Точки: " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << endl;
    cout << "Расстояние между p1 и p3: " << distance(Point(0, 1), Point(-1, 0)) << endl;

    // --- Тесты пятиугольника ---
    Pentagon pentagon1(p1, p2, p3, p4, p5); // задаём по точкам
    cout << "Пятиугольник pentagon1:" << endl << pentagon1 << endl;
    cout << "  центр: " << pentagon1.geometric_center() << endl;
    cout << "  площадь: " << pentagon1.square() << " периметр: " << pentagon1.perimeter() << endl;
    cout << "  приведение к double (площадь): " << static_cast<double>(pentagon1) << endl;
    cout << "  pentagon1 == pentagon1: " << std::boolalpha << (pentagon1 == pentagon1) << endl;

    // Пятиугольник по умолчанию + чтение из потока
    Pentagon pentagon2; // предполагается, что есть конструктор по умолчанию
    std::istringstream rin("(0,0) (3,0) (3,4) (0,4)");
    rin >> pentagon2; // читаем 4 точки
    cout << "Прямоугольник pentagon2 (прочитан):" << endl << pentagon2 << endl;
    cout << "  pentagon1 == pentagon2 (площади равны?): " << std::boolalpha << (pentagon1 == pentagon2) << endl;

    // --- Шетсиугольник и Восьмиугольник ---
    Hexagon hexagon1(p1, p2, p3, p4, p5, p6);
    cout << "Шестиугольник hexagon1:" << endl << hexagon1 << endl;
    cout << "  площадь hexagon1: " << hexagon1.square() << " периметр: " << hexagon1.perimeter() << endl;

    Octagon octagon1(p1, p2, p3, p4, p5, p6, p7, p8);
    cout << "Восьмиугольник octagon1:" << endl << octagon1 << endl;
    cout << "  площадь octagon1: " << octagon1.square() << " периметр: " << octagon1.perimeter() << endl;

    // --- Тест clone() ---
    Figure* pentagon_clone = pentagon1.clone();
    Figure* hexagon_clone = hexagon1.clone();
    Figure* octagon_clone = octagon1.clone();
    cout << "Клонированные фигуры:" << endl;
    cout << *pentagon_clone << endl << *hexagon_clone << endl << *octagon_clone << endl;
    delete pentagon_clone; delete hexagon_clone; delete octagon_clone;

    // --- Тесты Array_Of_Figures: add / print / total / remove ---
    Array_Of_Figures arr(2);
    arr.add_figure(pentagon1.clone());
    arr.add_figure(hexagon1.clone());
    arr.add_figure(octagon1.clone()); // должен сработать resize массива
    cout << "Массив после добавления (size=" << arr.get_size() << ", cap=" << arr.get_capacity() << "):" << endl;
    arr.print_figures(std::cout);
    cout << "Общая площадь: " << arr.total_square() << endl;

    // копирование
    Array_Of_Figures arr_copy = arr;
    cout << "Скопированный массив (size=" << arr_copy.get_size() << "):" << endl;
    arr_copy.print_figures(std::cout);

    // перемещение
    Array_Of_Figures arr_moved = std::move(arr);
    cout << "Перемещённый массив (новый владелец size=" << arr_moved.get_size()
         << "), исходный размер=" << arr.get_size() << endl;
    arr_moved.print_figures(std::cout);

    // оператор присваивания (копирование)
    Array_Of_Figures arr_assign(1);
    arr_assign = arr_copy;
    cout << "После copy-assignment arr_assign size=" << arr_assign.get_size() << endl;

    // оператор присваивания (перемещение)
    Array_Of_Figures arr_move_assign(1);
    arr_move_assign = std::move(arr_copy);
    cout << "После move-assignment arr_move_assign size=" << arr_move_assign.get_size()
         << ", arr_copy size=" << arr_copy.get_size() << endl;

    // доступ через operator[] и удаление элемента
    if (arr_moved.get_size() > 0) {
        Figure* f0 = arr_moved[0];
        cout << "Первый элемент arr_moved через operator[]:" << endl;
        if (f0) cout << *f0 << endl;
    }
    if (arr_moved.get_size() > 1) {
        cout << "Удаляем элемент с индексом 1 из arr_moved" << endl;
        arr_moved.remove_figure(1);
        cout << "После удаления, размер=" << arr_moved.get_size() << endl;
        arr_moved.print_figures(std::cout);
    }

    cout << "Все проверки завершены." << endl;
    return 0;
}