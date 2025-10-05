#include <iostream>
#include <vector>
#include <vector>
#include <cmath>
#include <fstream>
#include "../include/rpn.h"

using namespace std;

int count_rpn(vector<string> tokens) {
    vector<int> stack = vector<int>();
    for(string token : tokens) {
        if(is_number(token)) {
            size_t pos = 0;
            int number = stoi(token, &pos, 10);
            stack.push_back(number);
        }
        else if(is_operator(token)) {
            if(stack.size() < 2) throw runtime_error("Cannot produce operation with one or zero operands");

            char oper = token[0];
            int secondNumber = stack.back();
            stack.pop_back();
            int firstNumber = stack.back();
            stack.pop_back();

            int result;
            switch(oper) {
                case '+': result = firstNumber + secondNumber; break;
                case '-': result = firstNumber - secondNumber; break;
                case '*': result = firstNumber * secondNumber; break;
                case '/': 
                    if(secondNumber == 0) throw runtime_error("division by zero");
                    if(firstNumber % secondNumber != 0) throw runtime_error("unavaliable division");
                    result = firstNumber / secondNumber;
                    break;
            }

            stack.push_back(result);

        }
        else throw runtime_error("Token: \"" + token + "\" isn't neither operator nor a number");
    }

    if(stack.size() == 1) cout << stack.back() << endl;
    else throw runtime_error("Not enough amount of operators or operands");

    return stack.back();
}

bool is_operator(const string& token) {
    return token.size() == 1 && (token[0] == '+' || token[0] == '*' || token[0] == '/' || token[0] == '-');
}

bool is_number(const string& token) {
    if(token.empty()) return false;

    for(char digit : token) {
        if( !(digit >= '0' && digit <= '9') ) return false;
    }
    
    return true;
}