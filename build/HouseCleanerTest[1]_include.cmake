if(EXISTS "/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseCleanerTest[1]_tests.cmake")
  include("/Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseCleanerTest[1]_tests.cmake")
else()
  add_test(HouseCleanerTest_NOT_BUILT HouseCleanerTest_NOT_BUILT)
endif()
