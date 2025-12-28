FetchContent_Declare(
	flecs
	GIT_REPOSITORY  https://github.com/SanderMertens/flecs.git
	GIT_TAG		dcbaf278d15379aadea10421bbcbd3c4ead529a3
	FIND_PACKAGE_ARGS
)

FetchContent_Declare(
	JoltPhysics
	GIT_REPOSITORY	https://github.com/jrouwe/JoltPhysics.git
	GIT_TAG 23dadd0e603f1b321142d4c74df07fce85064989
	FIND_PACKAGE_ARGS NAMES JoltPhysics
)

FetchContent_MakeAvailable(
	flecs
	JoltPhysics
)

find_package(flecs CONFIG REQUIRED)
find_package(JoltPhysics CONFIG REQUIRED)


add_library(block block.cpp)
add_library(arena arena.cpp)

add_library(game game.cpp block arena)
