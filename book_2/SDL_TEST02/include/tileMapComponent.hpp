#ifndef TILEMAP_COMPONENT
#define TILEMAP_COMPONENT

#include "spriteComponent.hpp"
#include "spriteComponent.hpp"

class TileMapComponent:public SpriteComponent
{
private:
     int mBlockNum = 0;
     std::string mPath;
public:
     TileMapComponent(class Actor* owner ,int drawOrder = 100,std::string path = "");
     ~TileMapComponent();

     void Draw(SDL_Renderer* renderer) override;

     int GetBlockNum() const{return mBlockNum;}
     void SetBlockNum(int value){mBlockNum = value;}
};
#endif