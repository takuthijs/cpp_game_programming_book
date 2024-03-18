#include "ship.hpp"
#include "animeSpriteComponent.hpp"
#include "game.hpp"

Ship::Ship(Game *game)
    :Actor(game),
    mRightSpeed(0),
    mDownSpeed(0)
{
     // Create an animated sprite component
	AnimeSpriteComponent* asc = new AnimeSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Ship01.png"),
		game->GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Ship02.png"),
		game->GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Ship03.png"),
		game->GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

Ship::~Ship()
{
}

void Ship::UpdateActor(float deltaTime)
{
     Actor::UpdateActor(deltaTime);

     // 速度とデルタタイムに基づいて位置を更新する
     Vector2 pos = GetPosition();
     pos.x += mRightSpeed * deltaTime;
     pos.y += mDownSpeed * deltaTime;
     // 位置を画面の左半分に制限する
     if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}

	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}

     SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
}