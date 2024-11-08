#include <iostream>
#include <cmath>
#include <vector>

class Point {
public:
    double x, y;

    Point(double xCoord = 0, double yCoord = 0) : x(xCoord), y(yCoord) {}

    double distanceTo(const Point& other) const {
        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    void input() {
        std::cout << "Введите координаты точки (x y): ";
        std::cin >> x >> y;
    }
};

class Line {
public:
    Point start, end;
    double length;

    Line(const Point& p1 = Point(), const Point& p2 = Point()) : start(p1), end(p2) {
        length = start.distanceTo(end);
    }

    Point midpoint() const {
        return Point((start.x + end.x) / 2, (start.y + end.y) / 2);
    }

    void input() {
        std::cout << "Введите координаты начала линии (x1 y1): ";
        start.input();
        std::cout << "Введите координаты конца линии (x2 y2): ";
        end.input();
        length = start.distanceTo(end);
    }
};

class Triangle {
public:
    Point p1, p2, p3;
    double area;
    Line side1, side2, side3;

    Triangle(const Point& point1 = Point(), const Point& point2 = Point(), const Point& point3 = Point())
        : p1(point1), p2(point2), p3(point3),
          side1(point1, point2), side2(point2, point3), side3(point3, point1) {
        calculateArea();
    }

    void calculateArea() {
        double s = (side1.length + side2.length + side3.length) / 2.0;
        area = std::sqrt(s * (s - side1.length) * (s - side2.length) * (s - side3.length));
    }

    Point centroid() const {
        return Point((p1.x + p2.x + p3.x) / 3, (p1.y + p2.y + p3.y) / 3);
    }

    void input() {
        std::cout << "Введите координаты первой вершины треугольника (x1 y1): ";
        p1.input();
        std::cout << "Введите координаты второй вершины треугольника (x2 y2): ";
        p2.input();
        std::cout << "Введите координаты третьей вершины треугольника (x3 y3): ";
        p3.input();
        side1 = Line(p1, p2);
        side2 = Line(p2, p3);
        side3 = Line(p3, p1);
        calculateArea();
    }
};

class Ruler {
public:

    double measureDistance(const Point& p1, const Point& p2) {
        return p1.distanceTo(p2);
    }

    double measureDistance(const Point& p, const Line& l) {
        return p.distanceTo(l.midpoint());
    }

    double measureDistance(const Point& p, const Triangle& t) {
        return p.distanceTo(t.centroid());
    }

    double measureDistance(const Line& l1, const Line& l2) {
        return l1.midpoint().distanceTo(l2.midpoint());
    }

    double measureDistance(const Line& l, const Triangle& t) {
        return l.midpoint().distanceTo(t.centroid());
    }

    double measureDistance(const Triangle& t1, const Triangle& t2) {
        return t1.centroid().distanceTo(t2.centroid());
    }
};

int main() {
    Point p1, p2, p3, p4;
    Line line1, line2;
    Triangle triangle;

    std::cout << "Ввод точки p1:" << std::endl;
    p1.input();
    std::cout << "\nВвод точки p2:" << std::endl;
    p2.input();

    std::cout << "\nВвод линии 1:" << std::endl;
    line1.input();

    std::cout << "\nВвод треугольника:" << std::endl;
    triangle.input();

    Ruler ruler;

    std::cout << "\nРасстояние между точками p1 и p2: " << ruler.measureDistance(p1, p2) << std::endl;
    std::cout << "Расстояние между точкой p1 и серединой первой линии: " << ruler.measureDistance(p1, line1) << std::endl;
    std::cout << "Расстояние между точкой p1 и центром треугольника: " << ruler.measureDistance(p1, triangle) << std::endl;

    std::cout << "\nВвод линии 2:" << std::endl;
    line2.input();
    std::cout << "Расстояние между линиями: " << ruler.measureDistance(line1, line2) << std::endl;
    std::cout << "Расстояние между линией и центром треугольника: " << ruler.measureDistance(line1, triangle) << std::endl;

    return 0;
}