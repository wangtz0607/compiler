#include <memory>
#include <optional>
#include <utility>

#include "common/ops/SIToFP.h"
#include "common/ops/UIToFP.h"
#include "ir/Constant.h"
#include "ir/Constant/DoubleConstant.h"
#include "ir/Constant/FloatConstant.h"
#include "ir/Constant/I16Constant.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Constant/I32Constant.h"
#include "ir/Constant/I64Constant.h"
#include "ir/Constant/I8Constant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/IntegerToFloatingCastingOperator.h"
#include "ir/Instruction/SIToFP.h"
#include "ir/Instruction/UIToFP.h"
#include "ir/Type.h"
#include "ir/Type/Double.h"
#include "ir/Type/Float.h"
#include "ir/TypeVisitor.h"

using namespace ir;

namespace ir {

template <typename Op, typename ResultConst>
class ConstantVisitorImpl : public ConstantVisitor {
public:
    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitI1Constant(const I1Constant &value) override {
        visit<I1Constant>(value);
    }

    void visitI8Constant(const I8Constant &value) override {
        visit<I8Constant>(value);
    }

    void visitI16Constant(const I16Constant &value) override {
        visit<I16Constant>(value);
    }

    void visitI32Constant(const I32Constant &value) override {
        visit<I32Constant>(value);
    }

    void visitI64Constant(const I64Constant &value) override {
        visit<I64Constant>(value);
    }

private:
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename Const>
    void visit(const Const &value) {
        result_.emplace(std::make_unique<ResultConst>(Op()(value.value())));
    }
};

template <template <typename To> typename Op>
class TypeVisitorImpl final : public TypeVisitor {
public:
    explicit TypeVisitorImpl(const Constant &value) : value_(value) {}

    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitFloat(const Float &) override {
        visit<float, FloatConstant>();
    }

    void visitDouble(const Double &) override {
        visit<double, DoubleConstant>();
    }

private:
    const Constant &value_;
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename To, typename ResultConst>
    void visit() {
        ConstantVisitorImpl<Op<To>, ResultConst> visitor;
        value_.accept(visitor);
        result_.emplace(visitor.takeResult());
    }
};

template <template <typename To> typename Op>
std::unique_ptr<Constant> foldImpl(const IntegerToFloatingCastingOperator &I) {
    const Constant &value = static_cast<const Constant &>(*I.value());
    if (dynamic_cast<const PoisonValue *>(&value)) {
        return std::make_unique<PoisonValue>(I.type());
    }
    TypeVisitorImpl<Op> visitor(value);
    I.type()->accept(visitor);
    return visitor.takeResult();
}

} // namespace ir

std::unique_ptr<Constant> SIToFP::fold() const {
    return foldImpl<ops::SIToFP>(*this);
}

std::unique_ptr<Constant> UIToFP::fold() const {
    return foldImpl<ops::UIToFP>(*this);
}
