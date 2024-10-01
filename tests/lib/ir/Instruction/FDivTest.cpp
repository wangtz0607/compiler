#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/DoubleConstant.h"
#include "ir/Instruction/FDiv.h"
#include "ir/Type/Double.h"

using namespace ir;

class FDivTest : public ::testing::Test {
protected:
    std::shared_ptr<FDiv> fdiv_;

    FDivTest() : fdiv_(std::make_shared<FDiv>(std::make_shared<DoubleConstant>(3.14),
                                              std::make_shared<DoubleConstant>(2.72))) {
        fdiv_->setName("result");
    }
};

TEST_F(FDivTest, type) {
    EXPECT_EQ(*fdiv_->type(), Double());
}

TEST_F(FDivTest, format) {
    EXPECT_EQ(fdiv_->format(), "%result = fdiv double 0x40091eb851eb851f, 0x4005c28f5c28f5c3");
}

TEST_F(FDivTest, clone) {
    std::shared_ptr<FDiv> cloned = cast<FDiv>(fdiv_->clone());
    EXPECT_EQ(&*fdiv_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*fdiv_->rhs(), &*cloned->rhs());
}
