#include <iostream>
#include <iomanip> // Thư viện định dạng

int main() {
    std::cout << std::roght;  // Canh trái
    std::cout << std::setw(15) << "Ten"
              << std::setw(10) << "Tuoi"
              << std::setw(20) << "dia chi" << std::endl;

//    std::cout << std::setfill('');  // Dùng ký tự '-' lấp đầy
    std::cout << std::setw(15) << "Nguyen Van A"
              << std::setw(10) << 25
              << std::setw(20) << "Ha Noi" << std::endl;

    std::cout << std::setw(15) << "Le Thi B"
              << std::setw(10) << 30
              << std::setw(20) << "TP. HCM" << std::endl;

    return 0;
}
