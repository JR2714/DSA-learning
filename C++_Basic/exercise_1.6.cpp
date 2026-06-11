#include <iostream>
#include <string>
#include <utility>  // for std::swap
using std::string;
using std::swap;
using std::cout;

void permute(string& str, int low, int high) {
    if(low == high)
        cout << str << std::endl;
    else {
        for(int i = low; i <= high; i++) {
            swap(str[low], str[i]);
            permute(str, low + 1, high);
            swap(str[low], str[i]);
        }
    }
}

void permute(const string& str) {
    if (str.size() != 0) {
        string s = str;
        permute(s, 0, s.size() - 1);
    }
}

int main() {
    string str = "abc";
    permute(str);
}