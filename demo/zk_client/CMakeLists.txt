cmake_minimum_required (VERSION 2.8)

project(Demo)

set(CMAKE_CXX_COMPILER "clang++")

add_definitions("-g -Wall -O0")

include_directories($ENV{STT_INC} $ENV{BOOST_INC} /usr/include/mysql)
link_directories($ENV{STT_LIB} $ENV{BOOST_LIB} /usr/lib64/mysql)

#file(GLOB PRO_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.proto)
#find_program(PROTOC protoc)
#set(PROTOC_C_OUT_FLAG --cpp_out)
#foreach(PRO_FILE ${PRO_FILES})
#	get_filename_component(PRO_NAME ${PRO_FILE} NAME_WE)
##message("PRO_NAME ${PRO_NAME}")
#	set(CUR_PRO_GEN ${PRO_NAME}.pb.h, ${PRO_NAME}.pb.cc)
#	set(PRO_GEN ${PRO_GEN} ${PRO_NAME}.pb.cc)
#	add_custom_command(OUTPUT ${CUR_PRO_GEN} COMMAND ${PROTOC} ${PRO_FILE} ${PROTOC_C_OUT_FLAG} . DEPENDS ${PROTOC} ${PRO_FILE} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#endforeach(PRO_FILE ${PRO_FILES})

#message("this is from message ${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#set(SRC_FILES ${SRC_FILES} ${PRO_GEN})
#message("this is from message ${CMAKE_CURRENT_SOURCE_DIR},  ${SRC_FILES}")

add_executable(main ${SRC_FILES})
target_link_libraries(main netmsg Common MsgClientLib ServerBase CommonBase RedisDB MySqlDB Jsoncpp textlog boost_thread boost_chrono boost_system pthread boost_regex rt hiredis mysqlclient zookeeper_mt)

