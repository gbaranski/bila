cmake_minimum_required(VERSION 3.5) 
project(bounce_tales)

find_package(SDL2 REQUIRED)
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

if (APPLE)
  target_include_directories(${PROJECT_NAME} 
    PRIVATE
      ${SDL2_INCLUDE_DIRS}
  )
  target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()

if (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
  target_include_directories(
      ${PROJECT_NAME}
      PRIVATE
          include
  )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
