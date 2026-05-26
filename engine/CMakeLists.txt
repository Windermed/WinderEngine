cmake_minimum_required(VERSION 3.28)
project(WinderEngine LANGUAGES CXX)

# set for C++ 2017.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG		   3.1.0
)
FetchContent_MakeAvailable(SFML)

# collect all engine related source files
file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.h")

# Automatically reconfigures CMake whenever new files are added to the source folder.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "source")

# mirror source folder structure to visual studio filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX "source" FILES ${SOURCES})

# ensures we always build as a static library.
add_library(WinderEngine STATIC ${SOURCES})

# Links against the SFML modules we need
# we set it to public so that anything that gets linked to WinderEngine gets SFML transitively.
target_link_libraries(WinderEngine PUBLIC
	SFML::Graphics
	SFML::Audio
	SFML::Window
	SFML::System
	SFML::Main
)

# expose the engine headers and SFML headers publicly
target_include_directories(WinderEngine PUBLIC
	source
	source/Core
	source/Engine
	source/Character
	source/Player
	source/Sounds
	source/Textures
	source/UI
)

# enable strict compiler warnings
if(MSVC)
    target_compile_options(WinderEngine PRIVATE /W4)
else()
    target_compile_options(WinderEngine PRIVATE -Wall -Wextra)
endif()