#pragma once
#include <string>

bool is_correct_parenthesis_sequences(const std::string &s) {
    int cnt = 0;
    for (char c : s) {
        if (c == '(') ++cnt;
        else if (cnt == 0) return false;
        else --cnt;
    }
    return cnt == 0;
}
