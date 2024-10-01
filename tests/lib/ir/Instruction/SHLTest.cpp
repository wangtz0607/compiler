#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/SHL.h"
#include "ir/Type/I32.h"

using namespace ir;

class SHLTest : public ::testing::Test {
protected:
    std::shared_ptr<SHL> shl_;

    SHLTest() : shl_(std::make_shared<SHL>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(2))) {
        shl_->setName("result");
    }
};

TEST_F(SHLTest, type) {
    EXPECT_EQ(*shl_->type(), I32());
}

TEST_F(SHLTest, format) {
    EXPECT_EQ(shl_->format(), "%result = shl i32 42, 2");
}

TEST_F(SHLTest, clone) {
    std::shared_ptr<SHL> cloned = cast<SHL>(shl_->clone());
    EXPECT_EQ(&*shl_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*shl_->rhs(), &*cloned->rhs());
}
