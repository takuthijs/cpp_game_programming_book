#include "spriteComponent.hpp"
#include "actor.hpp"
#include "game.hpp"

//ベースクラスの初期化をしないとコンパイラに怒られる
SpriteComponent::SpriteComponent(Actor* owner, int drawOrder): 
Component(owner), 
mDrawOrder(drawOrder), 
mTexture(nullptr), 
mTexWidth(0), //このクラスを継承したやつが設定
mTexHeight(0) //このクラスを継承したやつが設定
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
     mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent :: Draw(SDL_Renderer* renderer)
{
     if(mTexture){
          SDL_Rect r;
          //幅と高さを所有アクターのスケールで拡縮する
          r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
          r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
          //短形の中心を所有アクターに合わせる
          r.x = static_cast<int>(mOwner->GetPosition().x - r.w /2);
          r.y = static_cast<int>(mOwner->GetPosition().y - r.h /2);

          //描画する
          SDL_RenderCopyEx(renderer,
          mTexture,//描画したいテクスチャ
          nullptr,//描画したいテクスチャの範囲
          &r,//出力先の短形
          -Math::ToDegrees(mOwner->GetRotation()),//変換された回転角
          nullptr,//回転中心
          SDL_FLIP_NONE//反転方法
          );
     }
}

void SpriteComponent :: SetTexture(SDL_Texture* texture)
{
     mTexture = texture;
     //テクスチャの幅と高さを求める
     SDL_QueryTexture(texture,nullptr,nullptr,&mTexWidth,&mTexHeight);
}