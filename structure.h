#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>
#include <map>

class Structure {
private:
    std::string name;
    std::map<std::string, int> cost;
    int studyBonus;
    int containmentBonus;
    int healthRestoreBonus;
    int sanityRestoreBonus;
    int explorerCapacityBonus;

public:
    Structure(const std::string& name, const std::map<std::string, int>& cost, 
              int studyBonus, int containmentBonus, int healthRestoreBonus, 
              int sanityRestoreBonus, int explorerCapacityBonus);
    std::string getName() const;
    std::map<std::string, int> getCost() const;
    int getStudyBonus() const;
    int getContainmentBonus() const;
    int getHealthRestoreBonus() const;
    int getSanityRestoreBonus() const;
    int getExplorerCapacityBonus() const;
};

#endif
