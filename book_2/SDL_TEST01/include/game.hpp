#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Game
{
private:
     bool isRunniing;//ゲームがスタートしているかどうか
     SDL_Window* window;
public:
     Game(/* args */);
     ~Game();

     int Setup();
     void Input();
     int Draw();
     void Update();
};


#endif /* GAME_HPP */
