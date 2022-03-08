cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# env = CMAKE_PREFIX_PATH
set(Qt5_DIR ".\\Qt\\lib\\cmake\\Qt5")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Project name
project(ImageCompressor VERSION 1.0)

set(SOURCE_FILES
    "src/AClustering.cpp"
    "src/Cluster.cpp"
    "src/Distance.cpp"
    "src/ImageLoader.cpp"
    "src/KMeansClustering.cpp"
    "src/DbscanClustering.cpp"
    "src/main.cpp"
    "src/Utils.cpp"
)

add_executable(ImageCompressor ${SOURCE_FILES})

# Include directories
target_include_directories(ImageCompressor PUBLIC
                           ${PROJECT_BINARY_DIR}/src/include
)

#set_property(TARGET ImageCompressor PROPERTY WIN32_EXECUTABLE true)

find_package(Qt5 COMPONENTS Gui REQUIRED)

target_link_libraries(ImageCompressor Qt5::Gui)