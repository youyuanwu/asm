#include <cstdlib>
#include <iostream>
#include "gtest/gtest.h"
#include "asm.h"


TEST(ExampleParse, Ok) {
    EXPECT_TRUE(true);
}

TEST(test,ok){
    int i = 99;


    std::function<void(void)> f = []() {
        std::cout << "hello" << std::endl;
    };
    saveAndRun(f);


    // stack should not be corrupted
    EXPECT_EQ(99,i);
}