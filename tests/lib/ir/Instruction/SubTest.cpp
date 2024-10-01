#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/Sub.h"
#include "ir/Type/I32.h"

using namespace ir;

class SubTest : public ::testing::Test {
protected:
    std::shared_ptr<Sub> sub_;

    SubTest() : sub_(std::make_shared<Sub>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        sub_->setName("result");
    }
};

TEST_F(SubTest, type) {
    EXPECT_EQ(*sub_->type(), I32());
}

TEST_F(SubTest, format) {
    EXPECT_EQ(sub_->format(), "%result = sub i32 42, 43");
}

TEST_F(SubTest, clone) {
    std::shared_ptr<Sub> cloned = cast<Sub>(sub_->clone());
    EXPECT_EQ(&*sub_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*sub_->rhs(), &*cloned->rhs());
}
