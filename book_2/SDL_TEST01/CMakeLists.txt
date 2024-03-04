# CMakeのバージョンを指定
cmake_minimum_required(VERSION 3.10)
# プロジェクト名を指定
project(SecondGame)

# C++17を指定
set(CMAKE_CXX_STANDARD 17)

# パッケージを見つける
# 今回の場合2Dキャンバスを描画するもの
#find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SDL2 REQUIRED COMPONENTS SDL2)

# ソースファイルのリストを作成
set(SOURCE_FILES
     src/main.cpp
     src/game.cpp
     src/dynamicArray.cpp
)

# ヘッダファイルのリストを作成
set(HEADER_FILES
     include/game.hpp
     include/dynamicArray.hpp
)

# 実行可能ファイルのビルド設定
add_executable(my_game ${SOURCE_FILES} ${HEADER_FILES})

# インクルードディレクトリを指定
target_include_directories(my_game PRIVATE include)

# リンクするライブラリを指定
#target_link_libraries(my_game PRIVATE sfml-graphics)
target_link_libraries(my_game PRIVATE SDL2::SDL2)
