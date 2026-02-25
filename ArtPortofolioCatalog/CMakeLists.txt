cmake_minimum_required(VERSION 3.5)
project(ArtPortfolioCatalog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Ensure all necessary Qt components are found for both executables.
# For Qt6, JSON functionality (QJsonDocument, etc.) is part of Qt6::Core.
# So, we only need to specify Widgets and Core.
find_package(Qt6 REQUIRED COMPONENTS Widgets Core) # Removed 'Json' component from here

# --- START: Google Test (Manual Integration) ---
# Add Google Test as a subdirectory to build it directly within your project.
# Ensure the 'googletest-main' folder is placed in your project's root directory.
add_subdirectory(googletest-main)
# --- END: Google Test (Manual Integration) ---


# Main executable for the GUI application
add_executable(ArtPortfolioCatalog
    main.cpp
    Artwork.cpp
    CsvRepository.cpp
    JsonRepository.cpp # JsonRepository uses QJson classes, which are in Qt6::Core
    Command.cpp
    Controller.cpp
    MainWindow.cpp
)

# Link all necessary Qt components for the main GUI application.
target_link_libraries(ArtPortfolioCatalog Qt6::Widgets Qt6::Core) # Removed Qt6::Json from link, as it's part of Core

# --- START: Test executable for automated tests with Google Test ---
add_executable(ArtPortfolioTests
    tests.cpp # Your new Google Test file
    Artwork.cpp # Source files for Artwork and other components used by tests
    CsvRepository.cpp
    Command.cpp
    Controller.cpp
)

# Link the test executable with Google Test libraries and Qt Core (for QString)
target_link_libraries(ArtPortfolioTests GTest::gtest_main GTest::gtest Qt6::Core)
# --- END: Test executable for automated tests with Google Test ---
