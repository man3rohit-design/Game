#pragma once
#include <string>

class InputHandler {
public:
    static char getLetter(const std::string& prompt = "Enter a letter: ");
    static std::string getString(const std::string& prompt);
    static int getMenuChoice(int min, int max, const std::string& prompt = "Choice: ");
    static bool getYesNo(const std::string& prompt);
    static std::string toLowerCase(const std::string& str);
    static std::string toUpperCase(const std::string& str);
};
