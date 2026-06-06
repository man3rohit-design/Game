#pragma once
#include <string>
#include <vector>

struct GameRecord {
    std::string word;
    std::string category;
    std::string difficulty;
    std::string result; // "Win" or "Lose"
    int score;
    std::string date;
};

struct PlayerData {
    std::string name;
    int totalScore;
    int gamesPlayed;
    int gamesWon;
    int gamesLost;
    std::vector<GameRecord> history;
};

class PlayerManager {
public:
    PlayerManager();
    bool loadPlayer(const std::string& name);
    bool savePlayer() const;
    void createPlayer(const std::string& name);
    void recordGame(const GameRecord& record);
    void addScore(int points);

    PlayerData getPlayerData() const;
    std::vector<PlayerData> getLeaderboard() const;
    bool isLoaded() const;
    double getWinRate() const;

private:
    PlayerData player;
    bool loaded;
    std::string getSavePath(const std::string& name) const;
    std::string getCurrentDate() const;
};
