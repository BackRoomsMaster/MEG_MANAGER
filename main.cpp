#include "game.h"
#include "game_initializer.h"

int main() {
    Game game;
    GameInitializer::initializeContainedEntities(game);
    game.play();
    return 0;
}
