#include "PlayerManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

PlayerManager::PlayerManager() : loaded(false) {
    fs::create_directories("saves");
}

std::string PlayerManager::getSavePath(const std::string& name) const {
    return "saves/" + name + ".dat";
}

std::string PlayerManager::getCurrentDate() const {
    std::time_t t = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return std::string(buf);
}

bool PlayerManager::loadPlayer(const std::string& name) {
    std::ifstream file(getSavePath(name));
    if (!file.is_open()) return false;

    player = PlayerData();
    player.name = name;

    std::string line;
    std::getline(file, line); // name
    std::getline(file, line); player.totalScore  = std::stoi(line);
    std::getline(file, line); player.gamesPlayed  = std::stoi(line);
    std::getline(file, line); player.gamesWon     = std::stoi(line);
    std::getline(file, line); player.gamesLost    = std::stoi(line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        GameRecord r;
        std::getline(ss, r.word,       '|');
        std::getline(ss, r.category,   '|');
        std::getline(ss, r.difficulty, '|');
        std::getline(ss, r.result,     '|');
        std::string sc; std::getline(ss, sc, '|');
        r.score = std::stoi(sc);
        std::getline(ss, r.date, '|');
        player.history.push_back(r);
    }

    loaded = true;
    return true;
}

bool PlayerManager::savePlayer() const {
    if (!loaded) return false;
    std::ofstream file(getSavePath(player.name));
    if (!file.is_open()) return false;

    file << player.name       << "\n"
         << player.totalScore  << "\n"
         << player.gamesPlayed  << "\n"
         << player.gamesWon     << "\n"
         << player.gamesLost    << "\n";

    for (const auto& r : player.history) {
        file << r.word << "|" << r.category << "|" << r.difficulty
             << "|" << r.result << "|" << r.score << "|" << r.date << "\n";
    }
    return true;
}

void PlayerManager::createPlayer(const std::string& name) {
    player = PlayerData();
    player.name        = name;
    player.totalScore  = 0;
    player.gamesPlayed = 0;
    player.gamesWon    = 0;
    player.gamesLost   = 0;
    loaded = true;
    savePlayer();
}

void PlayerManager::recordGame(const GameRecord& record) {
    player.history.push_back(record);
    player.gamesPlayed++;
    if (record.result == "Win")  player.gamesWon++;
    else                         player.gamesLost++;
    player.totalScore += record.score;
    savePlayer();
}

void PlayerManager::addScore(int points) {
    player.totalScore += points;
}

PlayerData PlayerManager::getPlayerData() const { return player; }
bool       PlayerManager::isLoaded()       const { return loaded; }

double PlayerManager::getWinRate() const {
    if (player.gamesPlayed == 0) return 0.0;
    return (static_cast<double>(player.gamesWon) / player.gamesPlayed) * 100.0;
}

std::vector<PlayerData> PlayerManager::getLeaderboard() const {
    // Scan saves directory for all .dat files
    std::vector<PlayerData> board;
    if (!fs::exists("saves")) return board;

    for (const auto& entry : fs::directory_iterator("saves")) {
        if (entry.path().extension() == ".dat") {
            std::string pname = entry.path().stem().string();
            PlayerManager tmp;
            if (tmp.loadPlayer(pname))
                board.push_back(tmp.getPlayerData());
        }
    }

    std::sort(board.begin(), board.end(), [](const PlayerData& a, const PlayerData& b) {
        return a.totalScore > b.totalScore;
    });
    return board;
}
