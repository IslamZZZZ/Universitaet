#pragma once
#include <vector>
#include <string>

std::vector<std::vector<std::string>> reading_rpn(const std::string& path = "data/input/input.txt");

void writing_rpn(const std::vector<std::vector<std::string>>& allTokens,
     const std::string& path = "data/output/output.txt");

std::string from_token_to_string(const std::vector<std::string>& token);

int count_rpn(const std::vector<std::string>& tokens);

bool is_operator(const std::string& token);

bool is_number(const std::string& token);