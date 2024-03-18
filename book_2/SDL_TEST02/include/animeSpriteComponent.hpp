#ifndef ANIME_SPRITE_COMPONENT_HPP
#define ANIME_SPRITE_COMPONENT_HPP

#include "spriteComponent.hpp"

class AnimeSpriteComponent:public SpriteComponent
{
private:
     //アニメーションでの全てのテクスチャ
     std::vector<SDL_Texture*> mAnimeTextures;
     //現在表示しているフレーム
     float mCurrFrame;
     //アニメーションのフレームレート
     float mAnimFPS;

public:
     AnimeSpriteComponent(class Actor* owner ,int drawOrder = 100);
     ~AnimeSpriteComponent();
     //フレームごとにアニメーションを更新する(componentからオーバーライド)
     void Update(float deltaTime)override;
     //アニメーションに使うテクスチャを設定する
     void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
     //アニメーションフレームレートのゲッターセッター
     float GetAnimFPS() const{return mAnimFPS;}
     void SetAnimFPS(float fps){mAnimFPS = fps;}
};
#endif
