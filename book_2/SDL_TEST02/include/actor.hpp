#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <stdio.h>
#include <vector>
#include "game.hpp"

class Game;

struct Vector2{
     float x;
     float y;
};

class Actor
{
public:
     enum State{
          EActive,
          EPaused,
          EDead
     };
     //コンストラクターとデストラクター
     Actor(Game* game);
     virtual ~Actor();

     //ゲームから呼び出される更新関数(オーバーライド不可)
     void Update(float deltaTime);
     //アクターがもつ全コンポーネントを更新(オーバーライド不可)
     void UpdateComponent(float deltaTime);
     //アクター独自の更新処理(オーバーライド可能)
     virtual void UpdateActor(float deltaTime);

     //ゲッター・セッター
     State GetState() const {return mState;}
     void SetState(State value) {mState = value;}

     Vector2 GetPosition() const {return mPosition;}
     void SetPosition(Vector2 value) {mPosition = value;}

     float GetScale() const {return mScale;}
     void SetScale(float value) {mScale = value;}

     float GetRotation() const {return mRotation;}
     void SetRotation(float value) {mRotation = value;}
     

     //コンポーネントの追加・削除
     void AddComponent(class Component* component);
     void RemoveComponent(class Component* component);
     
private:
     //アクターの状態
     State mState;
     //座標変換
     Vector2 mPosition;//アクターの中心位置
     float mScale;//アクターのスケール（1.0fが100%）
     float mRotation;//回転の角度（ラジアン）
     //アクターが持つコンポーネント
     std::vector<class Component*> mConponent;
     class Game* mGame;
};

#endif /* ACTOR_HPP */