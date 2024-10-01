#include <cstdint>
#include <memory>
#include <utility>

#include "common/OpException.h"
#include "common/ops/SExt.h"
#include "common/ops/Trunc.h"
#include "common/ops/ZExt.h"
#include "ir/Constant.h"
#include "ir/Constant/I16Constant.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Constant/I32Constant.h"
#include "ir/Constant/I64Constant.h"
#include "ir/Constant/I8Constant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/IntegerCastingOperator.h"
#include "ir/Instruction/SExt.h"
#include "ir/Instruction/Trunc.h"
#include "ir/Instruction/ZExt.h"
#include "ir/Type.h"
#include "ir/Type/I1.h"
#include "ir/Type/I16.h"
#include "ir/Type/I32.h"
#include "ir/Type/I64.h"
#include "ir/Type/I8.h"
#include "ir/TypeVisitor.h"

using namespace ir;

namespace {

template <typename Op, typename ToConst, typename ToTy>
class ConstantVisitorImpl final : public ConstantVisitor {
public:
    std::unique_ptr<Constant> takeResult() {
        return std::move(result_);
    }

    void visitI1Constant(const I1Constant &value) override {
        visit(value);
    }

    void visitI8Constant(const I8Constant &value) override {
        visit(value);
    }

    void visitI16Constant(const I16Constant &value) override {
        visit(value);
    }

    void visitI32Constant(const I32Constant &value) override {
        visit(value);
    }

    void visitI64Constant(const I64Constant &value) override {
        visit(value);
    }

private:
    std::unique_ptr<Constant> result_;

    template <typename FromConst>
    void visit(const FromConst &value) {
        try {
            result_ = std::make_unique<ToConst>(Op()(value.value()));
        } catch (const OpException &) {
            result_ = std::make_unique<PoisonValue>(std::make_unique<ToTy>());
        }
    }
};

template <template <typename To> typename Op>
class TypeVisitorImpl final : public TypeVisitor {
public:
    explicit TypeVisitorImpl(const Constant &value) : value_(value) {}

    std::unique_ptr<Constant> takeResult() {
        return std::move(result_);
    }

    void visitI1(const I1 &) override {
        visit<bool, I1Constant, I1>();
    }

    void visitI8(const I8 &) override {
        visit<int8_t, I8Constant, I8>();
    }

    void visitI16(const I16 &) override {
        visit<int16_t, I16Constant, I16>();
    }

    void visitI32(const I32 &) override {
        visit<int32_t, I32Constant, I32>();
    }

    void visitI64(const I64 &) override {
        visit<int64_t, I64Constant, I64>();
    }

private:
    const Constant &value_;
    std::unique_ptr<Constant> result_;

    template <typename To, typename ToConst, typename ToTy>
    void visit() {
        ConstantVisitorImpl<Op<To>, ToConst, ToTy> visitor;
        value_.accept(visitor);
        result_ = visitor.takeResult();
    }
};

template <template <typename To> typename Op>
std::unique_ptr<Constant> foldImpl(const IntegerCastingOperator &I) {
    const Constant &value = static_cast<const Constant &>(*I.value());
    if (dynamic_cast<const PoisonValue *>(&value)) {
        return std::make_unique<PoisonValue>(I.type());
    }
    TypeVisitorImpl<Op> visitor(value);
    I.type()->accept(visitor);
    return visitor.takeResult();
}

} // namespace

std::unique_ptr<Constant> Trunc::fold() const {
    return foldImpl<ops::Trunc>(*this);
}

std::unique_ptr<Constant> SExt::fold() const {
    return foldImpl<ops::SExt>(*this);
}

std::unique_ptr<Constant> ZExt::fold() const {
    return foldImpl<ops::ZExt>(*this);
}
