#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

struct Vector2{
     float x;
     float y;
};

class Game
{
private:
     bool mIsRunniing; // ゲームがスタートしているかどうか
     SDL_Window *mWindow;
     SDL_Renderer *mRenderer;

     const int mWidth;//画面幅
     const int mHeight;//画面の高さ

     const int mThickness;//壁の厚みとボールの直径
     const int mPaddleLength; //パドルの長さ

     Vector2 mPaddlePos;//跳ね返す板
     Vector2 mBallPos;//動き回るボール

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
