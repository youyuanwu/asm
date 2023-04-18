# import google test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


project(asm-test CXX)

add_executable("asm-all-tests" test.cpp)

target_link_libraries("asm-all-tests" PRIVATE asm gtest_main)
target_compile_features("asm-all-tests" PRIVATE cxx_std_17)

add_test(NAME "all-tests" COMMAND asm-all-tests)