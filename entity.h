#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
private:
    std::string name;
    int health;
    int damage;
    int studyDifficulty;
    int containmentDifficulty;
    int experienceValue;

public:
    Entity(const std::string& name, int health, int damage);
    std::string getName() const;
    int getHealth() const;
    int getDamage() const;
    int getStudyDifficulty() const;
    int getContainmentDifficulty() const;
    int getExperienceValue() const;
    void takeDamage(int amount);
    bool isAlive() const;
};

#endif
