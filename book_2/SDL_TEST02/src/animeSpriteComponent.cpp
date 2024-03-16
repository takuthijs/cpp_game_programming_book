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

void AnimeSpriteComponent::Update(float deltaTime){

}