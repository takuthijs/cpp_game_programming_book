#include "game.hpp"

// コンストラクタ
Game::Game() : 
mIsRunniing(true),
mFps(60),
mTicksCount(0),
mWidth(1024),
mHeight(720),
mThickness(15)
{
     std::cout << "セットアップ開始" << std::endl;
     //パドルをリストに追加
     mPaddles.push_back({{static_cast<float>(mThickness),static_cast<float>(mHeight/2 - 200/2)},200,0});
     mPaddles.push_back({{static_cast<float>(mWidth - mThickness*2),static_cast<float>(mHeight/2 - 200/2)},200,0});

     //ボールをリストに追加
     mBalls.push_back({{static_cast<float>(mWidth/2),static_cast<float>(mHeight/2)},{-200.0f,235.0f}});
     mBalls.push_back({{static_cast<float>(mWidth/2),static_cast<float>(mHeight/2)},{200.0f,-235.0f}});
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
         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 垂直同期を有効にする（描画中のものが描画し終わるまで次のフレームに入れ替えないやつ）
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
     bool addBall = false;
     while (SDL_PollEvent(&event))
     {
          switch (event.type)
          {
          case SDL_QUIT:
               mIsRunniing = false;
               break;
          case SDL_KEYDOWN:
               if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    addBall = true;
               }
               break;
          case SDL_KEYUP:
               if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    addBall = false;
                }
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

     //方向リセット
     mPaddles[0].dir = 0;
     mPaddles[1].dir = 0;
     //左側パドルの移動方向
     if(state[SDL_SCANCODE_W]){
          mPaddles[0].dir -= 1;
     }

     if(state[SDL_SCANCODE_S]){
          mPaddles[0].dir += 1;
     }

     //右側パドル移動方向
     if(state[SDL_SCANCODE_I]){
          mPaddles[1].dir -= 1;
     }

     if(state[SDL_SCANCODE_K]){
          mPaddles[1].dir += 1;
     }

     //スペースボタンでボール追加
     if(state[SDL_SCANCODE_SPACE]){
          // 乱数エンジンの生成
          std::random_device rd;
          std::mt19937 gen(rd());
          std::uniform_real_distribution<float> distX(-100.0f, 300.0f);
          std::uniform_real_distribution<float> distY(-100.0f, 300.0f);

          if(addBall){
               // ランダムな位置と速度を生成してボールを追加
               mBalls.push_back({{static_cast<float>(mWidth / 2), static_cast<float>(mHeight / 2)},{distX(gen), distY(gen)}});
               addBall = false;
          }
     }

}

void Game::Draw()
{
     // std::cout << "Drawing the game" << std::endl;

     //背景の描画
     SDL_SetRenderDrawColor(mRenderer,34,139,34,255);
     SDL_RenderClear(mRenderer);
     
     //壁の描画
     DrawShape(0,0,mWidth,mThickness);//上壁
     DrawShape(0,mHeight-mThickness,mWidth,mThickness);//下壁
     //DrawShape(0,0,mThickness,mHeight);//左壁
     //DrawShape(mWidth-mThickness,0,mThickness,mHeight);//右壁

     //ボールの描画
     std::for_each(mBalls.begin() , mBalls.end(), [this](Ball ball){ DrawShape(static_cast<int>(ball.pos.x),static_cast<int>(ball.pos.y),mThickness,mThickness);});
     
     //パドルの描画
     std::for_each(mPaddles.begin() , mPaddles.end(), [this](Paddle paddle){DrawShape(static_cast<int>(paddle.pos.x),static_cast<int>(paddle.pos.y),mThickness,paddle.length);});

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
          //前のフレームから16msが経過するまで待つ
          while(!SDL_TICKS_PASSED(SDL_GetTicks(),mTicksCount + 1000/mFps));

          float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
          mTicksCount = SDL_GetTicks();

          //デルタタイムの上限を設ける
          if(deltaTime >0.05f){
               deltaTime = 0.05f;
          }

          Input();
          
          //パドルの移動
          for (int i = 0; i < mPaddles.size(); i++)
          {
               if(mPaddles[i].dir != 0)
               {
                    mPaddles[i].pos.y += mPaddles[i].dir * 300.0f * deltaTime;
                    //パドルの移動制限
                    if(mPaddles[i].pos.y > mHeight - mPaddles[i].length - mThickness)mPaddles[i].pos.y = mHeight - mPaddles[i].length - mThickness;
                    if(mPaddles[i].pos.y < mThickness)mPaddles[i].pos.y = mThickness;
               }
          }

          //ボールの移動
          for(int i = 0; i < mBalls.size();i++){
               mBalls[i].pos.x += mBalls[i].vel.x * deltaTime;
               mBalls[i].pos.y += mBalls[i].vel.y * deltaTime;
               //壁に当たっていたらボールの位置を修正して向きを変える
               //下壁
               if(mBalls[i].pos.y > mHeight - mThickness-mThickness/2 && mBalls[i].pos.y > 0)
               {
                    mBalls[i].pos.y = mHeight - mThickness-mThickness/2;
                    mBalls[i].vel.y *= -1;
               }
               //上壁
               if(mBalls[i].pos.y < mThickness-mThickness/2 && mBalls[i].pos.y < 0)
               {
                    mBalls[i].pos.y = mThickness-mThickness/2;
                    mBalls[i].vel.y *= -1;
               }

               //左パドルに当たったかどうか
               if(mBalls[i].pos.x <= mPaddles[0].pos.x + mThickness
               && mBalls[i].pos.x >= mPaddles[0].pos.x 
               && mPaddles[0].pos.y + mPaddles[0].length >= mBalls[i].pos.y 
               && mPaddles[0].pos.y <= mBalls[i].pos.y 
               && mBalls[i].vel.x < 0)
               {
                    mBalls[i].vel.x *= -1;
               }

               //右パドルに当たったかどうか
               if(mBalls[i].pos.x <= mPaddles[1].pos.x
               && mBalls[i].pos.x + mThickness >= mPaddles[1].pos.x 
               && mPaddles[1].pos.y + mPaddles[1].length >= mBalls[i].pos.y 
               && mPaddles[1].pos.y <= mBalls[i].pos.y 
               && mBalls[i].vel.x > 0)
               {
                    mBalls[i].vel.x *= -1;
               }

               //ボールが範囲外に行った場合、ボールを削除
               if(mBalls[i].pos.x < -mWidth /4 || mBalls[i].pos.x > mWidth + mWidth /4 )
               {
                    auto it = mBalls.begin()+i;
                    mBalls.erase(it);
               }
               //右壁
               // if(mBallPos.x > mWidth-mThickness-mThickness/2 && mBallvel.x>0)
               // {
               //      mBallPos.x = mWidth-mThickness-mThickness/2;
               //      mBallvel.x *= -1;
               // }
          }
          
          Draw();
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
