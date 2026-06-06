#pragma once
#include <string>
#include <vector>
#include "Game.h"
#include "PlayerManager.h"

class Display {
public:
    static void clearScreen();
    static void printBanner();
    static void printHangman(int wrongCount);
    static void printGameState(const Game& game, const std::string& playerName);
    static void printWin(const Game& game, const std::string& playerName);
    static void printLose(const Game& game);
    static void printLeaderboard(const std::vector<PlayerData>& board);
    static void printStats(const PlayerData& player);
    static void printRules();
    static void printSeparator();
    static void printColored(const std::string& text, const std::string& color);
    static void printCentered(const std::string& text, int width = 60);
};
