# FILEPATH: /c:/Users/Oskar/Documents/cp3_project/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(cp3_project)

# Find Qt6
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)



# Find OpenCV
find_package(OpenCV REQUIRED)

set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Create the executable
add_executable(cp3_project ${SOURCES})

# Add the target includes for MY_PROJECT 
target_include_directories(cp3_project PRIVATE ${FORMS_DIR})
target_include_directories(cp3_project PRIVATE ${INCLUDE_DIR})
target_include_directories(cp3_project PRIVATE ${SOURCE_DIR})

# Link Qt6
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# Link OpenCV
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
