#include <SDL2/SDL_image.h>
#include <algorithm>

#include "game.hpp"
#include "actor.hpp"
#include "spriteComponent.hpp"
#include "ship.hpp"
#include "BGSpriteComponent.hpp"

// コンストラクタ
Game::Game() : mIsRunniing(true),
               mFps(60),
               mTicksCount(0),
               mWidth(1024),
               mHeight(768),
               mUpdatingActors(false),
               mActors{},
               mPendingActors{}
{
     // std::cout << "セットアップ開始" << std::endl;
}

// デストラクタ
Game::~Game()
{
     // std::cout << "ゲーム終了" << std::endl;
}

bool Game::Initialize()
{
     // std::cout << "Game setup" << std::endl;

     // SDLの初期化
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
     { // 他にも様々な初期化がある Audioとか諸々
          printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
          return false;
     }

     // SDL 画像初期化
     if (IMG_Init(IMG_INIT_PNG) == 0)
     {
          printf("SDL could not initialize! SDL_IMG_Error: %s\n", SDL_GetError());
          return false;
     }

     // ウィンドウの作成
     mWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
     if (mWindow == NULL)
     { // もし失敗するとnullptrになるらしい
          printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
          return false;
     }

     // レンダラーの作成
     mRenderer = SDL_CreateRenderer(
         mWindow,                                             // 描画する対象のウィンドウ
         -1,                                                  // ウィンドウが今回は一つなのでデフォルトの-1
         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 垂直同期を有効にする（ディスプレイに描画し終わるまで描画せずに待つこと）
     );

     if (mRenderer == NULL)
     {
          return false;
     }

     LoadData();
     mTicksCount = SDL_GetTicks();
     return true;
}

void Game::Input()
{
     // std::cout << "Processing user input" << std::endl;
     SDL_Event event;

     // キューにイベントがあれば繰り返し
     // ウィンドウのxボタンとか
     while (SDL_PollEvent(&event))
     {
          switch (event.type)
          {
          case SDL_QUIT:
               mIsRunniing = false;
               break;
          default:
               break;
          }
     }

     // キーボードの入力を取得する
     const Uint8 *state = SDL_GetKeyboardState(NULL);
     if (state[SDL_SCANCODE_ESCAPE])
     {
          mIsRunniing = false;
     }

     //船の移動
     mShip->ProcessKeyboard(state);
}

void Game::Draw()
{
     // std::cout << "Drawing the game" << std::endl;

     // 背景の描画
     SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
     SDL_RenderClear(mRenderer);

     // スプライトの配列をループしてそれぞれのDrawを呼ぶ
     for (auto it = mSprites.begin(); it != mSprites.end(); it++)
     {
          (*it)->Draw(mRenderer);
     }

     SDL_RenderPresent(mRenderer);
}

void Game::Update()
{
     // std::cout << "Updating game state" << std::endl;
     while (Game::mIsRunniing)
     {
          // 前のフレームから16msが経過するまで待つ
          while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 1000 / mFps))
               ;

          float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
          mTicksCount = SDL_GetTicks();

          // デルタタイムの上限を設ける
          if (deltaTime > 0.05f)
          {
               deltaTime = 0.05f;
          }

          Input();

          // 全てのアクターを更新
          mUpdatingActors = true;
          for (auto actor : mActors)
          {
               actor->Update(deltaTime);
          }
          mUpdatingActors = false;

          // 待ちアクターズをmActorsに移動
          for (auto pending : mPendingActors)
          {
               mActors.emplace_back(pending);
          }
          mPendingActors.clear();

          // 死んだアクターを一時配列に追加
          std::vector<Actor *> deadActors;

          for (auto actor : mActors)
          {
               if (actor->GetState() == Actor::State::EDead)
               {
                    deadActors.emplace_back(actor);
               }
          }

          for (auto actor : deadActors)
          {
               delete actor;
          }

          Draw();
     }
}

void Game::Shutdown()
{
     UnloadData();//アクターズ削除
	IMG_Quit();

     // レンダラーの破棄
     SDL_DestroyRenderer(mRenderer);
     // ウィンドウの破棄
     SDL_DestroyWindow(mWindow);
     // SDLの終了
     SDL_Quit();
}

void Game::AddActor(Actor *actor)
{
     // アクターの更新中なら待ちの方に追加
     if (mUpdatingActors)
     {
          mPendingActors.emplace_back(actor);
     }
     else
     {
          mActors.emplace_back(actor);
     }
}

void Game::RemoveActor(Actor *actor)
{
     // mPendingActors配列かmActors配列にいるアクターを削除する
     // イテレータを取得
     auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
     if (iter != mPendingActors.end())
     {
          // Swap to end of vector and pop off (avoid erase copies)
          std::iter_swap(iter, mPendingActors.end() - 1);
          mPendingActors.pop_back();
     }

     iter = std::find(mActors.begin(), mActors.end(), actor);
     if (iter != mActors.end())
     {
          std::iter_swap(iter, mActors.end() - 1);
          mActors.pop_back();
     }
}

// 引数は開始位置x,開始位置y,図形の横幅,図形の縦幅の順番
void Game::DrawShape(int x, int y, int width, int height)
{
     SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
     SDL_Rect shape{
         x,     // 左上隅x
         y,     // 左上隅y
         width, // 図形の横幅
         height // 図形の高さ
     };
     SDL_RenderFillRect(mRenderer, &shape);
}

// イメージをロードする処理
SDL_Texture *Game::LoadImage(const char *fileName)
{
     // 画像をファイルからロードする
     // 成功したらSDL_Surfaceのポインタ、失敗したらnullptrを返す
     SDL_Surface *surf = IMG_Load(fileName);
     if (!surf)
     {
          // テクスチャファイルのロードに失敗
          SDL_Log("Failed to load texture file %s", fileName);
          return nullptr;
     }
     SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surf);
     SDL_FreeSurface(surf);
     if (!texture)
     {
          // テクスチャへの変換に失敗
          SDL_Log("Failed to convert surface to texture for %s", fileName);
          return nullptr;
     }

     return texture;
}

void Game::AddSprite(SpriteComponent *sprite)
{
     // ソート済みの配列で挿入場所を見つける
     int myDrawOrder = sprite->GetDrawOrder();

     // 数字が小さいほど先に描画される
     auto iter = mSprites.begin();

     for (; iter != mSprites.end(); ++iter)
     {
          if (myDrawOrder < (*iter)->GetDrawOrder())
          {
               break;
          }
     }

     mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent *sprite)
{
     auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
     mSprites.erase(iter);
}

SDL_Texture *Game::GetTexture(const std::string &fileName)
{
     SDL_Texture *tex = nullptr;
     // Is the texture already in the map?
     auto iter = mTextures.find(fileName);
     if (iter != mTextures.end())
     {
          tex = iter->second;
     }
     else
     {
          // Load from file
          SDL_Surface *surf = IMG_Load(fileName.c_str());
          if (!surf)
          {
               SDL_Log("Failed to load texture file %s", fileName.c_str());
               return nullptr;
          }

          // Create texture from surface
          tex = SDL_CreateTextureFromSurface(mRenderer, surf);
          SDL_FreeSurface(surf);
          if (!tex)
          {
               SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
               return nullptr;
          }

          mTextures.emplace(fileName.c_str(), tex);
     }
     return tex;
}

void Game::LoadData()
{
     // Create player's ship
     mShip = new Ship(this);
     mShip->SetPosition(Vector2(100.0f, 384.0f));
     mShip->SetScale(1.5f);

     // Create actor for the background (this doesn't need a subclass)
     Actor *temp = new Actor(this);
     temp->SetPosition(Vector2(512.0f, 384.0f));
     // Create the "far back" background
     BGSpriteComponent *bg = new BGSpriteComponent(temp);
     bg->SetScreenSize(Vector2(1024.0f, 768.0f));
     std::vector<SDL_Texture *> bgtexs = {
         GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Farback01.png"),
         GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Farback02.png")};
     bg->SetBGTextures(bgtexs);
     bg->SetScrollSpeed(-100.0f);
     // Create the closer background
     bg = new BGSpriteComponent(temp, 50);
     bg->SetScreenSize(Vector2(1024.0f, 768.0f));
     bgtexs = {
         GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Stars.png"),
         GetTexture("cpp_game_programming_book/book_2/SDL_TEST02/assets/Stars.png")};
     bg->SetBGTextures(bgtexs);
     bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
     // Delete actors
     // Because ~Actor calls RemoveActor, have to use a different style loop
     while (!mActors.empty())
     {
          delete mActors.back();
     }

     // Destroy textures
     for (auto i : mTextures)
     {
          SDL_DestroyTexture(i.second);
     }
     mTextures.clear();
}
