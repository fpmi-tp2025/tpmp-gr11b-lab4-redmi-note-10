
cmake_minimum_required(VERSION 3.14)
project(MusicSalon VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_TESTS "Build test programs" ON)

# Find required packages
find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

# Find or fetch nlohmann_json if not found via find_package
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${SQLITE3_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

# Define source files
set(SOURCES
    src/auth/Authentication.cpp
    src/database/Database.cpp
    src/models/User.cpp
    src/models/CompactDisc.cpp
    src/models/Author.cpp
    src/models/Performer.cpp
    src/models/MusicalWork.cpp
    src/models/StockOperation.cpp
    src/ui/ConsoleUI.cpp
    src/utils/DateUtils.cpp
    src/utils/InputUtils.cpp
    src/main.cpp
)

# Define header files
set(HEADERS
    includes/auth/Authentication.h
    includes/database/Database.h
    includes/models/User.h
    includes/models/CompactDisc.h
    includes/models/Author.h
    includes/models/Performer.h
    includes/models/MusicalWork.h
    includes/models/StockOperation.h
    includes/ui/ConsoleUI.h
    includes/utils/DateUtils.h
    includes/utils/InputUtils.h
)

# Create executable
add_executable(music_salon ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(music_salon
    ${SQLITE3_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    nlohmann_json::nlohmann_json
)

# Copy resources to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Testing
if(BUILD_TESTS)
    enable_testing()
    
    # Find GTest
    find_package(GTest REQUIRED)
    include(GoogleTest)
    
    # Test source files
    set(TEST_SOURCES
        tests/auth/TestAuthentication.cpp
        tests/database/TestDatabase.cpp
        tests/models/TestCompactDisc.cpp
    )
    
    # Create test executable
    add_executable(music_salon_tests ${TEST_SOURCES})
    
    # Use modern GTest interface if available
    if(TARGET GTest::gtest AND TARGET GTest::gtest_main)
        target_link_libraries(music_salon_tests
            ${SQLITE3_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            nlohmann_json::nlohmann_json
            GTest::gtest
            GTest::gtest_main
            GTest::gmock
        )
    else()
        # Fallback to old-style interface
        target_link_libraries(music_salon_tests
            ${SQLITE3_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            nlohmann_json::nlohmann_json
            ${GTEST_LIBRARIES}
            ${GTEST_MAIN_LIBRARIES}
        )
        include_directories(${GTEST_INCLUDE_DIRS})
    endif()
    
    # Register tests
    gtest_discover_tests(music_salon_tests)
endif()

# Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Package generators based on platform
if(WIN32)
    set(CPACK_GENERATOR "NSIS;ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop;ZIP")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB;TGZ")
endif()

include(CPack)

# Install targets
install(TARGETS music_salon DESTINATION bin)
install(DIRECTORY resources/ DESTINATION share/music_salon/resources)