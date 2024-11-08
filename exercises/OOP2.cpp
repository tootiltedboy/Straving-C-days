#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateArea() const override {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() const override {
        return 2 * M_PI * radius;
    }

    ~Circle() override {}
};

class Rectangle : public Shape {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double calculateArea() const override {
        return length * width;
    }

    double calculatePerimeter() const override {
        return 2 * (length + width);
    }

    ~Rectangle() override {}
};

class Triangle : public Shape {
private:
    double side1, side2, side3;
public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}

    double calculateArea() const override {
        double s = (side1 + side2 + side3) / 2.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double calculatePerimeter() const override {
        return side1 + side2 + side3;
    }

    ~Triangle() override {}
};

int main() {
    double radius;
    cout << "Введите радиус окружности: ";
    cin >> radius;
    Shape* circle = new Circle(radius);
    cout << "Площадь круга равна: " << circle->calculateArea() << endl;
    cout << "Длинна окружности равна: " << circle->calculatePerimeter() << endl;
    delete circle;

    double length, width;
    cout << "Введите длинну прямоугольника: " << endl;
    cin >> length;
    cout << "Введите ширину прямоугольника: " << endl;
    cin >> width;
    Shape* rectangle = new Rectangle(length, width);
    cout << "Площадь прямоугольника равна: " << rectangle->calculateArea() << endl;
    cout << "Периметр прямоугольника равен: " << rectangle->calculatePerimeter() << endl;
    delete rectangle;

    double side1, side2, side3;
    cout << "Введите длину первой стороны: " << endl;
    cin >> side1;
    cout << "Введите длину второй стороны: " << endl;
    cin >> side2;
    cout << "Введите длину третьей стороны: " << endl;
    cin >> side3;
    Shape* triangle = new Triangle(side1, side2, side3);
    cout << "Площадь треугольника равна: " << triangle->calculateArea() << endl;
    cout << "Периметр треугольника равен: " << triangle->calculatePerimeter() << endl;
    delete triangle;

    return 0;
}