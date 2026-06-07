# include <iostream>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int sum_array(const int* arr, size_t n) {
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += *(arr + i);
    }
    return sum;
}

void reverse_array(int* arr, size_t n) {
    for (size_t i = 0; i < n - 1 - i; i++) {
        int temp = *(arr + i);
        *(arr + i) = *(arr + n - 1 - i);
        *(arr + n - 1 - i) = temp;
    }
}

int main() {
    int a = 1;
    int b = 2;
    int* p = &a;
    int* q = &b;
    swap(p, q);
    std::cout << "第一题：\n";
    std::cout << "p指向" << *p << std::endl 
              << "q指向" << *q << std::endl;
    
    std::cout << "第二题：\n";
    int arr[4] = {1,3,5,3};
    std::cout << sum_array(arr, 4) << std::endl;

    std::cout << "第三题：\n";
    reverse_array(arr, 4);
    std::cout << "[";
    for (size_t i = 0; i < std::size(arr); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]" << std::endl;

}