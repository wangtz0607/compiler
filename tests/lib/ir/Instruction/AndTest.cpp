#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/And.h"
#include "ir/Type/I32.h"

using namespace ir;

class AndTest : public ::testing::Test {
protected:
    std::shared_ptr<And> and_;

    AndTest() : and_(std::make_shared<And>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        and_->setName("result");
    }
};

TEST_F(AndTest, type) {
    EXPECT_EQ(*and_->type(), I32());
}

TEST_F(AndTest, format) {
    EXPECT_EQ(and_->format(), "%result = and i32 42, 43");
}

TEST_F(AndTest, clone) {
    std::shared_ptr<And> cloned = cast<And>(and_->clone());
    EXPECT_EQ(&*and_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*and_->rhs(), &*cloned->rhs());
}
