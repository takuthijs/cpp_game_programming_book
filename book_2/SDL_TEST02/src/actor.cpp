#include "actor.hpp"
#include "game.hpp"
#include "component.hpp"

Actor::Actor(Game* game)
{
     mGame = game;
     mGame->AddActor(this);
}

Actor::~Actor()
{
     mGame->RemoveActor(this);
     while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor:: Update(float deltaTime)
{
     if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor:: UpdateActor(float deltaTime)
{

}

void Actor::UpdateComponents(float deltaTime)
{
     for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor:: AddComponent(class Component* component)
{
     int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;iter != mComponents.end();++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	mComponents.insert(iter, component);
}
void Actor:: RemoveComponent(class Component* component)
{
     auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}