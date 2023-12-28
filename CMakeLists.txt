# FILEPATH: /c:/Users/Oskar/Documents/cp3_project/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(cp3_project)

# Find Qt6
find_package(Qt6 COMPONENTS Core REQUIRED)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add your source files here
set(SOURCES
    src/main.cpp
    # Add your source files here
)

# Add your header files here
set(HEADERS
    # Add your header files here
)

# Add your resource files here
set(RESOURCES
    # Add your resource files here
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link Qt6
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)

# Link OpenCV
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
