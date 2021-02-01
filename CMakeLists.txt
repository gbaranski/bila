cmake_minimum_required(VERSION 3.5) 
project(bounce_tales)

find_package(SDL2 REQUIRED)
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
  PRIVATE
    ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        include
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)
