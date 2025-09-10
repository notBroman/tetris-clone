add_subdirectory(renderer)
add_subdirectory(game)
link_libraries(renderer game)
add_executable(tetris-clone main.cpp)
