#ifndef BG_SPRITE_COMPONENT.HPP
#define BG_SPRITE_COMPONENT.HPP

#include "spriteComponent.hpp"

class BGSpriteComponent:public SpriteComponent
{
private:
     struct BGTexture{
          SDL_Texture* mTexture;
          Vector2 mOffset;
     };
     std::vector<BGTexture> mBGTextures;
     Vector2 mScreenSize;
     float mScrollSpeed;
public:
     //描画順序の初期値は下げる
     BGSpriteComponent(class Actor* owner,int drawOrder = 10);
     ~BGSpriteComponent();

     //更新と描画は親からオーバーライドする
     void Update(float deltaTime) override;
     void Draw(SDL_Renderer* renderer) override;
     //背景用のテクスチャを設定する
     void SetBGTextures(const std::vector<SDL_Texture*>& textures);
     //画面サイズとスクロール速度の設定/取得
     void SetScreenSize(const Vector2& size){mScreenSize = size;}
     void SetScrollSpeed(float speed){mScrollSpeed = speed;}
     float GetScrollSpeed() const {return mScrollSpeed;}
};

#endif