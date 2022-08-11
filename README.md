# 🏇 Horse Race 🏇
_Horse Race_ is a parallax-scrolling game in which you control a horse; the horse goes through a 6-races grand prix to win the Horse Trophy. 🏆

<img src="img/readme/race.gif?raw=true" width="320" height="240"> &nbsp;
<img src="img/readme/horse_menu.gif?raw=true" width="320" height="240"> &nbsp;

<img src="img/readme/ranking.gif?raw=true" width="320" height="240"> &nbsp;
<img src="img/readme/podium.gif?raw=true" width="320" height="240"> &nbsp;

### Quickstart
Before compilation, you must link the SFML and SQLite (both static and dynamic) libraries. The output file should be placed in the same directory as the img, music and font folders. Dynamic libraries (.dll files or .so files) and the database (mydb.db file) should also stay there.
There are other several location options to link dynamic libraries (other than putting them directly in the working directory):
- system shared libraries directory
- the directory from which the application is loaded
- PATH environment variable directories (Windows)
- LD_LIBRARY_PATH environment variable directories (Linux)

### Dependencies
- SFML 2.5.1
- SQLite 3.35.5

### CMake
Here's a ready CMake file to build the project.
##### Windows
```CMake
cmake_minimum_required(VERSION 3.20)
project(horserace)

set(CMAKE_CXX_STANDARD 14)
set(SFML_INC_DIR YOUR_PATH_TO_SFML/include)
include_directories(${SFML_INC_DIR})
include_directories(./include)

add_executable(horserace
        main.cpp
        src/AnimatedSprite.cpp
        src/Animation.cpp
        src/Game.cpp
        src/Horse.cpp
        src/HorseMenu.cpp
        src/Layer.cpp
        src/Menu.cpp
        src/Observer.cpp
        src/Obstacle.cpp
        src/PropertyManager.cpp
        src/Race.cpp
        src/RaceMenu.cpp
        src/RankingMenu.cpp
        src/StateDemo.cpp
        src/StateFinalResult.cpp
        src/StateHorseMenu.cpp
        src/StateRace.cpp
        src/Track.cpp
        src/Utility.cpp
        src/Weather.cpp)

target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-graphics-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-window-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-system-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SFML/lib/sfml-audio-d.lib)
target_link_libraries(horserace YOUR_PATH_TO_SQLITE/sqlite3.lib)
```
##### Linux
```CMake
cmake_minimum_required(VERSION 3.20)
project(horserace)

set(CMAKE_CXX_STANDARD 14)
set(SFML_INC_DIR YOUR_PATH_TO_SFML_INCLUDES)
include_directories(${SFML_INC_DIR})
include_directories(./include)

add_executable(horserace
        main.cpp
        src/AnimatedSprite.cpp
        src/Animation.cpp
        src/Game.cpp
        src/Horse.cpp
        src/HorseMenu.cpp
        src/Layer.cpp
        src/Menu.cpp
        src/Observer.cpp
        src/Obstacle.cpp
        src/PropertyManager.cpp
        src/Race.cpp
        src/RaceMenu.cpp
        src/RankingMenu.cpp
        src/StateDemo.cpp
        src/StateFinalResult.cpp
        src/StateHorseMenu.cpp
        src/StateRace.cpp
        src/Track.cpp
        src/Utility.cpp
        src/Weather.cpp)

target_link_libraries(horserace sfml-graphics)
target_link_libraries(horserace sfml-window)
target_link_libraries(horserace sfml-system)
target_link_libraries(horserace sfml-audio)
target_link_libraries(horserace YOUR_PATH_TO_SQLITE/sqlite3)
```
