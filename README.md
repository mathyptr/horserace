# 🏇 Horse Race 🏇
_Horse race_ is a parallax-scrolling game in which you control a horse; the horse goes through a 4-races grand prix to win the Horse Trophy. 🏆

### Quickstart
Before compilation, you must link the SFML and SQLite (both static and dynamic) libraries. The output file should be placed in the same directory as the img, music and font folders. Dynamic libraries (DLL files) and the database (mydb.db file) should also stay there.

### Dependencies
- SFML 2.5.1
- SQLite 3.35.5

### CMake
```CMake
cmake_minimum_required(VERSION 3.20)
project(horserace)

set(CMAKE_CXX_STANDARD 14)
set(SFML_INC_DIR YOUR_PATH_TO_SFML/include)
include_directories(${SFML_INC_DIR})


add_executable(horserace
        main.cpp
        Challenge.cpp
        Component.cpp
        Game.cpp
        Horse.cpp
        Layer.cpp
        Menu.cpp
        propertyManager.cpp)

target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-graphics-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-window-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-system-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-audio-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SQLITE/sqlite3.lib)
```
