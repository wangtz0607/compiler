#include <memory>

#include <gtest/gtest.h>

#include "ir/Instruction/Alloca.h"
#include "ir/Type/I32.h"
#include "ir/Type/Ptr.h"

using namespace ir;

class AllocaTest : public ::testing::Test {
protected:
    std::shared_ptr<Alloca> alloca_;

    AllocaTest() : alloca_(std::make_shared<Alloca>(std::make_unique<I32>())) {
        alloca_->setName("ptr");
    }
};

TEST_F(AllocaTest, type) {
    EXPECT_EQ(*alloca_->type(), Ptr());
}

TEST_F(AllocaTest, format) {
    EXPECT_EQ(alloca_->format(), "%ptr = alloca i32");
}

TEST_F(AllocaTest, clone) {
    std::shared_ptr<Alloca> cloned = cast<Alloca>(alloca_->clone());
    EXPECT_EQ(*alloca_->allocatedType(), *cloned->allocatedType());
}
