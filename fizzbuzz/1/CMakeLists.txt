cmake_minimum_required (VERSION 3.2.3) 

project (fizzbuzz)

set(CMAKE_CXX_FLAGS "-std=c++17")
 
set(EXTRA_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")

set(EXE_FILE ${PROJECT_NAME})

if ("${GMOCK_DIR}" STREQUAL "")
	message(STATUS "No GMOCK_DIR variable set, trying to use system gmock")
	set(GMOCK_DIR "/usr/src/googletest/googlemock")
	set(GMOCK_H_INCLUDE_DIR /usr/include/gmock)
	set(GMOCK_MAIN_DIR ${GMOCK_DIR})
else ("${GMOCK_DIR}" STREQUAL "")
	set(GMOCK_MAIN_DIR "${GMOCK_DIR}")
	set(GMOCK_INCLUDE_DIR "${GMOCK_MAIN_DIR}/include")
	set(GMOCK_H_INCLUDE_DIR "${GMOCK_DIR}/include/gmock")
	set(GTEST_INCLUDE_DIR "${GMOCK_DIR}/../googletest/include")
	include_directories(${GMOCK_INCLUDE_DIR})
	include_directories(${GTEST_INCLUDE_DIR})
endif ("${GMOCK_DIR}" STREQUAL "")

set(GMOCK_INCLUDE "${GMOCK_H_INCLUDE_DIR}/gmock.h")
set(LIB_GMOCK gmock)

if (EXISTS "${GMOCK_INCLUDE}")
	message(STATUS "Using gmock from ${GMOCK_MAIN_DIR}")
else (EXISTS "${GMOCK_INCLUDE}")
	message(FATAL_ERROR "Could not find googlemock in ${GMOCK_DIR}")
endif (EXISTS "${GMOCK_INCLUDE}")

set(GMOCK_INCLUDE_DIR "${GMOCK_DIR}/include/gmock")
set(GMOCK_INCLUDE "${GMOCK_INCLUDE_DIR}/gmock.h")

#project includes
include_directories(${TEST_INC_DIR}/${DEPOT_MOCKS_DIR}/)

#externial libs

set(CMAKE_CXX_FLAGS_DEBUG "${NORMAL_WARNING_FLAGS}")
add_subdirectory(${GMOCK_MAIN_DIR} gmock)
set(CMAKE_CXX_FLAGS_DEBUG "${EXTRA_WARNING_FLAGS}")

add_executable(${EXE_FILE} FizzBuzz.cpp)

target_link_libraries(${EXE_FILE} ${LIB_GMOCK})

