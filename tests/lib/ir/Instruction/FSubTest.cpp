#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/DoubleConstant.h"
#include "ir/Instruction/FSub.h"
#include "ir/Type/Double.h"

using namespace ir;

class FSubTest : public ::testing::Test {
protected:
    std::shared_ptr<FSub> fsub_;

    FSubTest() : fsub_(std::make_shared<FSub>(std::make_shared<DoubleConstant>(3.14),
                                              std::make_shared<DoubleConstant>(2.72))) {
        fsub_->setName("result");
    }
};

TEST_F(FSubTest, type) {
    EXPECT_EQ(*fsub_->type(), Double());
}

TEST_F(FSubTest, format) {
    EXPECT_EQ(fsub_->format(), "%result = fsub double 0x40091eb851eb851f, 0x4005c28f5c28f5c3");
}

TEST_F(FSubTest, clone) {
    std::shared_ptr<FSub> cloned = cast<FSub>(fsub_->clone());
    EXPECT_EQ(&*fsub_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*fsub_->rhs(), &*cloned->rhs());
}
