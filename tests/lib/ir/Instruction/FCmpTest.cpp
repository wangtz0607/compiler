#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/DoubleConstant.h"
#include "ir/Instruction/FCmp.h"
#include "ir/Type/I1.h"

using namespace ir;

class FCmpTest : public ::testing::Test {
protected:
    std::shared_ptr<FCmp> fcmp_;

    FCmpTest() : fcmp_(std::make_shared<FCmp>(FCmp::Condition::kOEQ,
                                              std::make_shared<DoubleConstant>(3.14),
                                              std::make_shared<DoubleConstant>(2.72))) {
        fcmp_->setName("result");
    }
};

TEST_F(FCmpTest, type) {
    EXPECT_EQ(*fcmp_->type(), I1());
}

TEST_F(FCmpTest, format) {
    EXPECT_EQ(fcmp_->format(), "%result = fcmp oeq double 0x40091eb851eb851f, 0x4005c28f5c28f5c3");
}

TEST_F(FCmpTest, clone) {
    std::shared_ptr<FCmp> cloned = cast<FCmp>(fcmp_->clone());
    EXPECT_EQ(fcmp_->cond(), cloned->cond());
    EXPECT_EQ(&*fcmp_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*fcmp_->rhs(), &*cloned->rhs());
}
