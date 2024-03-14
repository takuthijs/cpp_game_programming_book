#include "game.hpp"

// コンストラクタ
Game::Game(): 
mIsRunniing(true),
mFps(60),
mTicksCount(0),
mWidth(1024),
mHeight(720),
mUpdatingActors(false),
mActors{},
mPendingActors{}
{
     std::cout << "セットアップ開始" << std::endl;
}

// デストラクタ
Game::~Game()
{
     std::cout << "ゲーム終了" << std::endl;
}

bool Game::Initialize()
{
     std::cout << "Game setup" << std::endl;

     // SDLの初期化
     if (SDL_Init(SDL_INIT_VIDEO) < 0){ // 他にも様々な初期化がある Audioとか諸々
          printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
          return false;
     }

     // ウィンドウの作成
     mWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
     if (mWindow == NULL){ // もし失敗するとnullptrになるらしい
          printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
          return false;
     }

     // レンダラーの作成
     mRenderer = SDL_CreateRenderer(
         mWindow,                                             // 描画する対象のウィンドウ
         -1,                                                  // ウィンドウが今回は一つなのでデフォルトの-1
         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 垂直同期を有効にする（ディスプレイに描画し終わるまで描画せずに待つこと）
     );

     if (mRenderer == NULL){
          return false;
     }

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
     if (state[SDL_SCANCODE_ESCAPE]){
          mIsRunniing = false;
     }
}

void Game::Draw()
{
     // std::cout << "Drawing the game" << std::endl;

     //背景の描画
     SDL_SetRenderDrawColor(mRenderer,34,139,34,255);
     SDL_RenderClear(mRenderer);

     SDL_RenderPresent(mRenderer);
}

void Game::Update()
{
     std::cout << "Updating game state" << std::endl;
     while (Game::mIsRunniing)
     {
          //前のフレームから16msが経過するまで待つ
          while(!SDL_TICKS_PASSED(SDL_GetTicks(),mTicksCount + 1000/mFps));

          float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
          mTicksCount = SDL_GetTicks();

          //デルタタイムの上限を設ける
          if(deltaTime >0.05f){
               deltaTime = 0.05f;
          }

          Input();

          //全てのアクターを更新
          mUpdatingActors = true;
          for (auto actor : mActors) {
               actor->Update(deltaTime);
          }
          mUpdatingActors = false;

          //待ちアクターズをmActorsに移動
          for(auto pending : mPendingActors){
               mActors.emplace_back(pending);
          }
          mPendingActors.clear();

          //死んだアクターを一時配列に追加
          std::vector<Actor*> deadActors;

          for(auto actor : mActors){
               if(actor->GetState() == Actor::State::EDead){
                    deadActors.emplace_back(actor);
               }
          }

          for(auto actor : deadActors){
               delete actor;
          }

          Draw();
     }
}

void Game::Shutdown()
{
     //mActorsの削除
     while(!mActors.empty())
     {
          delete mActors.back();
     }

     // レンダラーの破棄
     SDL_DestroyRenderer(mRenderer);
     // ウィンドウの破棄
     SDL_DestroyWindow(mWindow);
     // SDLの終了
     SDL_Quit();
}

void Game::AddActor(Actor* actor){
     //アクターの更新中なら待ちの方に追加
     if(mUpdatingActors){
          mPendingActors.emplace_back(actor);
     }else{
          mActors.emplace_back(actor);
     }
}

void Game::RemoveActor(Actor* actor){
     //mPendingActors配列かmActors配列にいるアクターを削除する
     //イテレータを取得
    auto it = std::find_if(mActors.begin(), mActors.end(),
                         [actor](const Actor* element) {
                              return element == actor;
                         });
    //イテレータが最後の時は最後まで探索して見つかっていないから
    if (it != mActors.end()) {
        mActors.erase(it);
    }

     //mPendingActorsも探す mActorsにあった場合は無駄な処理かも...
     auto it2 = std::find_if(mPendingActors.begin(), mPendingActors.end(),
                         [actor](const Actor* element) {
                              return element == actor;
                         });
     //こっちにあった場合は削除する
     if (it2 != mPendingActors.end()) mPendingActors.erase(it2);
    
}

//引数は開始位置x,開始位置y,図形の横幅,図形の縦幅の順番
void Game::DrawShape(int x ,int y,int width,int height)
{
     SDL_SetRenderDrawColor(mRenderer,255,255,255,255);
     SDL_Rect shape{
          x,//左上隅x
          y,//左上隅y
          width,//図形の横幅
          height//図形の高さ
     };
     SDL_RenderFillRect(mRenderer,&shape);
}
