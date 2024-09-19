#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

class Player {
private:
    std::string name;
    int health;
    int knowledge;
    int level;
    int experience;
    std::map<std::string, int> resources;

public:
    Player(const std::string& name = "", int health = 100, int knowledge = 0);
    std::string getName() const;
    int getHealth() const;
    int getKnowledge() const;
    int getLevel() const;
    int getExperience() const;
    void takeDamage(int amount);
    void increaseKnowledge(int amount);
    void gainExperience(int amount);
    void levelUp();
    void addResource(const std::string& resource, int amount);
    int getResource(const std::string& resource) const;
    bool useResource(const std::string& resource, int amount);
};

#endif
