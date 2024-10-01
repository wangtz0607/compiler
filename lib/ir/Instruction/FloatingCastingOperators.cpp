#include <memory>
#include <optional>
#include <utility>

#include "common/OpException.h"
#include "common/ops/FPExt.h"
#include "common/ops/FPTrunc.h"
#include "ir/Constant.h"
#include "ir/Constant/DoubleConstant.h"
#include "ir/Constant/FloatConstant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/FloatingCastingOperator.h"
#include "ir/Instruction/FPExt.h"
#include "ir/Instruction/FPTrunc.h"
#include "ir/Type.h"
#include "ir/Type/Double.h"
#include "ir/Type/Float.h"
#include "ir/TypeVisitor.h"

using namespace ir;

namespace {

template <typename Op, typename ToConst, typename ToTy>
class ConstantVisitorImpl final : public ConstantVisitor {
public:
    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitFloatConstant(const FloatConstant &value) override {
        visit(value);
    }

    void visitDoubleConstant(const DoubleConstant &value) override {
        visit(value);
    }

private:
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename FromConst>
    void visit(const FromConst &value) {
        try {
            result_.emplace(std::make_unique<ToConst>(Op()(value.value())));
        } catch (const OpException &) {
            result_.emplace(std::make_unique<PoisonValue>(std::make_unique<ToTy>()));
        }
    }
};

template <template <typename To> typename Op>
class TypeVisitorImpl : public TypeVisitor {
public:
    explicit TypeVisitorImpl(const Constant &value) : value_(value) {}

    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitFloat(const Float &) override {
        visit<float, FloatConstant, Float>();
    }

    void visitDouble(const Double &) override {
        visit<double, DoubleConstant, Double>();
    }

private:
    const Constant &value_;
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename To, typename ToConst, typename ToTy>
    void visit() {
        ConstantVisitorImpl<Op<To>, ToConst, ToTy> visitor;
        value_.accept(visitor);
        result_.emplace(visitor.takeResult());
    }
};

template <template <typename To> typename Op>
std::unique_ptr<Constant> foldImpl(const FloatingCastingOperator &I) {
    const Constant &value = static_cast<const Constant &>(*I.value());
    if (dynamic_cast<const PoisonValue *>(&value)) {
        return std::make_unique<PoisonValue>(I.type());
    }
    TypeVisitorImpl<Op> visitor(value);
    I.type()->accept(visitor);
    return visitor.takeResult();
}

} // namespace

std::unique_ptr<Constant> FPTrunc::fold() const {
    return foldImpl<ops::FPTrunc>(*this);
}

std::unique_ptr<Constant> FPExt::fold() const {
    return foldImpl<ops::FPExt>(*this);
}
