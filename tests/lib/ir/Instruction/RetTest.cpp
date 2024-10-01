#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/Ret.h"
#include "ir/Type/Void.h"

using namespace ir;

class RetTest : public ::testing::Test {
protected:
    std::shared_ptr<Ret> ret1_, ret2_;

    RetTest() : ret1_(std::make_shared<Ret>()), ret2_(std::make_shared<Ret>(std::make_shared<I32Constant>(42))) {}
};

TEST_F(RetTest, type) {
    EXPECT_EQ(*ret1_->type(), Void());
    EXPECT_EQ(*ret2_->type(), Void());
}

TEST_F(RetTest, format) {
    EXPECT_EQ(ret1_->format(), "ret void");
    EXPECT_EQ(ret2_->format(), "ret i32 42");
}

TEST_F(RetTest, clone) {
    std::shared_ptr<Ret> cloned1 = cast<Ret>(ret1_->clone()), cloned2 = cast<Ret>(ret2_->clone());
    EXPECT_EQ(&*ret1_->value(), &*cloned1->value());
    EXPECT_EQ(&*ret2_->value(), &*cloned2->value());
}
