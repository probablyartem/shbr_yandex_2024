#include <iostream>
#include <vector>
#include <regex>


int main() {
    std::string word;
    std::cin >> word;

    std::string commands;
    std::cin >> commands;

    std::vector<char> left;
    std::vector<char> right;

    std::regex pattern("<delete>|<bspace>|<left>|<right>|[a-z]");
    auto words_begin = std::sregex_iterator(commands.begin(), commands.end(), pattern);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator it = words_begin; it != words_end; ++it) {
        std::string match = it->str();
        if (match == "<delete>") {
            if (!right.empty())
                right.pop_back();
        } else if (match == "<bspace>") {
            if (!left.empty())
                left.pop_back();
        } else if (match == "<left>") {
            if (!left.empty()) {
                right.push_back(left.back());
                left.pop_back();
            }
        } else if (match == "<right>") {
            if (!right.empty()) {
                left.push_back(right.back());
                right.pop_back();
            }
        } else {
            left.push_back(match[0]);
        }
    }

    std::string result(left.begin(), left.end());
    result += std::string(right.rbegin(), right.rend());

    std::cout << (word == result ? "Yes" : "No");

    return 0;
}
