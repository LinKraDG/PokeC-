cmake_minimum_required(VERSION 3.23)
project(PokeC++ LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(PROJECT_HEADERS 
    include/Utils/Constants.h
    
    include/UI/Text.h

    include/Core/AssetManager.h
    include/Core/Game.h
    include/Core/World.h
    include/Core/Selections.h
    include/Core/Screens/Screens.h
    include/Core/Screens/Badges.h
    include/Core/Screens/Title.h

    include/Panels/Interfaces.h

    include/Gameplay/GameObject.h
    include/Gameplay/JsonsConv.h
    include/Gameplay/Rival.h
    include/Gameplay/Combat.h
    include/Gameplay/Moves/Move.h
    include/Gameplay/Moves/Status_move.h
    include/Gameplay/Moves/Damage_move.h
    include/Gameplay/Pokemons/Pokemon.h




)

set(PROJECT_SOURCES 

    src/Core/AssetManager.cpp
    src/Core/Game.cpp
    src/Core/Text.cpp
    src/Core/World.cpp
    src/Core/Selections.cpp
    src/Core/Screens/Screens.cpp
    src/Core/Screens/Badges.cpp
    src/Core/Screens/Title.cpp

    src/Panels/Interfaces.cpp

    src/main.cpp

    src/Gameplay/Rival.cpp
    src/Gameplay/Combat.cpp
    src/Gameplay/Moves/Move.cpp
    src/Gameplay/Moves/Status_move.cpp
    src/Gameplay/Moves/Damage_move.cpp
    src/Gameplay/Pokemons/Pokemon.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
