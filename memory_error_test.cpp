#include <iostream>
#include <cstring>

int main() {
    char* buffer = new char[5];
    std::strcpy(buffer, "Hello, AddressSanitizer!");
    std::cout << buffer << std::endl;
    // delete[] buffer;
    return 0;
}
