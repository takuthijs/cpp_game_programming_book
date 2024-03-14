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

void Actor:: Update(float deltaTime){

}

void Actor:: UpdateActor(float deltaTime){
     
}

void Actor::UpdateComponent(float deltaTime){

}

void Actor:: AddComponent(class Component* component){

}
void Actor:: RemoveComponent(class Component* component){

}