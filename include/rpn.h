#pragma once
#include <vector>
#include <string>

int count_rpn(std::vector<std::string> tokens);

bool is_operator(const std::string& token);

bool is_number(const std::string& token);