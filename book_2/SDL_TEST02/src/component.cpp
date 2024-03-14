#include "component.hpp"

Component::Component(Actor* owner,int updateOrder):
mOwner(owner),
mUpdateOrder(updateOrder)
{
}

Component::~Component()
{
}

void Component::Update(float deltaTime){

}