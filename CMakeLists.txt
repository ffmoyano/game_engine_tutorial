cmake_minimum_required(VERSION 3.25)
project(game_engine_tutorial)

set(CMAKE_CXX_STANDARD 23)
set(SOURCES src/main.cpp src/game/Game.cpp src/logger/Logger.h src/logger/Logger.cpp src/component/TransformComponent.h src/system/MovementSystem.h src/ECS/ECS.h src/ECS/ECS.cpp)
set(SDL2_INCLUDE_DIR C:/SDL2/x86_64-w64-mingw32/include/SDL2)
set(SDL2_LIBRARY_DIR C:/SDL2/x86_64-w64-mingw32/lib)
set(ROOT ./)



include_directories(${SDL2_INCLUDE_DIR} libs/glm libs/imgui libs/lua libs/sol libs/spdlog)
link_directories(${SDL2_LIBRARY_DIR} libs/glm libs/imgui libs/lua libs/sol libs/spdlog)

add_executable(game_engine_tutorial ${SOURCES})
add_custom_command(TARGET game_engine_tutorial POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:game_engine_tutorial>/assets)


target_link_libraries(${PROJECT_NAME} -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a SDL2.dll SDL2_image.dll SDL2_ttf.dll SDL2_mixer.dll lua54.dll -mwindows)
