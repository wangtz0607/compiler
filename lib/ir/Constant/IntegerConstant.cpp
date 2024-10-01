#include "ir/Constant/IntegerConstant.h"

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>

#include "common/ops/Trunc.h"
#include "ir/Constant/I16Constant.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Constant/I32Constant.h"
#include "ir/Constant/I64Constant.h"
#include "ir/Constant/I8Constant.h"
#include "ir/Type/I1.h"
#include "ir/Type/I16.h"
#include "ir/Type/I32.h"
#include "ir/Type/I64.h"
#include "ir/Type/I8.h"
#include "ir/TypeVisitor.h"

using namespace ir;

namespace {

class TypeVisitorImpl final : public TypeVisitor {
public:
    explicit TypeVisitorImpl(int64_t value) : value_(value) {}

    std::unique_ptr<IntegerConstant> takeResult() {
        return std::move(result_.value());
    }

    void visitI1(const I1 &) override {
        visit<I1Constant, bool>();
    }

    void visitI8(const I8 &) override {
        visit<I8Constant, int8_t>();
    }

    void visitI16(const I16 &) override {
        visit<I16Constant, int16_t>();
    }

    void visitI32(const I32 &) override {
        visit<I32Constant, int32_t>();
    }

    void visitI64(const I64 &) override {
        visit<I64Constant, int64_t>();
    }

private:
    int64_t value_;
    std::optional<std::unique_ptr<IntegerConstant>> result_;

    template <typename Const, typename To>
    void visit() {
        result_.emplace(std::make_unique<Const>(ops::Trunc<To>()(value_)));
    }
};

} // namespace

std::unique_ptr<IntegerConstant> ir::createIntegerConstant(std::unique_ptr<Type> type, int64_t value) {
    TypeVisitorImpl visitor(value);
    type->accept(visitor);
    return visitor.takeResult();
}
