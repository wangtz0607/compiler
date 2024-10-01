#include <memory>
#include <optional>
#include <utility>

#include "common/ops/FNeg.h"
#include "ir/Constant.h"
#include "ir/Constant/DoubleConstant.h"
#include "ir/Constant/FloatConstant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/FNeg.h"
#include "ir/Instruction/UnaryFloatingArithmeticOperator.h"

using namespace ir;

namespace {

template <typename Op>
class ConstantVisitorImpl final : public ConstantVisitor {
public:
    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitFloatConstant(const FloatConstant &value) override {
        visit<FloatConstant>(value);
    }

    void visitDoubleConstant(const DoubleConstant &value) override {
        visit<DoubleConstant>(value);
    }

private:
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename Const>
    void visit(const Const &value) {
        result_.emplace(std::make_unique<Const>(Op()(value.value())));
    }
};

template <typename Op>
std::unique_ptr<Constant> foldImpl(const UnaryFloatingArithmeticOperator &I) {
    const Constant &value = static_cast<const Constant &>(*I.value());
    if (dynamic_cast<const PoisonValue *>(&value)) {
        return std::make_unique<PoisonValue>(I.type());
    }
    ConstantVisitorImpl<Op> visitor;
    value.accept(visitor);
    return visitor.takeResult();
}

} // namespace

std::unique_ptr<Constant> FNeg::fold() const {
    return foldImpl<ops::FNeg>(*this);
}
