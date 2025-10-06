#include <iostream>
#include <vector>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "../include/rpn.h"

using namespace std;

vector<vector<string>> reading_rpn(const string& path) {
    //Wir öffnen file
    ifstream in(path);

    //Check if it's found
    if(!in) throw runtime_error("File were found nicht");

    string line;
    vector<vector<string>> allTokens;

    //Read line by line und split each one into tokens
    while(getline(in, line)) {
        string token;
        vector<string> tokens;

        //split each line into tokens und then put them into vector of tokens
        istringstream iss(line);
        while(iss >> token) tokens.push_back(token);

        allTokens.push_back(tokens);
    }
    return allTokens;
}

void writing_rpn(const vector<vector<string>>& allTokens, const string& path) {
    //creating directory of unseren output files if not existing
    filesystem::create_directories("data/output");
    ofstream out(path);

    //writing into file
    for(auto token : allTokens) {
        string lineToken = from_token_to_string(token);
        out << lineToken << " = " << count_rpn(token) << '\n';
    }

    return;
}

string from_token_to_string(const vector<string>& token) {
    string out = " ";

    for(size_t i = 0; i < token.size(); ++i) {
        if(i) out += ' ';
        out += token[i];
    }

    return out;
}

//Die Idee ist that we use stack, put every numbers there und if we face with operator
//we pop zwei last numbers und use operator we faced with und afterall we put it in stack
//und dieses algorithm must lead(if input data are correct) to one-element stack that would be our result
int count_rpn(const vector<string>& tokens) {
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

    if(stack.size() != 1) throw runtime_error("Not enough amount of operators or operands");

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