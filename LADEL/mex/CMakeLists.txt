cmake_minimum_required(VERSION 3.20)
project(LADEL-mex)

# Find the Matlab MEX compiler:
find_package(Matlab REQUIRED COMPONENTS MEX_COMPILER)
add_library(matlab_mex_headers INTERFACE)
target_include_directories(matlab_mex_headers SYSTEM 
    INTERFACE ${Matlab_INCLUDE_DIRS})

# Create a target for compiling a MEX function:
matlab_add_mex(
    NAME ladel_mex                    # Name for use in Matlab
    SRC src/ladel_mex.c               # Source files to compile
        src/ladel_mex_util.c          #
    LINK_TO ladel::ladel              # Dependencies
)
target_include_directories(ladel_mex PRIVATE include)
if (NOT WIN32)
    # Matlab's C++ standard library is too old, so link it statically:
    target_link_options(ladel_mex PUBLIC -static-libstdc++ -static-libgcc)
endif()

# Install the final MEX file
install(FILES $<TARGET_FILE:ladel_mex>
        EXCLUDE_FROM_ALL
        COMPONENT mex_interface
        DESTINATION .)
