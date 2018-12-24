cmake_minimum_required(VERSION 3.8)

project(SnakeSFML VERSION 0.0.0.1 LANGUAGES C CXX)



set(HEADERS
        entity/entity.h
        snake.h
        snakejoint.h)
set(SOURCES
        entity/entity.cpp
        main.cpp
        snake.cpp
        snakejoint.cpp)


add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)



target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
