# CMakeList.txt : CMake project for GolferProblem, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GolferProblem "./source/GolferProblem.cpp" "./include/GolferProblem.h" "./source/main.cpp" "include/util.h" "source/util.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GolferProblem PROPERTY CXX_STANDARD 20)
endif()

set(HEADER_FOLDER include)
set(SOURCE_FOLDER source)

set(COMMON_HEADER_FILES
        ${HEADER_FOLDER}/GolferProblem.h
        ${HEADER_FOLDER}/util.h

        )
message(STATUS "HEADER_FILES: ${HEADER_FILES}")

set(COMMON_SOURCE_FILES
        ${SOURCE_FOLDER}/main.cpp
        ${SOURCE_FOLDER}/GolferProblem.cpp
        ${SOURCE_FOLDER}/util.cpp
        )
message(STATUS "SOURCE_FILES: ${SOURCE_FILES}")



# TODO: Add tests and install targets if needed.
