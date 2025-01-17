
## game/*
set( GAME_SOURCES 
    Main.cpp
    Precompiled.hpp )

## Folder organisation
source_group( TREE ${BTX_TEST_GAME_ROOT} FILES ${GAME_SOURCES} )

## Project
add_library( GameLibrary SHARED
    ${GAME_SOURCES} )

## game.dll
set_target_properties( GameLibrary PROPERTIES
    OUTPUT_NAME "Game"
    FOLDER "Game" )

## Includes
target_include_directories( GameLibrary PRIVATE
    ${ADMUTIL_INCLUDE_DIRETORY}
    ${BTX_TEST_GAME_ROOT}/game
    ${BTX_TEST_GAME_ROOT}/btx-engine )

## Link against adm-utils and whatever
## else you may need here
target_link_libraries( GameLibrary
    AdmUtils
    BtxCommon )

## Precompiled headers
target_precompile_headers( GameLibrary PRIVATE 
    ${BTX_TEST_GAME_ROOT}/game/Precompiled.hpp )

if ( NOT DEFINED BTX_BIN_DIRECTORY )
    set( BTX_BIN_DIRECTORY ${BTX_TEST_GAME_ROOT}/bin )
endif()

## Output here
install( TARGETS GameLibrary
    RUNTIME DESTINATION ${BTX_BIN_DIRECTORY}/game/plugins/GameLibrary
    LIBRARY DESTINATION ${BTX_BIN_DIRECTORY}/game/plugins/GameLibrary )

if ( WIN32 )
    ## Place PDBs on Windows
    install( FILES $<TARGET_PDB_FILE:GameLibrary> 
        DESTINATION ${BTX_BIN_DIRECTORY}/game OPTIONAL )
endif()

## Copy the configs
install( FILES ${BTX_TEST_GAME_ROOT}/assets/engineConfig.json
    DESTINATION ${BTX_BIN_DIRECTORY} )

install( FILES ${BTX_TEST_GAME_ROOT}/assets/gameConfig.json
    DESTINATION ${BTX_BIN_DIRECTORY}/game )

install( FILES ${BTX_TEST_GAME_ROOT}/assets/plugins.json
    DESTINATION ${BTX_BIN_DIRECTORY}/game/plugins/GameLibrary )
