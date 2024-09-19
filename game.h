#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <queue>
#include <map>
#include "player.h"
#include "entity.h"
#include "structure.h"
#include "explorer.h"
#include "level.h"

class Game {
private:
    Player player;
    std::vector<Entity> activeEntities;
    std::queue<Entity> entityQueue;
    std::vector<Structure> availableStructures;
    std::map<std::string, int> builtStructures;
    std::vector<Explorer> explorers;
    std::vector<Level> backroomsLevels;
    int currentDay;
    int entitiesContained;
    bool hasCenterOperativo;

public:
    Game();
    void play();
    void playDay();
    void displayStatus();
    void movePlayer();
    void interactWithEntity();
    void restPlayer();
    void buildStructure();
    void manageExplorers();
    void hireExplorer();
    void healExplorers();
    void displayExplorers() const;
    void displayDetailedExplorers() const;
    void exploreBackroomsLevel();
    void missionResult(const Level& level, std::vector<Explorer*>& team);
    void studyEntity(Entity& entity);
    void containEntity(Entity& entity);
    int getTotalStudyBonus() const;
    int getTotalContainmentBonus() const;
    void initializeStructures();
    void initializeBackroomsLevels();
    void displayBackroomsLevels() const;
    Entity getRandomEntity() const;
};

#endif
