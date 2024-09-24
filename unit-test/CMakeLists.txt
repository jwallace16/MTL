cmake_minimum_required(VERSION 3.14)
set(GTEST_NAME TestMatrix)
project(${GTEST_NAME})

# Create a list of full paths to all of the library files
foreach(SRC ${MTL_LIB_SOURCES})
    list(APPEND UT_SOURCES "${PROJECT_SOURCE_DIR}/${SRC}")
endforeach()


include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_SOURCES
    TestMatrix.cpp
    TestSquareMatrix.cpp
    TestVector.cpp
    TestVector3.cpp
    TestQuaternion.cpp
    TestDCM.cpp
    TestEuler.cpp
    TestAxisAngle.cpp
)

# Modern CMake for C++, chapter08/04-gtest/test/CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${GTEST_NAME} ${TEST_SOURCES})
target_link_libraries(TestMatrix GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TestMatrix)