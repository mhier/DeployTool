cmake_minimum_required(VERSION 2.6)
project(DeployTool)

set(WT_CONNECTOR "Wt::HTTP" CACHE STRING "Connector used (Wt::HTTP or Wt::FCGI)")

set(DeployTool_TARGET wt_project.wt)

set(CMAKE_CXX_FLAGS "-Wno-psabi")

find_package(Boost REQUIRED COMPONENTS program_options signals system filesystem thread)
find_package(wt REQUIRED COMPONENTS http fcgi dbo dbosqlite3 dbomysql)

#add_custom_target(link_target ALL
#                  COMMAND ${CMAKE_COMMAND} -E create_symlink /usr/share/Wt/resources ${CMAKE_BINARY_DIR}/resources)

configure_file(${CMAKE_SOURCE_DIR}/wt_project ${CMAKE_BINARY_DIR}/wt_project COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/DeployTool.css ${CMAKE_BINARY_DIR}/DeployTool.css COPYONLY)

aux_source_directory(${CMAKE_SOURCE_DIR}/src DeployTool_SOURCE)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${DeployTool_TARGET} ${DeployTool_SOURCE})
target_link_libraries(${DeployTool_TARGET} ${WT_CONNECTOR} Wt::DboMySQL Wt::DboSqlite3 ${Boost_LIBRARIES})
