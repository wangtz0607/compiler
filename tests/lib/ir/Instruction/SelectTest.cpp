#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I1Constant.h"
#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/Select.h"
#include "ir/Type/I32.h"
#include "utils/Memory.h"

using namespace ir;

class SelectTest : public ::testing::Test {
protected:
    std::shared_ptr<Select> select_;

    SelectTest()
        : select_(std::make_shared<Select>(
            std::make_shared<I1Constant>(true),
            std::make_shared<I32Constant>(42), std::make_shared<I32Constant>(43))) {
        select_->setName("result");
    }
};

TEST_F(SelectTest, type) {
    EXPECT_EQ(*select_->type(), I32());
}

TEST_F(SelectTest, format) {
    EXPECT_EQ(select_->format(), "%result = select i1 true, i32 42, i32 43");
}

TEST_F(SelectTest, clone) {
    std::shared_ptr<Select> cloned = cast<Select>(select_->clone());
    EXPECT_EQ(&*select_->cond(), &*cloned->cond());
    EXPECT_EQ(&*select_->trueValue(), &*cloned->trueValue());
    EXPECT_EQ(&*select_->falseValue(), &*cloned->falseValue());
}
