cmake_minimum_required(VERSION 2.8)

project(main)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "-g -m64 -Werror")

#set(EXECUTABLE_OUTPUT_PATH "bin")
#set(LIBRARY_OUTPUT_PATH "lib")
set(CMAKE_INSTALL_PREFIX ".")

#$ENV{env_variable} get environment variable
include_directories($ENV{BOOST_INC})
link_directories($ENV{BOOST_LIB})
link_libraries(boost_thread boost_system pthread rt)

add_definitions("-DNDEBUG -Os")

#add all source files into DIR_SRCS
#aux_source_directory(. DIR_SRCS)

set(DIR_SRCS
	main.cpp
	A.cpp
)

add_executable(main ${DIR_SRCS})

#build shared library
#ADD_LIBRARY(hello SHARED ${SHARED_LIBRARY})

#build static library
#ADD_LIBRARY(hello STATIC ${STATIC_LIBRARY})

target_link_libraries(main "uuid")

install(TARGETS main DESTINATION bin)

#message("\${DIR_SRCS}=${DIR_SRCS}")
#message("\${PROJECT_BINARY_PATH}=${PROJECT_BINARY_DIR}")
message("\${CMAKE_INSTALL_PREFIX}=${CMAKE_INSTALL_PREFIX}")
