#include "game.hpp"

int main(){

    Game game;

    if(game.Initialize()){
        game.Update();
    }

    game.Shutdown();
    return 0;
}
