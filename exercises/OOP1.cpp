#include <iostream>
constexpr double pi = 3.141592653589793;
using namespace std;

class Circle {
public:
    double radius;
    double calc() {
        double circ =2*pi*radius;
        double square =pi*pow(radius,2);
        cout << "Длина окружности = " << circ << endl;
        cout << "Площать окружности = " << square << endl;
        return 0;
    }
};

int main() {
    Circle circle;
    cout << "Введите радиус окружности: ";
    cin >>circle.radius;
    circle.calc();
    return 0;
}