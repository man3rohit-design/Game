#pragma once
#include <string>
#include <vector>
#include <set>
#include "WordDatabase.h"

enum class GameStatus {
    PLAYING,
    WIN,
    LOSE
};

struct GameConfig {
    std::string category;
    std::string difficulty;
    int maxAttempts;
};

class Game {
public:
    Game(const WordEntry& wordEntry, const GameConfig& config);

    bool guessLetter(char letter);
    bool useHint();
    GameStatus getStatus() const;
    std::string getMaskedWord() const;
    int getScore() const;
    int getRemainingAttempts() const;
    int getMaxAttempts() const;
    std::set<char> getGuessedLetters() const;
    std::set<char> getWrongLetters() const;
    std::string getWord() const;
    std::string getHint() const;
    std::string getCategory() const;
    bool isHintUsed() const;
    int getWrongCount() const;

private:
    WordEntry entry;
    GameConfig config;
    std::set<char> guessedLetters;
    std::set<char> wrongLetters;
    int score;
    int wrongCount;
    bool hintUsed;
    GameStatus status;

    void updateStatus();
};
