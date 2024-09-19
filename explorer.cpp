#include "explorer.h"
#include <algorithm>
#include <cmath>

Explorer::Explorer(const std::string& name, int health, int sanity, int skill)
    : name(name), health(health), maxHealth(health), sanity(sanity), maxSanity(sanity), 
      skill(skill), experience(0), level(1) {}

std::string Explorer::getName() const { return name; }
int Explorer::getHealth() const { return health; }
int Explorer::getMaxHealth() const { return maxHealth; }
int Explorer::getSanity() const { return sanity; }
int Explorer::getMaxSanity() const { return maxSanity; }
int Explorer::getSkill() const { return skill; }
int Explorer::getExperience() const { return experience; }
int Explorer::getLevel() const { return level; }

void Explorer::takeDamage(int amount) {
    health = std::max(0, health - amount);
}

void Explorer::takeSanityDamage(int amount) {
    sanity = std::max(0, sanity - amount);
}

void Explorer::heal(int amount) {
    health = std::min(health + amount, maxHealth);
}

void Explorer::restoreSanity(int amount) {
    sanity = std::min(sanity + amount, maxSanity);
}

void Explorer::gainExperience(int amount) {
    experience += amount;
    while (experience >= 100 * level) {
        levelUp();
    }
}

void Explorer::levelUp() {
    experience -= 100 * level;
    level++;
    maxHealth += 10;
    maxSanity += 5;
    health = maxHealth;
    sanity = maxSanity;
    skill += 1;
}

bool Explorer::isAlive() const { return health > 0; }
bool Explorer::isSane() const { return sanity > 0; }
