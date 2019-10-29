# CMakeList.txt : CMake project for PChat, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT F:/boost_1_71_0)
set(Boost_INCLUDE_DIRS ${BOOST_ROOT})
set(Boost_LIBRARY_DIRS ${BOOST_ROOT}/stage/lib/)
set(Boost_LIBRARIES ${BOOST_ROOT}/stage/lib/)
set(Boost_USE_RELEASE_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS thread system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
message(STATUS "Boost version: ${Boost_VERSION}")

if (WIN32)
	add_definitions( -DBOOST_ALL_NO_LIB )
    add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

FILE(GLOB GLOBAL_SRCFILES *.cpp)
FILE(GLOB GLOBAL_HFILES *.h)

FILE(GLOB SERVER_SRCFILES Server/*.cpp)
FILE(GLOB SERVER_HFILES Server/*.h)

FILE(GLOB CLIENT_SRCFILES Client/*.cpp)
FILE(GLOB CLIENT_HFILES Client/*.h)

message(STATUS ${CLIENT_SRCFILES})
message(STATUS ${CLIENT_HFILES})

# Add source to this project's executable.
add_executable ( PChatServer ${SERVER_SRCFILES} ${SERVER_HFILES} ${GLOBAL_SRCFILES} ${GLOBAL_HFILES} )
target_link_libraries( PChatServer ${Boost_LIBRARIES} )

add_executable ( PChatClient ${CLIENT_SRCFILES} ${CLIENT_SRCFILES} ${GLOBAL_SRCFILES} ${GLOBAL_HFILES} )
target_link_libraries( PChatClient ${Boost_LIBRARIES} )