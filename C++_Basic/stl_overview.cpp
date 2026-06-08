#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>

int main()
{
    //1.写一个向量并排序输出
    std::vector<int> vec = {2, 7, 1, 8, 2};
    std::sort(vec.begin(), vec.end());
    std::cout << "[";
    for(size_t i = 0; i < vec.size(); i++)
    {
        if (i != vec.size() - 1)
        {
            std::cout << vec[i] << ", ";
        }
        else
        {
            std::cout << vec[i] << "]\n";
        }
    }
    //2.Base-Range for
    for(const int& x : vec)
    {
        std::cout << x << "\n";
    }
    //3.map的使用
    std::map<std::string, int> ages;
    ages["Jacob"] = 22;
    ages["Judy"] = 23;
    ages["David"] = 24;
    for(const auto& [k,v] : ages) //结构化绑定，尚不熟悉
    {
        std::cout << "Name: " << k << " -> " << "Age: " << v << "\n"; 
    }
    //4.算法 + lambda
    std::sort(vec.begin(), vec.end(), [](int a, int b)
    {
        return a > b;
    });
    for(const auto& x : vec)
    {
        std::cout << x << "\n";
    }
    //5.综合
    std::vector<int> vec_1;
    std::cout << "依次输入5个数：\n";
    for(int i = 0; i <5; i++)
    {
        int value;
        std::cin >> value;
        vec_1.push_back(value);
    }
    std::set<int> vec_1_unq(vec_1.begin(), vec_1.end());
    for(const int& x : vec_1_unq)
    {
        std::cout << x << "\n";
    }
    //下面再用sort + unique 写一次
    std::vector<int> vec_2;
    std::cout << "依次输入5个数：\n";
    for(int i = 0; i <5; i++)
    {
        int value;
        std::cin >> value;
        vec_2.push_back(value);
    }
    std::sort(vec_2.begin(), vec_2.end());
    auto it = std::unique(vec_2.begin(), vec_2.end());
    vec_2.erase(it, vec_2.end());
    for(const int& x : vec_2)
    {
        std::cout << x << "\n";
    }
    //后一种做法需要注意的是，由于unique只去除临近相同的东西的指针，所以要先排序，
    //且在unique之后还要擦除erase。

    return 0;
}