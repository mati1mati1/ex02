add_test([=[HouseLocationTest.Construction]=]  /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseLocationTest [==[--gtest_filter=HouseLocationTest.Construction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HouseLocationTest.Construction]=]  PROPERTIES WORKING_DIRECTORY /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HouseLocationTest.SetDirtLevel]=]  /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseLocationTest [==[--gtest_filter=HouseLocationTest.SetDirtLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HouseLocationTest.SetDirtLevel]=]  PROPERTIES WORKING_DIRECTORY /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HouseLocationTest.GetDirtLevel]=]  /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build/HouseLocationTest [==[--gtest_filter=HouseLocationTest.GetDirtLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HouseLocationTest.GetDirtLevel]=]  PROPERTIES WORKING_DIRECTORY /Users/matanamichy/TAU/2024/cppPrograming/Ex02ProgramingTopics/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  HouseLocationTest_TESTS HouseLocationTest.Construction HouseLocationTest.SetDirtLevel HouseLocationTest.GetDirtLevel)
