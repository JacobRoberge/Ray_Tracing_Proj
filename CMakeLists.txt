cmake_minimum_required (VERSION 3.18)

project (Ray_Tracing_Proj LANGUAGES C CXX)
#project (EvoInt LANGUAGES CXX)

#set(VCPKG_TARGET_TRIPLET x64-windows)
#set(DCMAKE_GENERATOR_PLATFORM x64)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)







# default build type is Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)


# Source files

SET(Main_dir ${CMAKE_CURRENT_SOURCE_DIR}/source/main)



file(GLOB_RECURSE Main_source "${Main_dir}/*.h" "${Main_dir}/*.cpp")

           
enable_testing()

# source/main.cpp
add_executable (${PROJECT_NAME} source/main.cpp)


add_library(Main_lib STATIC ${Main_source})
target_link_libraries(${PROJECT_NAME} PRIVATE Main_lib)
target_include_directories(${PROJECT_NAME} PRIVATE "${Main_dir}/headers")


######################################################
#TESTING ###########
###############################################
SET(tests_dir ${CMAKE_CURRENT_SOURCE_DIR}/source/tests)
file(GLOB_RECURSE tests_source "${tests_dir}/*.h" "${tests_dir}/*.cpp")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable (test_exe ${tests_source})

# target_link_libraries(test_exe PRIVATE net_lib)
# target_include_directories(test_exe PRIVATE "${net_dir}/headers")

# target_link_libraries(test_exe PRIVATE game_lib)
# target_include_directories(test_exe PRIVATE "${games_dir}/headers")


include(GoogleTest)
gtest_discover_tests(test_exe)
##target_link_libraries(test_exe PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
target_link_libraries(test_exe gtest_main)


add_test(NAME test_exe COMMAND my_test)

