#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "Actor.hpp"

struct Vector2{
     float x;
     float y;
};

class Actor;

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

     bool mUpdatingActors;//アクターの更新処理を行なっているかどうか
     std::vector<class Actor*> mActors;//実際に処理を行うアクター
     std::vector<class Actor*> mPendingActors;//追加などを行うアクター、mActorの処理が完了したらmActorsに追加する

     void Input();
     void Draw();

     void DrawShape(int,int,int,int);//図形を描画する処理
public:
     Game();
     ~Game();
     bool Initialize();
     void Update();
     void Shutdown();

     //アクターを受け取る処理
     void AddActor(Actor* actor);
     void RemoveActor(Actor* actor);
};

#endif /* GAME_HPP */
