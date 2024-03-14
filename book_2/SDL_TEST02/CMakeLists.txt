# CMakeのバージョンを指定
cmake_minimum_required(VERSION 3.10)
# プロジェクト名を指定
project(SecondGame)

# C++17を指定
set(CMAKE_CXX_STANDARD 17)

#SDLの画像ライブラリのパス
set(SDL2_IMAGE_INCLUDE_DIRS /usr/local/opt/sdl2_image/include)

# パッケージを見つける
# 今回の場合2Dキャンバスを描画するもの
#find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
message(STATUS "ステータス: ${SDL2_IMAGE_INCLUDE_DIRS}")


# ソースファイルのリストを作成
set(SOURCE_FILES
     src/main.cpp
     src/game.cpp
     src/actor.cpp
     src/component.cpp
     src/spriteComponent.cpp
)

# ヘッダファイルのリストを作成
set(HEADER_FILES
     include/game.hpp
     include/actor.hpp
     include/component.hpp
     include/spriteComponent.hpp
)

# 実行可能ファイルのビルド設定
add_executable(my_game ${SOURCE_FILES} ${HEADER_FILES})

# インクルードディレクトリを指定
target_include_directories(my_game PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# プリプロセッサの定義を追加
add_definitions(-D_THREAD_SAFE)

# リンクするライブラリを指定
#target_link_libraries(my_game PRIVATE sfml-graphics)
# リンクするライブラリを指定
target_link_libraries(my_game PRIVATE ${SDL2_LIBRARIES} /usr/local/lib/libSDL2_image.dylib)
