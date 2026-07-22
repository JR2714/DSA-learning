// Receive strings, sort them in dictionary order, and count the number of different words.

#include <iostream>
#include <set>
#include <string>

int main() {
    std::set<std::string> words;
    std::cout << "Input the strings, end with END.\n";
    std::string word;
    std::cin >> word;
    while(word != "END") {
        words.insert(word);
        std::cin >> word;
    }
    for(const auto& s : words) {
        std::cout << s << "\n";
    }
    std::cout << "The number of the different words is " << words.size() << ".\n";
}