set(test_sources
    test_bit_op.cpp
    test_index_op.cpp)

add_executable(test ${test_sources})

target_compile_features(
   test
   PUBLIC
   cxx_std_17
)

find_package(GTest REQUIRED)

target_link_libraries(
  test
  PUBLIC
  GTest::GTest
  GTest::Main
  register::register
)