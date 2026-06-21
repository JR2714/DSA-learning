#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>   // for std::invalid_argument, std::out_of_range
using std::string;
using std::stack;
using std::istringstream;

int evalPostfix(const string& expr) {
    stack<int> s;
    istringstream iss(expr);
    string token;

    while(iss >> token) {
        if(token == "+" || token == "-" || token == "*" || token == "/") {
            if(s.size() < 2) { // 检查栈中是否有两个元素
                throw std::runtime_error("后缀表达式格式错误：操作数不足！");
            }
            // 取出操作数
            int rhs = s.top(); s.pop();
            int lhs = s.top(); s.pop();
            // 运算并放结果回栈
            if(token == "+") s.push(lhs + rhs);
            else if(token == "-") s.push(lhs - rhs);
            else if(token == "*") s.push(lhs * rhs);
            else if(token == "/") {
                if(rhs == 0) {
                    throw std::runtime_error("除零错误！");
                }
                s.push(lhs / rhs);
            }
        } else {
            // 尝试将token转化为int写入栈中
            try {
                // 使用 std::stoi 转换，并检查是否完全消耗（防止 "123abc" 被误读）
                size_t pos;
                int num = std::stoi(token, &pos);
                // 如果 pos != token.size()，说明 token 中含有非数字后缀，如 "123abc"
                if (pos != token.size()) {
                    throw std::invalid_argument("含非数字字符");
                }
                s.push(num);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("无效的 token: " + token);
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("数字超出 int 范围: " + token);
            }
        }
    }

    // 最终栈中应只剩一个结果
    if (s.size() != 1) {
        throw std::runtime_error("后缀表达式格式错误：操作数过多或运算符不足");
    }
    
    return s.top();
}

// 测试用
#include <iostream>
int main() {
    auto test = [](const char* name, const std::string& expr, int expected) {
        try {
            int result = evalPostfix(expr);
            std::cout << name << ": " << expr << " = " << result
                      << (result == expected ? " ✓" : " ✗ (expected " + std::to_string(expected) + ")")
                      << std::endl;
        } catch (const std::exception& e) {
            std::cout << name << ": " << expr << " → ERROR: " << e.what() << std::endl;
        }
    };

    test("Weiss示例", "6 5 2 3 + 8 * + 3 + *", 288);
    test("简单1  ", "3 4 + 5 *", 35);
    test("简单2  ", "3 4 5 + *", 27);
    test("除法   ", "10 3 /", 3);
    test("减法   ", "10 3 -", 7);
    test("负数   ", "-5 3 *", -15);
    test("除零   ", "5 0 /", 0);  // 预期抛异常

    return 0;
}