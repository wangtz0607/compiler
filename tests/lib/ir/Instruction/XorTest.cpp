#include <memory>

#include <gtest/gtest.h>

#include "mini-llvm/ir/Constant/I32Constant.h"
#include "mini-llvm/ir/Instruction/Xor.h"
#include "mini-llvm/ir/Type/I32.h"

using namespace mini_llvm;
using namespace mini_llvm::ir;

class XorTest : public ::testing::Test {
protected:
    std::shared_ptr<Xor> xor_;

    XorTest() : xor_(std::make_shared<Xor>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        xor_->setName("result");
    }
};

TEST_F(XorTest, type) {
    EXPECT_EQ(*xor_->type(), I32());
}

TEST_F(XorTest, format) {
    EXPECT_EQ(xor_->format(), "%result = xor i32 42, 43");
}

TEST_F(XorTest, clone) {
    std::shared_ptr<Xor> cloned = cast<Xor>(xor_->clone());
    EXPECT_EQ(&*xor_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*xor_->rhs(), &*cloned->rhs());
}
