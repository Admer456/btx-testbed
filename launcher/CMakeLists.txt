
set( BTX_LAUNCHER_SOURCES
        Main.cpp
        Precompiled.hpp )

## Folder organisation
source_group( TREE ${BTX_TEST_GAME_ROOT} FILES ${BTX_LAUNCHER_SOURCES} )

## Project
add_executable( EngineLauncher
        ${BTX_LAUNCHER_SOURCES} )

## btx.exe
set_target_properties( EngineLauncher PROPERTIES
        OUTPUT_NAME "TestGame"
        FOLDER "Game" )

## Includes
target_include_directories( EngineLauncher PRIVATE
        ${ADMUTIL_INCLUDE_DIRETORY}
        ${BTX_TEST_GAME_ROOT}
        ${BTX_TEST_GAME_ROOT}/btx-engine )

## Link against SDL2 libs and others
target_link_libraries( EngineLauncher 
        AdmUtils BtxCommon )

## Precompiled headers
target_precompile_headers( EngineLauncher PRIVATE 
        ${BTX_TEST_GAME_ROOT}/launcher/Precompiled.hpp )

if ( NOT DEFINED BTX_BIN_DIRECTORY )
        set( BTX_BIN_DIRECTORY ${BTX_TEST_GAME_ROOT}/bin )
endif()

## Output here
install( TARGETS EngineLauncher
        RUNTIME DESTINATION ${BTX_BIN_DIRECTORY}
        LIBRARY DESTINATION ${BTX_BIN_DIRECTORY} )

if ( WIN32 )
        ## On Windows, place PDBs as well
        install( FILES $<TARGET_PDB_FILE:EngineLauncher> 
                DESTINATION ${BTX_BIN_DIRECTORY} OPTIONAL )
endif()

