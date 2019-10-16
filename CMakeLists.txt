cmake_minimum_required(VERSION 3.2)

project(HeyiDataStructure)

include_directories(.)

aux_source_directory(. DIR_SRCS)

add_executable(testtree debug/TestTree.cpp ${DIR_SRCS})
