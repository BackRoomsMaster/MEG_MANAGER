#include "game_initializer.h"
#include <iostream>

void GameInitializer::initializeContainedEntities(Game& game) {
    const int initialEntities = 3;
    
    for (int i = 0; i < initialEntities; ++i) {
        Entity entity = game.getRandomEntity();
        game.addContainedEntity(entity);
        std::cout << "Entità iniziale contenuta: " << entity.getName() << std::endl;
    }
    
    std::cout << "Inizializzazione completata: " << initialEntities << " entità contenute all'inizio del gioco." << std::endl;
}
