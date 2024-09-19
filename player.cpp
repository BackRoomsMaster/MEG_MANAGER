#include "player.h"
#include <algorithm>

Player::Player(const std::string& name, int health, int knowledge)
    : name(name), health(health), knowledge(knowledge), level(1), experience(0) {}

std::string Player::getName() const { return name; }
int Player::getHealth() const { return health; }
int Player::getKnowledge() const { return knowledge; }
int Player::getLevel() const { return level; }
int Player::getExperience() const { return experience; }

void Player::takeDamage(int amount) {
    health = std::max(0, health - amount);
}

void Player::increaseKnowledge(int amount) {
    knowledge += amount;
}

void Player::gainExperience(int amount) {
    experience += amount;
    while (experience >= 100 * level) {
        levelUp();
    }
}

void Player::levelUp() {
    experience -= 100 * level;
    level++;
    health += 20;
    knowledge += 5;
}

void Player::addResource(const std::string& resource, int amount) {
    resources[resource] += amount;
}

int Player::getResource(const std::string& resource) const {
    auto it = resources.find(resource);
    return (it != resources.end()) ? it->second : 0;
}

bool Player::useResource(const std::string& resource, int amount) {
    if (getResource(resource) >= amount) {
        resources[resource] -= amount;
        return true;
    }
    return false;
}
