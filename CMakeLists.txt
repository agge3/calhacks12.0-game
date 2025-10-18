cmake_minimum_required(VERSION 4.1)
project(falling-blocks
	DESCRIPTION "falling blocks!"
	LANGUAGES CXX)

add_executable(falling-blocks)

file(GLOB SRC *.cpp)
target_sources(falling-blocks PRIVATE ${SRC})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_compile_features(falling-blocks PRIVATE cxx_std_20)
target_link_libraries(falling-blocks PRIVATE
	SFML::Graphics
	SFML::Window
	SFML::System
)
