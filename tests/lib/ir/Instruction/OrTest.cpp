#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/Or.h"
#include "ir/Type/I32.h"

using namespace ir;

class OrTest : public ::testing::Test {
protected:
    std::shared_ptr<Or> or_;

    OrTest() : or_(std::make_shared<Or>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        or_->setName("result");
    }
};

TEST_F(OrTest, type) {
    EXPECT_EQ(*or_->type(), I32());
}

TEST_F(OrTest, format) {
    EXPECT_EQ(or_->format(), "%result = or i32 42, 43");
}

TEST_F(OrTest, clone) {
    std::shared_ptr<Or> cloned = cast<Or>(or_->clone());
    EXPECT_EQ(&*or_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*or_->rhs(), &*cloned->rhs());
}
