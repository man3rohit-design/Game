#pragma once
#include <string>
#include <vector>
#include <map>

struct WordEntry {
    std::string word;
    std::string category;
    std::string hint;
    std::string difficulty; // "easy", "medium", "hard"
};

class WordDatabase {
public:
    WordDatabase();
    WordEntry getRandomWord(const std::string& category = "any", const std::string& difficulty = "any") const;
    std::vector<std::string> getCategories() const;

private:
    std::vector<WordEntry> words;
    void loadWords();
};
