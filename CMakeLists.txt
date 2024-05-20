cmake_minimum_required(VERSION 3.6)
project(fftw_wrapper)

# --- Version Control ---
set(FFTW_WRAPPER_MAJOR_VERSION 0)
set(FFTW_WRAPPER_MINOR_VERSION 0)
set(FFTW_WRAPPER_PATCH_VERSION 1)
set(PROJECT_VERSION ${FFTW_WRAPPER_MAJOR_VERSION}.${FFTW_WRAPPER_MINOR_VERSION}.${FFTW_WRAPPER_PATCH_VERSION})
message(STATUS "${PROJECT_NAME} version ${PROJECT_VERSION}")

# --- Compiler Flags ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast")

# --- Add Dependencies ---
find_package(spdlog REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(FFTW REQUIRED fftw3 IMPORTED_TARGET)
find_library(
    FFTW_DOUBLE_THREADS_LIB
    NAMES "fftw3_threads"
    PATHS ${PKG_FFTW_LIBRARY_DIRS} ${LIB_INSTALL_DIR}
)

if(FFTW_DOUBLE_THREADS_LIB)
    set(FFTW_DOUBLE_THREADS_LIB_FOUND TRUE)
    set(FFTW_LIBRARIES ${FFTW_LIBRARIES} ${FFTW_DOUBLE_THREADS_LIB})
    add_library(FFTW::DoubleThreads INTERFACE IMPORTED)
    set_target_properties(FFTW::DoubleThreads
        PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${FFTW_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${FFTW_DOUBLE_THREADS_LIB}"
    )
else()
    set(FFTW_DOUBLE_THREADS_LIB_FOUND FALSE)
endif()

set(FFTW_WRAPPER_SRCS
    src/fft.cpp
)
set(FFTW_WRAPPER_HDRS
    include/fftw_wrapper/fft.hpp
)

# --- Create the C++ Library ---
add_library(${PROJECT_NAME} ${FFTW_WRAPPER_SRCS} ${FFTW_WRAPPER_HDRS})
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    spdlog::spdlog
    PkgConfig::FFTW
    ${FFTW_DOUBLE_THREADS_LIB}
)

# --- Add Executables ---
if(NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS true)
endif()

if(BUILD_TESTS)
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
endif()

# # --- Compile and Make Visible to other packages ---
# include(CMakePackageConfigHelpers)

# set(PKG_NAME ${PROJECT_NAME})
# configure_package_config_file(
# "cmake/${PROJECT_NAME}Config.cmake.in"
# "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
# INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
# PATH_VARS PKG_NAME
# NO_SET_AND_CHECK_MACRO
# NO_CHECK_REQUIRED_COMPONENTS_MACRO
# )

# install(
# FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
# "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
# DESTINATION lib/cmake/${PROJECT_NAME}
# )