#include "entity.h"
#include <algorithm>

Entity::Entity(const std::string& name, int health, int damage)
    : name(name), health(health), damage(damage) {
    studyDifficulty = health / 2;
    containmentDifficulty = health;
    experienceValue = health + damage;
}

std::string Entity::getName() const { return name; }
int Entity::getHealth() const { return health; }
int Entity::getDamage() const { return damage; }
int Entity::getStudyDifficulty() const { return studyDifficulty; }
int Entity::getContainmentDifficulty() const { return containmentDifficulty; }
int Entity::getExperienceValue() const { return experienceValue; }

void Entity::takeDamage(int amount) {
    health = std::max(0, health - amount);
}

bool Entity::isAlive() const { return health > 0; }
