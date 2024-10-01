#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/DoubleConstant.h"
#include "ir/Instruction/FNeg.h"
#include "ir/Type/Double.h"

using namespace ir;

class FNegTest : public ::testing::Test {
protected:
    std::shared_ptr<FNeg> fneg_;

    FNegTest() : fneg_(std::make_shared<FNeg>(std::make_shared<DoubleConstant>(3.14))) {
        fneg_->setName("result");
    }
};

TEST_F(FNegTest, type) {
    EXPECT_EQ(*fneg_->type(), Double());
}

TEST_F(FNegTest, format) {
    EXPECT_EQ(fneg_->format(), "%result = fneg double 0x40091eb851eb851f");
}

TEST_F(FNegTest, clone) {
    std::shared_ptr<FNeg> cloned = cast<FNeg>(fneg_->clone());
    EXPECT_EQ(&*fneg_->value(), &*cloned->value());
}
