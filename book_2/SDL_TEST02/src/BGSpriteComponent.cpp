#include "BGSpriteComponent.hpp"

BGSpriteComponent::BGSpriteComponent(Actor *owner, int drawOrder = 10)
    : SpriteComponent(owner, drawOrder),
    mScrollSpeed(0.0f)
{
}

BGSpriteComponent::~BGSpriteComponent()
{
}

void BGSpriteComponent::Update(float deltaTime)
{
     SpriteComponent::Update(deltaTime);
     for (auto &bg : mBGTextures)
     {
          // xのオフセットを更新
          bg.mOffset.x += mScrollSpeed * deltaTime;
          // もし画面から完全に出たら、オフセットを最後の背景テクスチャの右にリセットする
          if (bg.mOffset.x < -mScreenSize.x)
          {
               //bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
               bg.mOffset.x += mScreenSize.x * mBGTextures.size() ;
          }
     }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer)
{
     // Draw each background texture
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*> &textures)
{
     int count = 0;
     for (auto tex : textures)
     {
          BGTexture temp;
          temp.mTexture = tex;
          // それぞれのテクスチャは画面幅分のオフセットを持つ
          temp.mOffset.x = count * mScreenSize.x;
          temp.mOffset.y = 0;
          mBGTextures.emplace_back(temp);
          count++;
     }
}