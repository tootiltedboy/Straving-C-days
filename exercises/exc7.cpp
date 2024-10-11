//This programme was made to perform output for the digits of the number
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;


int main(int argc, char const *argv[]) {
    vector<string> names  {"Первая", "Вторая", "Третья", "Четвертая", "Пятая"};
    unsigned int number;
    cout << "Введите пятизначное число: ";
    cin >> number;
    string s_number = std::to_string(number);
    if (s_number.size() > names.size()) {
        cout << "Ошибка! Максимальное кол-во чисел в числе: " << names.size() << '\n';
        return -1;
    }
    for (size_t i = 0; i < s_number.size(); i++) {
        this_thread::sleep_for(500ms);
        cout << names[i] << " цифра числа: " << s_number[i] << '\n';
    }
    return 0;
}
