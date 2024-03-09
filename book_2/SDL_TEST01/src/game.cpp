#include "game.hpp"

// コンストラクタ
Game::Game() : 
mIsRunniing(true),
mWidth(1024),
mHeight(720),
mThickness(15),
mPaddleLength(200),
mPaddlePos{static_cast<float>(mThickness),static_cast<float>(mHeight/2 - mPaddleLength/2)},
mBallPos{static_cast<float>(mWidth/2),static_cast<float>(mHeight/2)}
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
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
     { // 他にも様々な初期化がある Audioとか諸々
          printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
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
         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 垂直同期を有効にする（バッファを入れ替えるやつ）
     );

     if (mRenderer == NULL)
     {
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
     if (state[SDL_SCANCODE_ESCAPE])
     {
          mIsRunniing = false;
     }
}

void Game::Draw()
{
     // std::cout << "Drawing the game" << std::endl;

     //背景の描画
     SDL_SetRenderDrawColor(mRenderer,0,0,255,255);
     SDL_RenderClear(mRenderer);
     
     //壁の描画
     DrawShape(0,0,mWidth,mThickness);//上壁
     DrawShape(0,mHeight-mThickness,mWidth,mThickness);//下壁
     //DrawShape(0,0,mThickness,mHeight);//左壁
     DrawShape(mWidth-mThickness,0,mThickness,mHeight);//右壁

     //ボールの描画
     DrawShape(static_cast<int>(mBallPos.x),static_cast<int>(mBallPos.y),mThickness,mThickness);
     
     //制御板の描画
     DrawShape(static_cast<int>(mPaddlePos.x),static_cast<int>(mPaddlePos.y),mThickness,mPaddleLength);

     SDL_RenderPresent(mRenderer);
}

//引数は開始位置x,開始位置y,図形の横幅,図形の縦幅の順番
void Game::DrawShape(int x ,int y,int width,int height){
     SDL_SetRenderDrawColor(mRenderer,255,255,255,255);
     SDL_Rect shape{
          x,//左上隅x
          y,//左上隅y
          width,//図形の横幅
          height//図形の高さ
     };
     SDL_RenderFillRect(mRenderer,&shape);
}

void Game::Update()
{
     std::cout << "Updating game state" << std::endl;
     while (Game::mIsRunniing)
     {
          // ここにフレームに合わせた処理を書く
          Input();
          Draw();
          SDL_Delay(16);
     }
}

void Game::Shutdown()
{
     // レンダラーの破棄
     SDL_DestroyRenderer(mRenderer);
     // ウィンドウの破棄
     SDL_DestroyWindow(mWindow);
     // SDLの終了
     SDL_Quit();
}
