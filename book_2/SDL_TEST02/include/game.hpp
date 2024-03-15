#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <list>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

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
     std::list<class SpriteComponent*> mSprites;//読み込んだ画像

     void Input();
     void Draw();

     void DrawShape(int,int,int,int);//図形を描画する処理
     SDL_Texture* LoadImage(const char* fileName);//イメージをロードする

public:
     Game();
     ~Game();
     bool Initialize();
     void Update();
     void Shutdown();

     //ゲッター・セッター
     int GetWidth() const{return mWidth;};
     int GetHeight() const{return mHeight;};

     //アクターを受け取る処理
     void AddActor(Actor* actor);
     void RemoveActor(Actor* actor);

     //スプライトの追加SpriteComponentのコンストラクターで呼び出し
     void AddSprite(SpriteComponent* sprite);
     void RemoveSprite(SpriteComponent* sprite);
};

#endif /* GAME_HPP */
