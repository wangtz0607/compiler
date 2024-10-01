#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/DoubleConstant.h"
#include "ir/Instruction/FAdd.h"
#include "ir/Type/Double.h"

using namespace ir;

class FAddTest : public ::testing::Test {
protected:
    std::shared_ptr<FAdd> fadd_;

    FAddTest()
        : fadd_(std::make_shared<FAdd>(std::make_shared<DoubleConstant>(3.14),
                                       std::make_shared<DoubleConstant>(2.72))) {
        fadd_->setName("result");
    }
};

TEST_F(FAddTest, type) {
    EXPECT_EQ(*fadd_->type(), Double());
}

TEST_F(FAddTest, format) {
    EXPECT_EQ(fadd_->format(), "%result = fadd double 0x40091eb851eb851f, 0x4005c28f5c28f5c3");
}

TEST_F(FAddTest, clone) {
    std::shared_ptr<FAdd> cloned = cast<FAdd>(fadd_->clone());
    EXPECT_EQ(&*fadd_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*fadd_->rhs(), &*cloned->rhs());
}
