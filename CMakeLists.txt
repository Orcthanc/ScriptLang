cmake_minimum_required( VERSION 3.0 )

project( ScriptLang )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/*.cpp" )

add_library( ${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} )

target_include_directories( ${PROJECT_NAME} PUBLIC "include" )


project( ScriptLangTest )

add_executable( ${PROJECT_NAME} "test/main.cpp" )

target_include_directories( ${PROJECT_NAME} PUBLIC ScriptLang )
target_link_libraries( ${PROJECT_NAME} PUBLIC ScriptLang )
