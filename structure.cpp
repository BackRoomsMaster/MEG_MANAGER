#include "structure.h"

Structure::Structure(const std::string& name, const std::map<std::string, int>& cost, 
                     int studyBonus, int containmentBonus, int healthRestoreBonus, 
                     int sanityRestoreBonus, int explorerCapacityBonus)
    : name(name), cost(cost), studyBonus(studyBonus), containmentBonus(containmentBonus),
      healthRestoreBonus(healthRestoreBonus), sanityRestoreBonus(sanityRestoreBonus),
      explorerCapacityBonus(explorerCapacityBonus) {}

std::string Structure::getName() const { return name; }
std::map<std::string, int> Structure::getCost() const { return cost; }
int Structure::getStudyBonus() const { return studyBonus; }
int Structure::getContainmentBonus() const { return containmentBonus; }
int Structure::getHealthRestoreBonus() const { return healthRestoreBonus; }
int Structure::getSanityRestoreBonus() const { return sanityRestoreBonus; }
int Structure::getExplorerCapacityBonus() const { return explorerCapacityBonus; }
