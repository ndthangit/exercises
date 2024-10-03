#include <iostream>
#include <string>
#include <cctype>

int countWords(const std::string& text) {
    int wordCount = 0;
    bool inWord = false;
    for (char c : text) {
        if (!std::isspace(c)) {
            if (!inWord) {
                inWord = true;
                wordCount++;
            }
        } else {
            inWord = false;
        }
    }
    return wordCount;
}

int main() {
    std::string inputText;
    std::getline(std::cin, inputText);
    int wordCount = countWords(inputText);
    std::cout << wordCount << std::endl;
    return 0;
}
