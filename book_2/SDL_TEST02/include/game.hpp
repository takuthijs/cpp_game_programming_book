#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

struct Vector2{
     float x;
     float y;
};

struct Ball{
     Vector2 pos;
     Vector2 vel;
};

struct Paddle{
     Vector2 pos;
     int length;
     int dir;
};

class Game
{
private:
     bool mIsRunniing; // ゲームがスタートしているかどうか
     const int mFps;
     Uint32 mTicksCount;
     SDL_Window *mWindow;
     SDL_Renderer *mRenderer;

     const int mWidth;//画面幅
     const int mHeight;//画面の高さ

     const int mThickness;//壁の厚みとボールの直径

     std::vector<Ball> mBalls;//ボールのリスト
     std::vector<Paddle> mPaddles;//パドルのリスト 

     void Input();
     void Draw();

     void DrawShape(int,int,int,int);//図形を描画する処理
public:
     Game();
     ~Game();
     bool Initialize();
     void Update();
     void Shutdown();
};

#endif /* GAME_HPP */
