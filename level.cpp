#include "level.h"

Level::Level(const std::string& name, const std::string& description, Difficulty difficulty, const std::vector<Entity>& entities)
    : name(name), description(description), difficulty(difficulty), entities(entities) {}

std::string Level::getName() const { return name; }
std::string Level::getDescription() const { return description; }
Difficulty Level::getDifficulty() const { return difficulty; }
const std::vector<Entity>& Level::getEntities() const { return entities; }
