#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/ICmp.h"
#include "ir/Type/I1.h"

using namespace ir;

class ICmpTest : public ::testing::Test {
protected:
    std::shared_ptr<ICmp> icmp_;

    ICmpTest()
        : icmp_(std::make_shared<ICmp>(ICmp::Condition::kEQ,
                                       std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        icmp_->setName("result");
    }
};

TEST_F(ICmpTest, type) {
    EXPECT_EQ(*icmp_->type(), I1());
}

TEST_F(ICmpTest, format) {
    EXPECT_EQ(icmp_->format(), "%result = icmp eq i32 42, 43");
}

TEST_F(ICmpTest, clone) {
    std::shared_ptr<ICmp> cloned = cast<ICmp>(icmp_->clone());
    EXPECT_EQ(icmp_->cond(), cloned->cond());
    EXPECT_EQ(&*icmp_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*icmp_->rhs(), &*cloned->rhs());
}
