#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I64Constant.h"
#include "ir/Instruction/Trunc.h"
#include "ir/Type/I32.h"

using namespace ir;

class TruncTest : public ::testing::Test {
protected:
    std::shared_ptr<Trunc> trunc_;

    TruncTest() : trunc_(std::make_shared<Trunc>(std::make_shared<I64Constant>(42), std::make_unique<I32>())) {
        trunc_->setName("result");
    }
};

TEST_F(TruncTest, type) {
    EXPECT_EQ(*trunc_->type(), I32());
}

TEST_F(TruncTest, format) {
    EXPECT_EQ(trunc_->format(), "%result = trunc i64 42 to i32");
}

TEST_F(TruncTest, clone) {
    std::shared_ptr<Trunc> cloned = cast<Trunc>(trunc_->clone());
    EXPECT_EQ(&*trunc_->value(), &*cloned->value());
    EXPECT_EQ(*trunc_->type(), *cloned->type());
}
