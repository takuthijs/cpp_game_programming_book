#include "animeSpriteComponent.hpp"

AnimeSpriteComponent::AnimeSpriteComponent(Actor* owner,int drawOrder):
SpriteComponent(owner,drawOrder),
mCurrFrame(0),
mAnimFPS(24.0f)
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

void AnimeSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimeTextures = textures;
	if (mAnimeTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimeTextures[0]);
	}
}