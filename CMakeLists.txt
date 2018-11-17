cmake_minimum_required(VERSION 3.12)
project(liftoff)

set(CMAKE_CXX_STANDARD 17)
set(CC=/usr/bin/g++)
set(CMAKE_MODULE_PATH .)

add_executable(liftoff src/main.cpp src/Game.cpp src/Game.h src/Platform.cpp src/Platform.h src/Ball.cpp src/Ball.h src/Controls.cpp src/Controls.h)
target_sources(liftoff PRIVATE src/main.cpp)

include_directories(/usr/local/lib)
include_directories(/usr/local/include)
include_directories(/usr/local/Cellar)
include_directories(/Library/Frameworks)

find_package(OPENGL REQUIRED)
if (OPENGL_FOUND)
    target_include_directories(liftoff PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(liftoff PRIVATE ${OPENGL_LIBRARIES})
endif ()

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    target_include_directories(liftoff PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(liftoff PRIVATE ${SDL2_LIBRARIES})
endif ()

find_package(SDL2_IMAGE REQUIRED)
if (SDL2_IMAGE_FOUND)
    target_include_directories(liftoff PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(liftoff PRIVATE ${SDL2_IMAGE_LIBRARIES})
endif ()
