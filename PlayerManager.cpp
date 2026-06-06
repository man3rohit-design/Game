#include "WordDatabase.h"
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <ctime>

WordDatabase::WordDatabase() {
    loadWords();
}

void WordDatabase::loadWords() {
    // ── ANIMALS ──────────────────────────────────────────────────────────────
    words.push_back({"CAT",        "Animals", "A common household pet that purrs.",            "easy"});
    words.push_back({"DOG",        "Animals", "Man's best friend.",                            "easy"});
    words.push_back({"FISH",       "Animals", "It lives in water and has fins.",               "easy"});
    words.push_back({"BIRD",       "Animals", "It has wings and can fly.",                     "easy"});
    words.push_back({"BEAR",       "Animals", "A large mammal that hibernates in winter.",     "easy"});
    words.push_back({"TIGER",      "Animals", "This is a wild striped animal.",                "medium"});
    words.push_back({"ELEPHANT",   "Animals", "The largest land animal with a long trunk.",    "medium"});
    words.push_back({"DOLPHIN",    "Animals", "A highly intelligent marine mammal.",           "medium"});
    words.push_back({"PENGUIN",    "Animals", "A flightless bird that lives in cold regions.", "medium"});
    words.push_back({"GIRAFFE",    "Animals", "The tallest land animal on Earth.",             "medium"});
    words.push_back({"CROCODILE",  "Animals", "A large reptile with powerful jaws.",           "hard"});
    words.push_back({"CHAMELEON",  "Animals", "A reptile known for changing colour.",          "hard"});
    words.push_back({"ORANGUTAN",  "Animals", "A great ape found in Borneo and Sumatra.",      "hard"});
    words.push_back({"SALAMANDER", "Animals", "An amphibian that can regrow lost limbs.",      "hard"});

    // ── COUNTRIES ────────────────────────────────────────────────────────────
    words.push_back({"CUBA",        "Countries", "An island nation in the Caribbean.",               "easy"});
    words.push_back({"PERU",        "Countries", "Home of Machu Picchu.",                            "easy"});
    words.push_back({"IRAN",        "Countries", "A country in the Middle East, formerly Persia.",   "easy"});
    words.push_back({"NEPAL",       "Countries", "Home of Mount Everest.",                           "easy"});
    words.push_back({"BRAZIL",      "Countries", "The largest country in South America.",            "medium"});
    words.push_back({"FRANCE",      "Countries", "Home of the Eiffel Tower.",                        "medium"});
    words.push_back({"CANADA",      "Countries", "The second largest country in the world.",         "medium"});
    words.push_back({"GERMANY",     "Countries", "Known for the Autobahn and Oktoberfest.",          "medium"});
    words.push_back({"PORTUGAL",    "Countries", "A country in southwestern Europe.",               "medium"});
    words.push_back({"ARGENTINA",   "Countries", "Known for tango and Patagonia.",                   "hard"});
    words.push_back({"MOZAMBIQUE",  "Countries", "A country on the east coast of Africa.",           "hard"});
    words.push_back({"SWITZERLAND", "Countries", "Known for watches, chocolate, and neutrality.",    "hard"});
    words.push_back({"PHILIPPINES", "Countries", "An archipelago nation in Southeast Asia.",         "hard"});

    // ── MOVIES ───────────────────────────────────────────────────────────────
    words.push_back({"JAWS",        "Movies", "A terrifying shark thriller by Spielberg.",          "easy"});
    words.push_back({"ALIEN",       "Movies", "In space, no one can hear you scream.",              "easy"});
    words.push_back({"AVATAR",      "Movies", "A film set on the moon Pandora.",                    "medium"});
    words.push_back({"TITANIC",     "Movies", "A love story aboard a doomed ocean liner.",          "medium"});
    words.push_back({"INCEPTION",   "Movies", "A film about dreams within dreams.",                 "medium"});
    words.push_back({"INTERSTELLAR","Movies", "Astronauts travel through a wormhole.",              "medium"});
    words.push_back({"GLADIATOR",   "Movies", "A Roman general becomes a gladiator for revenge.",   "medium"});
    words.push_back({"BRAVEHEART",  "Movies", "The story of Scottish warrior William Wallace.",     "hard"});
    words.push_back({"SHAWSHANK",   "Movies", "A tale of hope and friendship in prison.",           "hard"});
    words.push_back({"GOODFELLAS",  "Movies", "A Scorsese film about the mob in New York.",         "hard"});

    // ── SPORTS ───────────────────────────────────────────────────────────────
    words.push_back({"GOLF",       "Sports", "Played on a course with a small white ball.",         "easy"});
    words.push_back({"POLO",       "Sports", "A team sport played on horseback.",                   "easy"});
    words.push_back({"RUGBY",      "Sports", "A full-contact team sport with an oval ball.",        "medium"});
    words.push_back({"TENNIS",     "Sports", "Played with a racket on a rectangular court.",       "medium"});
    words.push_back({"CRICKET",    "Sports", "Played with a bat and a red ball on a pitch.",        "medium"});
    words.push_back({"SWIMMING",   "Sports", "A competitive sport performed in water.",             "medium"});
    words.push_back({"BASEBALL",   "Sports", "Known as America's favourite pastime.",               "medium"});
    words.push_back({"BADMINTON",  "Sports", "Played with a shuttlecock over a net.",               "hard"});
    words.push_back({"VOLLEYBALL", "Sports", "A net sport played by two teams of six.",             "hard"});
    words.push_back({"TAEKWONDO",  "Sports", "A Korean martial art known for high kicks.",          "hard"});

    // ── TECHNOLOGY ───────────────────────────────────────────────────────────
    words.push_back({"BYTE",        "Technology", "A unit of digital information (8 bits).",             "easy"});
    words.push_back({"WIFI",        "Technology", "Wireless internet connection technology.",            "easy"});
    words.push_back({"CODE",        "Technology", "Instructions written for a computer.",               "easy"});
    words.push_back({"SERVER",      "Technology", "A computer that provides data to other computers.",  "medium"});
    words.push_back({"PYTHON",      "Technology", "A popular, beginner-friendly programming language.", "medium"});
    words.push_back({"BROWSER",     "Technology", "Software used to access the internet.",              "medium"});
    words.push_back({"NETWORK",     "Technology", "A group of connected computers.",                    "medium"});
    words.push_back({"COMPILER",    "Technology", "Converts source code into machine code.",            "medium"});
    words.push_back({"DATABASE",    "Technology", "An organised collection of structured data.",        "hard"});
    words.push_back({"ALGORITHM",   "Technology", "A step-by-step procedure to solve a problem.",      "hard"});
    words.push_back({"BLOCKCHAIN",  "Technology", "A distributed, immutable digital ledger.",          "hard"});
    words.push_back({"ENCRYPTION",  "Technology", "The process of encoding data to prevent access.",   "hard"});

    // ── FOOD ─────────────────────────────────────────────────────────────────
    words.push_back({"RICE",        "Food", "A staple grain eaten worldwide.",                     "easy"});
    words.push_back({"CAKE",        "Food", "A sweet baked dessert often served at birthdays.",   "easy"});
    words.push_back({"SOUP",        "Food", "A liquid dish made by boiling ingredients.",         "easy"});
    words.push_back({"PIZZA",       "Food", "An Italian flatbread topped with sauce and cheese.", "easy"});
    words.push_back({"PASTA",       "Food", "An Italian dish made from dough.",                   "easy"});
    words.push_back({"SUSHI",       "Food", "A Japanese dish with rice and seafood.",             "medium"});
    words.push_back({"BURGER",      "Food", "A grilled patty served in a bun.",                   "medium"});
    words.push_back({"NOODLES",     "Food", "Long thin strips of dough, common in Asia.",         "medium"});
    words.push_back({"LASAGNA",     "Food", "A layered Italian pasta bake.",                      "medium"});
    words.push_back({"CHOCOLATE",   "Food", "A sweet food made from cacao beans.",                "hard"});
    words.push_back({"QUESADILLA",  "Food", "A Mexican dish with cheese in a tortilla.",          "hard"});
    words.push_back({"BRUSCHETTA",  "Food", "An Italian appetiser on toasted bread.",             "hard"});
}

WordEntry WordDatabase::getRandomWord(const std::string& category, const std::string& difficulty) const {
    std::vector<WordEntry> filtered;

    for (const auto& w : words) {
        bool catMatch  = (category   == "any" || w.category   == category);
        bool diffMatch = (difficulty == "any" || w.difficulty == difficulty);
        if (catMatch && diffMatch)
            filtered.push_back(w);
    }

    if (filtered.empty())
        throw std::runtime_error("No words found for the selected category/difficulty.");

    return filtered[std::rand() % filtered.size()];
}

std::vector<std::string> WordDatabase::getCategories() const {
    std::vector<std::string> cats;
    for (const auto& w : words) {
        if (std::find(cats.begin(), cats.end(), w.category) == cats.end())
            cats.push_back(w.category);
    }
    return cats;
}
