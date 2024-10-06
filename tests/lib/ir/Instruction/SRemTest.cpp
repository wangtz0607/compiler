#include <memory>

#include <gtest/gtest.h>

#include "mini-llvm/ir/Constant/I32Constant.h"
#include "mini-llvm/ir/Instruction/SRem.h"
#include "mini-llvm/ir/Type/I32.h"

using namespace mini_llvm;
using namespace mini_llvm::ir;

class SRemTest : public ::testing::Test {
protected:
    std::shared_ptr<SRem> srem_;

    SRemTest() : srem_(std::make_shared<SRem>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        srem_->setName("result");
    }
};

TEST_F(SRemTest, type) {
    EXPECT_EQ(*srem_->type(), I32());
}

TEST_F(SRemTest, format) {
    EXPECT_EQ(srem_->format(), "%result = srem i32 42, 43");
}

TEST_F(SRemTest, clone) {
    std::shared_ptr<SRem> cloned = cast<SRem>(srem_->clone());
    EXPECT_EQ(&*srem_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*srem_->rhs(), &*cloned->rhs());
}
