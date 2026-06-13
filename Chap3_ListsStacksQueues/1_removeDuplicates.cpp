#include <iostream>
#include <vector>
#include <list>

template <typename Container>
void removeDuplicates(Container& lst) {
    for(auto current = lst.begin(); current != lst.end(); current++) {
        for(auto scanner = std::next(current, 1); scanner != lst.end(); ) {
            if(*current == *scanner)
               scanner = lst.erase(scanner);
            else
                scanner++;
        }
    }
}

int main() {
    std::vector<int> v = {1, 1, 3, 2, 4, 4};
    std::list<int> l = {1, 1, 2, 3, 4, 4};
    removeDuplicates(v);
    removeDuplicates(l);
    for(const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    for(const auto& elem : l) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}