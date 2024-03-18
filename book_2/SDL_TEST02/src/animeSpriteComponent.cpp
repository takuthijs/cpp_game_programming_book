#include "animeSpriteComponent.hpp"

AnimeSpriteComponent::AnimeSpriteComponent(Actor* owner,int drawOrder = 100):
SpriteComponent(owner,drawOrder),
mCurrFrame(0),
mAnimFPS(0)
{
}

AnimeSpriteComponent::~AnimeSpriteComponent()
{
}

void AnimeSpriteComponent::Update(float deltaTime)
{
     SpriteComponent::Update(deltaTime);
     if(mAnimeTextures.size() > 0)
     {
          //フレームレートとデルタタイムに基づいてカウントフレームを更新する
          mCurrFrame += mAnimFPS * deltaTime;
          //必要に応じてカレントフレームを巻き戻す
          while(mCurrFrame >= mAnimeTextures.size())
          {
               mCurrFrame -= mAnimeTextures.size();
          }

          //現時点のテクスチャを設定する
          SetTexture(mAnimeTextures[static_cast<int>(mCurrFrame)]);
     }
}