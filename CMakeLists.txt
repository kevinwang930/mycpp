cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Mycpp VERSION 1.0)

# specify the C++ standard
add_library(Mycpp_compiler_flags INTERFACE)
target_compile_features(Mycpp_compiler_flags INTERFACE cxx_std_11)
# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 2: Use add_subdirectory() to add MathFunctions to this project
add_subdirectory(MathFunctions)
# add the executable
add_executable(Example tutorial.cxx)

# TODO 3: Use target_link_libraries to link the library to our executable
target_link_libraries(Example PUBLIC MathFunctions Mycpp_compiler_flags)
# TODO 4: Add MathFunctions to Tutorial's target_include_directories()
# Hint: ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Example PUBLIC
        "${PROJECT_BINARY_DIR}"
)
