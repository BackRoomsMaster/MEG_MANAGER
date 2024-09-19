#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>

class Explorer {
private:
    std::string name;
    int health;
    int maxHealth;
    int sanity;
    int maxSanity;
    int skill;
    int experience;
    int level;

public:
    Explorer(const std::string& name, int health, int sanity, int skill);
    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getSanity() const;
    int getMaxSanity() const;
    int getSkill() const;
    int getExperience() const;
    int getLevel() const;
    void takeDamage(int amount);
    void takeSanityDamage(int amount);
    void heal(int amount);
    void restoreSanity(int amount);
    void gainExperience(int amount);
    void levelUp();
    bool isAlive() const;
    bool isSane() const;
};

#endif
