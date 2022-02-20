set(test_sources
    test_bit_op.cpp
    test_index_op.cpp)

add_executable(tests ${test_sources})

target_compile_features(
  tests
  PUBLIC
  cxx_std_11
)

find_package(GTest REQUIRED)

target_link_libraries(
  tests
  PUBLIC
  GTest::GTest
  GTest::Main
  register::register
)

add_test(
  NAME tests
  COMMAND tests)