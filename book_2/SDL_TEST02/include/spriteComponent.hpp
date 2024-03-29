#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "component.hpp"
#include <string>

class SpriteComponent : public Component
{
public:
     //描画順序（drawOrder）が低いほど遠くに置かれる
     SpriteComponent(class Actor* owner,int drawOrder = 100);
     ~SpriteComponent();
     virtual void Draw(SDL_Renderer* renderer);
     virtual void SetTexture(SDL_Texture* texture);
     int GetDrawOrder() const{return mDrawOrder;};
     int GetTexWidth() const{return mTexWidth;};
     int GetTexHeight() const{return mTexHeight;};

protected:
     //描画するテクスチャ
     SDL_Texture* mTexture;
     //描画順序
     int mDrawOrder;
     //テクスチャの幅と高さ
     int mTexWidth;
     int mTexHeight;
};

#endif