#include <memory>

#include <gtest/gtest.h>

#include "ir/Constant/I32Constant.h"
#include "ir/Instruction/Alloca.h"
#include "ir/Instruction/Store.h"
#include "ir/Type/I32.h"
#include "ir/Type/Void.h"

using namespace ir;

class StoreTest : public ::testing::Test {
protected:
    std::shared_ptr<Alloca> alloca_;
    std::shared_ptr<Store> store_;

    StoreTest() : alloca_(std::make_shared<Alloca>(std::make_unique<I32>())),
                  store_(std::make_shared<Store>(std::make_shared<I32Constant>(42), alloca_)) {
        alloca_->setName("ptr");
    }
};

TEST_F(StoreTest, type) {
    EXPECT_EQ(*store_->type(), Void());
}

TEST_F(StoreTest, format) {
    EXPECT_EQ(store_->format(), "store i32 42, ptr %ptr");
}

TEST_F(StoreTest, clone) {
    std::shared_ptr<Store> cloned = cast<Store>(store_->clone());
    EXPECT_EQ(&*store_->value(), &*cloned->value());
    EXPECT_EQ(&*store_->ptr(), &*cloned->ptr());
}
