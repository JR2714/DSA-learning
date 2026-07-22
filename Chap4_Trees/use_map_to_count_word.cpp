#include <iostream>
#include <map>
#include <string>
int main() {
    // Count the number of times each word appears in a piece of text.
    std::map<std::string, int> count_map;
    std::cout << "Input the words end with END.\n";
    std::string word;
    std::cin >> word;
    while(word != "END") {
        ++count_map[word];
        std::cin >> word;
    }
    for(const auto& p : count_map) {
        std::cout << p.first << " " << p.second << "\n";
    }
    
    // Compare find and [] in map.
    std::map<std::string, int> temp;
    temp.insert({"Leclerc", 100});
    std::cout << temp["Verstappen"] << "\n"; // This will insert a key "Max" with value 0.
    temp.find("Kimi"); // This won't creat a new item in the map.
    for(const auto& p : temp) {
        std::cout << p.first << " " << p.second << "\n";
    }
}