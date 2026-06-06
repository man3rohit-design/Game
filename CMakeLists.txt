#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

#include "WordDatabase.h"
#include "Game.h"
#include "PlayerManager.h"
#include "Display.h"
#include "InputHandler.h"

// ── Forward declarations ─────────────────────────────────────────────────────
void    loginMenu(PlayerManager& pm);
void    mainMenu(PlayerManager& pm, WordDatabase& db);
void    playGame(PlayerManager& pm, WordDatabase& db);
void    viewLeaderboard(PlayerManager& pm);
void    viewStats(PlayerManager& pm);

// ── Login / Registration ─────────────────────────────────────────────────────
void loginMenu(PlayerManager& pm) {
    Display::printBanner();
    std::cout << "\n";
    Display::printCentered("1. Login");
    Display::printCentered("2. Register");
    Display::printCentered("3. Continue as Guest");
    std::cout << "\n";
    int choice = InputHandler::getMenuChoice(1, 3, "  Choice: ");

    if (choice == 3) {
        pm.createPlayer("Guest");
        return;
    }

    std::string name = InputHandler::getString("\n  Enter your name: ");
    if (name.empty()) name = "Player";

    if (choice == 1) {
        if (!pm.loadPlayer(name)) {
            std::cout << "\n  Player not found. Creating new account...\n";
            pm.createPlayer(name);
        } else {
            std::cout << "\n  Welcome back, " << name << "!\n";
        }
    } else {
        pm.createPlayer(name);
        std::cout << "\n  Account created! Welcome, " << name << "!\n";
    }
    std::cout << "  Press ENTER to continue...";
    std::cin.get();
}

// ── Category selection ───────────────────────────────────────────────────────
std::string chooseCategory(WordDatabase& db) {
    std::vector<std::string> cats = db.getCategories();
    cats.insert(cats.begin(), "Any");

    std::cout << "\n  SELECT CATEGORY:\n";
    for (int i = 0; i < static_cast<int>(cats.size()); i++)
        std::cout << "    " << (i + 1) << ". " << cats[i] << "\n";
    std::cout << "\n";

    int choice = InputHandler::getMenuChoice(1, static_cast<int>(cats.size()), "  Choice: ");
    return (choice == 1) ? "any" : cats[choice - 1];
}

// ── Difficulty selection ─────────────────────────────────────────────────────
GameConfig chooseDifficulty(const std::string& category) {
    std::cout << "\n  SELECT DIFFICULTY:\n";
    std::cout << "    1. Easy   (8 attempts, short words)\n";
    std::cout << "    2. Medium (6 attempts, medium words)\n";
    std::cout << "    3. Hard   (4 attempts, long words)\n\n";

    int choice = InputHandler::getMenuChoice(1, 3, "  Choice: ");
    GameConfig cfg;
    cfg.category = category;

    switch (choice) {
        case 1: cfg.difficulty = "easy";   cfg.maxAttempts = 8; break;
        case 2: cfg.difficulty = "medium"; cfg.maxAttempts = 6; break;
        case 3: cfg.difficulty = "hard";   cfg.maxAttempts = 4; break;
    }
    return cfg;
}

// ── Single game round ────────────────────────────────────────────────────────
void playGame(PlayerManager& pm, WordDatabase& db) {
    Display::clearScreen();
    Display::printSeparator();
    std::cout << "\033[1m\033[33m";
    Display::printCentered("NEW GAME");
    std::cout << "\033[0m";
    Display::printSeparator();

    std::string category = chooseCategory(db);
    GameConfig  cfg      = chooseDifficulty(category);

    WordEntry entry;
    try {
        entry = db.getRandomWord(cfg.category, cfg.difficulty);
    } catch (const std::exception& e) {
        std::cout << "\n  ⚠  " << e.what() << " Trying 'any' difficulty...\n";
        cfg.difficulty = "any";
        entry = db.getRandomWord(cfg.category, "any");
    }

    Game game(entry, cfg);
    std::string playerName = pm.getPlayerData().name;

    // Main game loop
    while (game.getStatus() == GameStatus::PLAYING) {
        Display::printGameState(game, playerName);

        char input = InputHandler::getLetter("  >> Guess a letter: ");

        if (input == 'Q') {
            std::cout << "\n  Quitting to menu...\n";
            std::cout << "  Press ENTER...";
            std::cin.get();
            return;
        }

        if (input == 'H') {
            if (!game.isHintUsed()) {
                game.useHint();
                std::cout << "\n  \033[35m💡 Hint: " << game.getHint() << "\033[0m\n";
                std::cout << "  Press ENTER...";
                std::cin.get();
            } else {
                std::cout << "\n  Hint already used!\n";
                std::cout << "  Press ENTER...";
                std::cin.get();
            }
            continue;
        }

        bool correct = game.guessLetter(input);
        if (!correct && game.getGuessedLetters().count(input)) {
            // was a re-guess — guessLetter returned false for already-guessed
            std::cout << "\n  ⚠  You already guessed '" << input << "'!\n";
            std::cout << "  Press ENTER...";
            std::cin.get();
        }
    }

    // Outcome
    GameRecord record;
    record.word       = game.getWord();
    record.category   = game.getCategory();
    record.difficulty = cfg.difficulty;
    record.score      = game.getScore();

    if (game.getStatus() == GameStatus::WIN) {
        Display::printWin(game, playerName);
        record.result = "Win";
    } else {
        Display::printLose(game);
        record.result = "Lose";
    }

    pm.recordGame(record);
    std::cout << "  Press ENTER to continue...";
    std::cin.get();
}

// ── Stats / Leaderboard ──────────────────────────────────────────────────────
void viewLeaderboard(PlayerManager& pm) {
    auto board = pm.getLeaderboard();
    Display::printLeaderboard(board);
    std::cout << "  Press ENTER to continue...";
    std::cin.get();
}

void viewStats(PlayerManager& pm) {
    Display::printStats(pm.getPlayerData());
    std::cout << "  Press ENTER to continue...";
    std::cin.get();
}

// ── Main menu ────────────────────────────────────────────────────────────────
void mainMenu(PlayerManager& pm, WordDatabase& db) {
    while (true) {
        Display::printBanner();
        std::string name = pm.getPlayerData().name;
        std::cout << "\033[32m";
        Display::printCentered("Welcome, " + name + "!");
        std::cout << "\033[0m\n";

        std::cout << "    1. Play Game\n";
        std::cout << "    2. View My Stats\n";
        std::cout << "    3. Leaderboard\n";
        std::cout << "    4. How to Play\n";
        std::cout << "    5. Exit\n\n";

        int choice = InputHandler::getMenuChoice(1, 5, "  Choice: ");
        switch (choice) {
            case 1: playGame(pm, db);      break;
            case 2: viewStats(pm);         break;
            case 3: viewLeaderboard(pm);   break;
            case 4:
                Display::printRules();
                std::cout << "  Press ENTER to continue...";
                std::cin.get();
                break;
            case 5:
                Display::clearScreen();
                std::cout << "\n  Thanks for playing! Goodbye!\n\n";
                return;
        }
    }
}

// ── Entry point ──────────────────────────────────────────────────────────────
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    WordDatabase  db;
    PlayerManager pm;

    loginMenu(pm);
    mainMenu(pm, db);

    return 0;
}
