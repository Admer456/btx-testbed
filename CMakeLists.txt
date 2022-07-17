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

add_subdirectory( btx-engine )
add_subdirectory( game )
add_subdirectory( launcher )
