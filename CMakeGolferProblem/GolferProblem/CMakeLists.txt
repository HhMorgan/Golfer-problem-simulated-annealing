# CMakeList.txt : CMake project for GolferProblem, include source and define
# project specific logic here.
#

# Add source to this project's executable.
#add_executable (GolferProblem "./source/main.cpp")
cmake_minimum_required(VERSION 3.24)
project(GolferProblem)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FOLDER include)
set(SOURCE_FOLDER source)

set(COMMON_HEADER_FILES
        ${HEADER_FOLDER}/GolferProblem.h
        ${HEADER_FOLDER}/util.h
        ${HEADER_FOLDER}/solver.h
        )
message(STATUS "HEADER_FILES: ${HEADER_FILES}")

set(COMMON_SOURCE_FILES
        ${SOURCE_FOLDER}/main.cpp
        ${SOURCE_FOLDER}/util.cpp
        ${SOURCE_FOLDER}/solver.cpp
        )
message(STATUS "SOURCE_FILES: ${SOURCE_FILES}")


add_library(GolferProblemCommon STATIC ${COMMON_HEADER_FILES} ${COMMON_SOURCE_FILES})
target_include_directories(GolferProblemCommon 
        PUBLIC  ${HEADER_FOLDER}/
        PRIVATE ${SOURCE_FOLDER}/}
)


#add_library(GolferProblemCommon STATIC ${COMMON_HEADER_FILES} ${COMMON_SOURCE_FILES})

# Main executable
add_executable(GolferProblem ${SOURCE_FOLDER}/main.cpp ${SOURCE_FOLDER}/util.cpp ${SOURCE_FOLDER}/solver.cpp) 
#target_link_libraries(GDA2023 PUBLIC GDA2023Common)

# Add folders
target_include_directories(GolferProblem PUBLIC ${HEADER_FOLDER} PRIVATE ${SOURCE_FOLDER})
