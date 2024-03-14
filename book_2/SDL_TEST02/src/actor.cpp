#include "actor.hpp"

Actor::Actor(Game* game)
{
     mGame = game;
     mGame->AddActor(this);
}

Actor::~Actor()
{
     mGame->RemoveActor(this);
}

void Actor::Update(float deltaTime){

}