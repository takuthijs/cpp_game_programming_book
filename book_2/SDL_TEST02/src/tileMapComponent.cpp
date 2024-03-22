#include "tileMapComponent.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TileMapComponent::TileMapComponent(Actor* owner ,int drawOrder):
SpriteComponent(owner,drawOrder)
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent ::Draw(SDL_Renderer *renderer)
{
     if (mTexture)
     {
          // 以下処理からはfor文で実行
          // csvデータを読み込み　TileMapのクラスを作成してその中の関数にする予定
          std::string path = "cpp_game_programming_book/book_2/SDL_TEST02/assets/MapLayer1.csv";
          std::ifstream file(path.c_str());
          std::string line;
          std::vector<std::vector<std::string>> data;

          while (std::getline(file, line))
          {
               std::vector<std::string> row;
               std::stringstream ss(line);
               std::string cell;

               while (std::getline(ss, cell, ','))
               {
                    row.push_back(cell);
               }

               data.push_back(row);
          }

          SDL_Rect r;
          int blockSize = static_cast<int>(mTexWidth * mOwner->GetScale() / 8);
          mBlockNum = 0;

          // CSVデータを処理する
          for (const auto &row : data)
          {
               for (const auto &cell : row)
               {
                    //セルの文字を数字に変換
                    int cell_value = std::stoi(cell);

                    //-1の場合は描画以降の処理はしない
                    if(cell_value < 0)continue;

                    // 幅と高さを所有アクターのスケールで拡縮する
                    r.w = blockSize;
                    r.h = blockSize;
                    // 左上から右に順番に移動していく、移動量はsrcrect.w分ずつ
                    r.x = blockSize * (mBlockNum%8);
                    r.y = blockSize * (mBlockNum/8);
                    
                    // ここでSDL_RenderCopyExのsrcrectパラメーターを使ってその番号に応じた位置を与えて描画する処理を繰り返す
                    //std::cout << cell << ",";
                    SDL_Rect srcrect;
                    // 幅と高さを所有アクターのスケールで拡縮する
                    // 画像サイズも768pxなので画面幅と同じ、一行に8個のブロックが書かれています。
                    srcrect.w = blockSize;
                    srcrect.h = blockSize;

                    srcrect.x = mBlockNum * cell_value%8;
                    srcrect.y = mBlockNum * cell_value/8;

                    // 描画する
                    SDL_RenderCopyEx(renderer,
                                   mTexture,                                // 描画したいテクスチャ
                                   &srcrect,                                // 描画したいテクスチャの範囲
                                   &r,                                      // 出力先の短形
                                   -Math::ToDegrees(mOwner->GetRotation()), // 変換された回転角
                                   nullptr,                                 // 回転中心
                                   SDL_FLIP_NONE                            // 反転方法
                    );

                    mBlockNum ++;
               }
               std::cout << std::endl;
          }

     }
}