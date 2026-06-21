#include <string>
#include <stack>
using std::string;
using std::stack;

bool isBalanced(const string& expr) {
    stack<char> s;
    for(const char t : expr) {
        if(t != '(' && t != ')' && t != '[' && t != ']' && t != '{' && t != '}') {
            continue;
        }
        if(t == '(' || t == '[' || t == '{') {
            s.push(t);
        } else if(!s.empty() && t == ')' && s.top() == '(') {
            s.pop();
        } else if(!s.empty() && t == ']' && s.top() == '[') {
            s.pop();
        } else if(!s.empty() && t == '}' && s.top() == '{') {
            s.pop();
        } else {
            return false;
        }
    }
    return s.empty();
}

// 测试用
#include <iostream>
int main() {
    auto test = [](const char* name, const std::string& expr, bool expected) {
        bool result = isBalanced(expr);
        std::cout << name << ": " << expr << " → " << (result ? "true" : "false")
                  << (result == expected ? " ✓" : " ✗ (expected " + std::string(expected ? "true" : "false") + ")")
                  << std::endl;
    };

    test("简单平衡", "{[()]}", true);
    test("交叉错误", "{[(])}", false);
    test("代码片段", "if (a[0] > 0) { return a[0]; }", true);
    test("只有开括号", "(", false);
    test("只有闭括号", ")", false);
    test("空字符串", "", true);
    test("多层嵌套", "((([])))", true);
    test("三种括号", "()[]{}", true);

    return 0;
}