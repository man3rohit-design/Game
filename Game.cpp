#include "InputHandler.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <algorithm>

char InputHandler::getLetter(const std::string& prompt) {
    char ch;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        if (input.size() == 1 && std::isalpha(static_cast<unsigned char>(input[0]))) {
            return static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));
        }
        // Allow 'H' or 'Q' as special commands
        if (input.size() == 1) {
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));
            if (ch == 'H' || ch == 'Q') return ch;
        }
        std::cout << "  ⚠  Please enter a single letter.\n";
    }
}

std::string InputHandler::getString(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    // Trim
    auto start = input.begin();
    while (start != input.end() && std::isspace(static_cast<unsigned char>(*start))) ++start;
    auto end = input.end();
    while (end != start && std::isspace(static_cast<unsigned char>(*(end - 1)))) --end;
    return std::string(start, end);
}

int InputHandler::getMenuChoice(int minVal, int maxVal, const std::string& prompt) {
    int choice;
    while (true) {
        std::cout << prompt;
        if (std::cin >> choice && choice >= minVal && choice <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  ⚠  Invalid choice. Enter a number between "
                  << minVal << " and " << maxVal << ".\n";
    }
}

bool InputHandler::getYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            char c = static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));
            if (c == 'Y') return true;
            if (c == 'N') return false;
        }
        std::cout << "  ⚠  Please enter Y or N.\n";
    }
}

std::string InputHandler::toLowerCase(const std::string& str) {
    std::string out = str;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return out;
}

std::string InputHandler::toUpperCase(const std::string& str) {
    std::string out = str;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return out;
}
