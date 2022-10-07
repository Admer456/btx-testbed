## Minimum is 3.16 for PCH support
cmake_minimum_required( VERSION 3.16 )

## Project name
project( BTX_TestGame )

## Some property stuff
set_property( GLOBAL PROPERTY USE_FOLDERS ON )
## C++17's filesystem and inline static initialisers are pretty nice
set( CMAKE_CXX_STANDARD 17 )

set( BTX_TEST_GAME_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
set( BTX_BIN_DIRECTORY ${BTX_TEST_GAME_ROOT}/bin )

## BtxCommon is always included first
set( BTX_COMMON_WITH_RHI ON CACHE BOOL "Build ElegyRhi" FORCE )
add_subdirectory( btx-common )
set_target_properties( BtxCommon PROPERTIES FOLDER "Engine" )
set_target_properties( AdmUtils PROPERTIES FOLDER "Libs" )
set_target_properties( ElegyRhi PROPERTIES FOLDER "Libs" )

## Engine
add_subdirectory( btx-engine )

## Game and launcher
add_subdirectory( game )
add_subdirectory( launcher )
