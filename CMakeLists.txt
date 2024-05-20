cmake_minimum_required(VERSION 2.8.5...3.29.2)
project(poker-nal)

# Debug mode
set(FLAGS "-Wall -Wextra")
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

option(USE_EMOJI "Use emoji when printing cards" ON)
if (USE_EMOJI)
    message("Using emojis")
else()
    message("Not using emojis")
    add_definitions(-DNOEMOJI)
endif()

# CMake settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS} -g3 -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS} -O3")

# Find packages
find_package(Doxygen OPTIONAL_COMPONENTS dot)

# =-=-=-=-=-=-= DOCS =-=-=-=-=-=-=
if (DOXYGEN_FOUND)
    message("Doxygen found. You can use `make docs`")

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Doxygen not found. You won't be able to use `make docs`")
endif (DOXYGEN_FOUND)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${SOURCE_DIR}/card.cpp
    ${SOURCE_DIR}/deck.cpp
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/player.cpp
    ${SOURCE_DIR}/utils.cpp
)


# =-=-=-=-=-=-= EXECUTABLE =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# =-=-=-=-=-=-= TESTS =-=-=-=-=-=-=

set(
    SOURCE_FILES_TEST
    ${SOURCE_FILES}
    ${SOURCE_DIR}/main.cpp
)

# Adding executables
add_executable(poker-nal-tests ${SOURCE_FILES_TEST})

# Libraries
target_link_directories(
    poker-nal-tests
    PRIVATE
)
target_link_libraries(
    poker-nal-tests
    PRIVATE
    stdc++
)

# Header files
target_include_directories(
    poker-nal-tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# =-=-=-=-=-=-= SERVER TEST =-=-=-=-=-=-=
# Source files
set (
    SOURCE_SERV_FILES
    ${SOURCE_DIR}/server-test.cpp
    ${SOURCE_DIR}/server.cpp
)

# Adding executable
add_executable(poker-nal-server ${SOURCE_SERV_FILES})

# Libraries
target_link_directories(
    poker-nal-server
    PRIVATE
)
target_link_libraries(
    poker-nal-server
    PRIVATE
    stdc++
)

# Header files
target_include_directories(
    poker-nal-server
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# =-=-=-=-=-=-= CLIENT TEST =-=-=-=-=-=-=
# Source files
set (
    SOURCE_CLIENT_FILES
    ${SOURCE_DIR}/client-test.cpp
    ${SOURCE_DIR}/client.cpp
)

# Adding executable
add_executable(poker-nal-client ${SOURCE_CLIENT_FILES})

# Libraries
target_link_directories(
    poker-nal-client
    PRIVATE
)
target_link_libraries(
    poker-nal-client
    PRIVATE
    stdc++
)

# Header files
target_include_directories(
    poker-nal-client
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
