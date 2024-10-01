#include <memory>
#include <unordered_set>

#include <gtest/gtest.h>

#include "ir/BasicBlock.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Instruction/CondBr.h"
#include "ir/Type/Void.h"

using namespace ir;

class CondBrTest : public ::testing::Test {
protected:
    std::shared_ptr<BasicBlock> block1_, block2_;
    std::shared_ptr<CondBr> br_;

    CondBrTest() : block1_(std::make_shared<BasicBlock>()),
                   block2_(std::make_shared<BasicBlock>()),
                   br_(std::make_shared<CondBr>(std::make_unique<I1Constant>(true), block1_, block2_)) {
        block1_->setName("block1");
        block2_->setName("block2");
    }
};

TEST_F(CondBrTest, successors) {
    std::unordered_set<BasicBlock *> successors{&*br_->trueDest(), &*br_->falseDest()};
    EXPECT_EQ(br_->successors(), successors);
}

TEST_F(CondBrTest, type) {
    EXPECT_EQ(*br_->type(), Void());
}

TEST_F(CondBrTest, format) {
    EXPECT_EQ(br_->format(), "br i1 true, label %block1, label %block2");
}

TEST_F(CondBrTest, clone) {
    std::shared_ptr<CondBr> cloned = cast<CondBr>(br_->clone());
    EXPECT_EQ(&*br_->cond(), &*cloned->cond());
    EXPECT_EQ(&*br_->trueDest(), &*cloned->trueDest());
    EXPECT_EQ(&*br_->falseDest(), &*cloned->falseDest());
}
