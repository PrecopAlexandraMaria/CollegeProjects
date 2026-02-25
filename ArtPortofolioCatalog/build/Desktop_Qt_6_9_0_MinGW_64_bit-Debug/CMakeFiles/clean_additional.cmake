# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ArtPortfolioCatalog_autogen"
  "ArtPortfolioTests_autogen"
  "CMakeFiles\\ArtPortfolioCatalog_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ArtPortfolioCatalog_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\ArtPortfolioTests_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ArtPortfolioTests_autogen.dir\\ParseCache.txt"
  "googletest-main\\googlemock\\CMakeFiles\\gmock_autogen.dir\\AutogenUsed.txt"
  "googletest-main\\googlemock\\CMakeFiles\\gmock_autogen.dir\\ParseCache.txt"
  "googletest-main\\googlemock\\CMakeFiles\\gmock_main_autogen.dir\\AutogenUsed.txt"
  "googletest-main\\googlemock\\CMakeFiles\\gmock_main_autogen.dir\\ParseCache.txt"
  "googletest-main\\googlemock\\gmock_autogen"
  "googletest-main\\googlemock\\gmock_main_autogen"
  "googletest-main\\googletest\\CMakeFiles\\gtest_autogen.dir\\AutogenUsed.txt"
  "googletest-main\\googletest\\CMakeFiles\\gtest_autogen.dir\\ParseCache.txt"
  "googletest-main\\googletest\\CMakeFiles\\gtest_main_autogen.dir\\AutogenUsed.txt"
  "googletest-main\\googletest\\CMakeFiles\\gtest_main_autogen.dir\\ParseCache.txt"
  "googletest-main\\googletest\\gtest_autogen"
  "googletest-main\\googletest\\gtest_main_autogen"
  )
endif()
