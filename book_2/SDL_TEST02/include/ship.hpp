#ifndef SHIP_HPP
#define SHIP_HPP

#include "actor.hpp"

class Ship:public Actor
{
private:
     float mRightSpeed;
     float mDownSpeed;
public:
     Ship(class Game* game);
     ~Ship();
     void UpdateActor(float deltaTime)override;
     void ProcessKeyboard(const uint8_t* state);
     float GetRightSpeed() const{return mRightSpeed;}
     float GetDownSpeed() const{return mDownSpeed;}
};
#endif