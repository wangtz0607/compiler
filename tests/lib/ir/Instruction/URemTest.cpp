#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/URem.h"
#include "ir/Type/I32.h"

using namespace ir;

class URemTest : public ::testing::Test {
protected:
    std::shared_ptr<URem> urem_;

    URemTest() : urem_(std::make_shared<URem>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        urem_->setName("result");
    }
};

TEST_F(URemTest, type) {
    EXPECT_EQ(*urem_->type(), I32());
}

TEST_F(URemTest, format) {
    EXPECT_EQ(urem_->format(), "%result = urem i32 42, 43");
}

TEST_F(URemTest, clone) {
    std::shared_ptr<URem> cloned = cast<URem>(urem_->clone());
    EXPECT_EQ(&*urem_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*urem_->rhs(), &*cloned->rhs());
}
