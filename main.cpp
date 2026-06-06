#include "Display.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <set>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[97m"
#define BOLD    "\033[1m"

void Display::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Display::printSeparator() {
    std::cout << CYAN << std::string(60, '=') << RESET << "\n";
}

void Display::printCentered(const std::string& text, int width) {
    int pad = (width - static_cast<int>(text.size())) / 2;
    if (pad < 0) pad = 0;
    std::cout << std::string(pad, ' ') << text << "\n";
}

void Display::printColored(const std::string& text, const std::string& color) {
    std::cout << color << text << RESET;
}

void Display::printBanner() {
    clearScreen();
    printSeparator();
    std::cout << BOLD << YELLOW;
    printCentered("██╗  ██╗ █████╗ ███╗  ██╗ ██████╗ ███╗  ███╗ █████╗ ███╗  ██╗");
    printCentered("██║  ██║██╔══██╗████╗ ██║██╔════╝ ████╗████║██╔══██╗████╗ ██║");
    printCentered("███████║███████║██╔██╗██║██║  ███╗██╔████╔██║███████║██╔██╗██║");
    printCentered("██╔══██║██╔══██║██║╚████║██║   ██║██║╚██╔╝██║██╔══██║██║╚████║");
    printCentered("██║  ██║██║  ██║██║ ╚███║╚██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚███║");
    printCentered("╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝");
    std::cout << RESET;
    printCentered("~ The Classic Word Guessing Game ~");
    printSeparator();
}

void Display::printHangman(int wrongCount) {
    // 7-stage hangman (0 = none, 6 = full body)
    const std::string stages[7][8] = {
        // Stage 0
        { "  +------+",
          "  |      |",
          "  |       ",
          "  |       ",
          "  |       ",
          "  |       ",
          "  |       ",
          "==========" },
        // Stage 1 – head
        { "  +------+",
          "  |      |",
          "  |      O",
          "  |       ",
          "  |       ",
          "  |       ",
          "  |       ",
          "==========" },
        // Stage 2 – body
        { "  +------+",
          "  |      |",
          "  |      O",
          "  |      |",
          "  |       ",
          "  |       ",
          "  |       ",
          "==========" },
        // Stage 3 – left arm
        { "  +------+",
          "  |      |",
          "  |      O",
          "  |     /|",
          "  |       ",
          "  |       ",
          "  |       ",
          "==========" },
        // Stage 4 – both arms
        { "  +------+",
          "  |      |",
          "  |      O",
          "  |     /|\\",
          "  |       ",
          "  |       ",
          "  |       ",
          "==========" },
        // Stage 5 – left leg
        { "  +------+",
          "  |      |",
          "  |      O",
          "  |     /|\\",
          "  |     / ",
          "  |       ",
          "  |       ",
          "==========" },
        // Stage 6 – both legs (game over)
        { "  +------+",
          "  |      |",
          "  |      O",
          "  |     /|\\",
          "  |     / \\",
          "  |       ",
          "  |       ",
          "==========" }
    };

    int idx = wrongCount;
    if (idx < 0) idx = 0;
    if (idx > 6) idx = 6;

    std::string color = (idx <= 2) ? GREEN : (idx <= 4) ? YELLOW : RED;
    for (int i = 0; i < 8; i++)
        std::cout << color << "  " << stages[idx][i] << RESET << "\n";
}

void Display::printGameState(const Game& game, const std::string& playerName) {
    clearScreen();
    printSeparator();
    std::cout << BOLD << CYAN;
    printCentered("HANGMAN GAME");
    std::cout << RESET;
    printSeparator();

    // Hangman drawing
    printHangman(game.getWrongCount());
    std::cout << "\n";

    // Category & attempts
    std::cout << YELLOW << "  Category : " << RESET << game.getCategory() << "\n";
    std::cout << YELLOW << "  Player   : " << RESET << playerName << "\n";
    std::cout << YELLOW << "  Score    : " << RESET << game.getScore() << "\n";

    int remaining = game.getRemainingAttempts();
    std::string lifeColor = (remaining > 3) ? GREEN : (remaining > 1) ? YELLOW : RED;
    std::cout << lifeColor << "  Lives    : ";
    for (int i = 0; i < remaining; i++)        std::cout << "♥ ";
    for (int i = remaining; i < game.getMaxAttempts(); i++) std::cout << "♡ ";
    std::cout << "  (" << remaining << "/" << game.getMaxAttempts() << ")\n" << RESET;

    // Hidden word
    std::cout << "\n  " << BOLD << WHITE;
    std::cout << game.getMaskedWord();
    std::cout << RESET << "\n\n";

    // Wrong letters
    if (!game.getWrongLetters().empty()) {
        std::cout << RED << "  Wrong letters: ";
        for (char c : game.getWrongLetters()) std::cout << c << " ";
        std::cout << RESET << "\n";
    }

    // Hint used?
    if (game.isHintUsed()) {
        std::cout << MAGENTA << "  Hint: " << game.getHint() << RESET << "\n";
    }

    std::cout << "\n";
    printSeparator();
    if (!game.isHintUsed())
        std::cout << "  [H] Use Hint (-20 pts)   [Q] Quit\n";
    else
        std::cout << "  [Q] Quit\n";
    printSeparator();
}

void Display::printWin(const Game& game, const std::string& playerName) {
    clearScreen();
    printSeparator();
    std::cout << BOLD << GREEN;
    printCentered("🎉 CONGRATULATIONS! 🎉");
    std::cout << RESET;
    printSeparator();
    std::cout << GREEN << "\n  You guessed the word: " << BOLD << game.getWord() << "\n" << RESET;
    std::cout << YELLOW << "  Final Score : " << BOLD << game.getScore() << " pts\n" << RESET;
    std::cout << YELLOW << "  Player      : " << playerName << "\n\n" << RESET;
    printSeparator();
}

void Display::printLose(const Game& game) {
    clearScreen();
    printSeparator();
    std::cout << BOLD << RED;
    printCentered("💀 GAME OVER! 💀");
    std::cout << RESET;
    printSeparator();
    printHangman(6);
    std::cout << RED << "\n  The word was: " << BOLD << game.getWord() << "\n" << RESET;
    std::cout << MAGENTA << "  Hint        : " << game.getHint() << "\n\n" << RESET;
    printSeparator();
}

void Display::printLeaderboard(const std::vector<PlayerData>& board) {
    clearScreen();
    printSeparator();
    std::cout << BOLD << YELLOW;
    printCentered("🏆 LEADERBOARD 🏆");
    std::cout << RESET;
    printSeparator();

    if (board.empty()) {
        std::cout << "  No players yet.\n";
    } else {
        std::cout << BOLD
                  << std::left << std::setw(5)  << "Rank"
                  << std::setw(18) << "Name"
                  << std::setw(10) << "Score"
                  << std::setw(8)  << "Wins"
                  << std::setw(8)  << "Losses"
                  << "Win%\n" << RESET;
        std::cout << std::string(60, '-') << "\n";

        int rank = 1;
        for (const auto& p : board) {
            std::string color = (rank == 1) ? YELLOW : (rank == 2) ? WHITE : (rank == 3) ? "\033[33m" : RESET;
            double wr = (p.gamesPlayed > 0) ? (100.0 * p.gamesWon / p.gamesPlayed) : 0.0;
            std::cout << color
                      << std::left << std::setw(5)  << rank
                      << std::setw(18) << p.name
                      << std::setw(10) << p.totalScore
                      << std::setw(8)  << p.gamesWon
                      << std::setw(8)  << p.gamesLost
                      << std::fixed << std::setprecision(1) << wr << "%\n" << RESET;
            rank++;
        }
    }
    printSeparator();
}

void Display::printStats(const PlayerData& p) {
    clearScreen();
    printSeparator();
    std::cout << BOLD << CYAN;
    printCentered("📊 PLAYER STATISTICS");
    std::cout << RESET;
    printSeparator();

    double wr = (p.gamesPlayed > 0) ? (100.0 * p.gamesWon / p.gamesPlayed) : 0.0;

    std::cout << YELLOW << "  Name         : " << RESET << p.name         << "\n";
    std::cout << YELLOW << "  Total Score  : " << RESET << p.totalScore   << " pts\n";
    std::cout << YELLOW << "  Games Played : " << RESET << p.gamesPlayed  << "\n";
    std::cout << GREEN  << "  Games Won    : " << RESET << p.gamesWon     << "\n";
    std::cout << RED    << "  Games Lost   : " << RESET << p.gamesLost    << "\n";
    std::cout << CYAN   << "  Win Rate     : " << RESET
              << std::fixed << std::setprecision(1) << wr << "%\n\n";

    if (!p.history.empty()) {
        std::cout << BOLD << "  Recent Games:\n" << RESET;
        std::cout << std::string(60, '-') << "\n";
        int start = std::max(0, static_cast<int>(p.history.size()) - 5);
        for (int i = start; i < static_cast<int>(p.history.size()); i++) {
            const auto& r = p.history[i];
            std::string col = (r.result == "Win") ? GREEN : RED;
            std::cout << col << "  [" << r.result << "] " << RESET
                      << std::left << std::setw(14) << r.word
                      << "  " << std::setw(12) << r.category
                      << "  " << std::setw(8) << r.difficulty
                      << "  " << r.score << " pts  " << r.date << "\n";
        }
    }
    printSeparator();
}

void Display::printRules() {
    clearScreen();
    printSeparator();
    std::cout << BOLD << YELLOW;
    printCentered("📖 HOW TO PLAY");
    std::cout << RESET;
    printSeparator();
    std::cout << R"(
  1. A secret word is chosen from the selected category.
  2. Blanks represent each letter in the word.
  3. Guess one letter at a time.
  4. Each correct guess reveals the letter(s) in the word.
  5. Each wrong guess draws another part of the hangman.
  6. You WIN by guessing all letters before running out of lives.
  7. You LOSE when the hangman is fully drawn.

  SCORING:
    ✔ Correct Guess  : +10 points
    ✘ Wrong Guess    : -5  points
    🏆 Win Bonus     : +50 points
    💡 Hint Used     : -20 points

  DIFFICULTY:
    Easy   → 8 attempts  (short words)
    Medium → 6 attempts  (medium words)
    Hard   → 4 attempts  (long words)
)";
    printSeparator();
}
