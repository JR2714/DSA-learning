#include <iostream>

//数二进制数中“1”的个数
int numOfOne(unsigned int N) {
    if (N == 0)
        return 0;
    return numOfOne(N / 2) + (N % 2);
}

int main() {
    std::cout << numOfOne(2) << std::endl;
}