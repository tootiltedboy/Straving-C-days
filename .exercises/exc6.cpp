/*Simple password verification programme. Each password must be from 8 to 14 symbols,
and at least 3 out of 4 special symbol groups */
#include <iostream>
#include <string>
bool Verificate(const std::string& password) {
    if (password.size() < 8 || password.size() > 14) {
        return false;
    }
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int other = 0;

    for (char c : password) {
        if (c < 33 || c > 126) {
            return false;
        }
        if ('A' <= c && c <= 'Z') {
            upper = 1;
        }
        else if ('a' <= c && c<= 'z') {
            lower = 1;
        }
        else if ('0' <= c && c<= '9') {
            digit = 1;
        }
        else {
            other = 1;
        }
    }
    return upper+lower+digit+other >= 3;
}
int main() {
    std::string password;
    std::cout << "Please enter your password:\n";
    std::getline(std::cin, password);
    if (Verificate(password)) {
        std::cout << "Password verified and accepted" << std::endl;
    }
    else {
        std::cout << "Wrong password\n" << "Please try again later" << std::endl;
    }
}
