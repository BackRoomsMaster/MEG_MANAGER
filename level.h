#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "entity.h"

enum class Difficulty { Easy, Medium, Hard, Extreme };

class Level {
private:
    std::string name;
    std::string description;
    Difficulty difficulty;
    std::vector<Entity> entities;

public:
    Level(const std::string& name, const std::string& description, Difficulty difficulty, const std::vector<Entity>& entities);
    std::string getName() const;
    std::string getDescription() const;
    Difficulty getDifficulty() const;
    const std::vector<Entity>& getEntities() const;
};

#endif
