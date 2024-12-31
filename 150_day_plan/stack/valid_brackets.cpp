#include "iostream"
#include <vector>

using namespace std;

int main() {
       bool valid = true;
       vector<char> brackets;
       char close_bracket;
    for (char bracket : s) {
        if (bracket == '{' || bracket == '(' || bracket == '[') {
            brackets.push_back(bracket);
        }
        else if (brackets.size() && (bracket == '}' || bracket == ')' || bracket == ']')) {
            close_bracket = brackets.back();
            brackets.pop_back();
            if (bracket == ')') {
                valid = (close_bracket == '(') ? true : false;
            }
            else if (bracket == '}') {
                valid = (close_bracket == '{') ? true : false;
            }
            else if (bracket == ']') {
                valid = (close_bracket == '[') ? true : false;
            }
            else {
                valid = false;
            }
            if (!valid)
                break;
        }
        else {
            return false;
        }
    }
    if (brackets.size()) {
        cout << brackets.size() << endl;
        return false;
    }
       cout << valid;
       return 0;
}

