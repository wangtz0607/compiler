#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/ASHR.h"
#include "ir/Type/I32.h"

using namespace ir;

class ASHRTest : public ::testing::Test {
protected:
    std::shared_ptr<ASHR> ashr_;

    ASHRTest() : ashr_(std::make_shared<ASHR>(std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(2))) {
        ashr_->setName("result");
    }
};

TEST_F(ASHRTest, type) {
    EXPECT_EQ(*ashr_->type(), I32());
}

TEST_F(ASHRTest, format) {
    EXPECT_EQ(ashr_->format(), "%result = ashr i32 42, 2");
}

TEST_F(ASHRTest, clone) {
    std::shared_ptr<ASHR> cloned = cast<ASHR>(ashr_->clone());
    EXPECT_EQ(&*ashr_->lhs(), &*cloned->lhs());
    EXPECT_EQ(&*ashr_->rhs(), &*cloned->rhs());
}
