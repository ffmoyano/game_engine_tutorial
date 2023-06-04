#include <SDL.h>
#include "Game.h"


// on windows is necessary to put argc and argv
int main(int argc, char* argv[])
{
    Game game;
    game.initialize();
    game.run();
    game.destroy();

    return 0;
}
