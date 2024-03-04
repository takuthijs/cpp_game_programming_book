#include "game.hpp"

//コンストラクタ
Game::Game() : isRunniing(true) {
     std::cout << "セットアップ開始" << std::endl;
     Setup();
}

//デストラクタ
Game::~Game(){
     std::cout << "ゲーム終了" << std::endl;
}

int Game::Setup() {
    std::cout << "Game setup" << std::endl;
    // SDLの初期化
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // ウィンドウの作成
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

void Game::Input() {
     //std::cout << "Processing user input" << std::endl;
}

int Game::Draw() {
    //std::cout << "Drawing the game" << std::endl;

    SDL_Event e;
     // イベントの処理
     while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
               isRunniing = false;
          }
     }

     // ウィンドウに描画などの処理を追加

     // 一時的に適当なウェイト
     SDL_Delay(16);
     return 0;
}

void Game::Update() {
    std::cout << "Updating game state" << std::endl;
    while(Game::isRunniing){
          //ここにフレームに合わせた処理を書く
          Input();
          Draw();
    }

    // ウィンドウの破棄
    SDL_DestroyWindow(window);

    // SDLの終了
    SDL_Quit();
}

