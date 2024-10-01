#include <memory>
#include <optional>
#include <utility>

#include "common/ops/FAdd.h"
#include "common/ops/FDiv.h"
#include "common/ops/FMul.h"
#include "common/ops/FRem.h"
#include "common/ops/FSub.h"
#include "ir/Constant.h"
#include "ir/Constant/DoubleConstant.h"
#include "ir/Constant/FloatConstant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/BinaryFloatingArithmeticOperator.h"
#include "ir/Instruction/FAdd.h"
#include "ir/Instruction/FDiv.h"
#include "ir/Instruction/FMul.h"
#include "ir/Instruction/FRem.h"
#include "ir/Instruction/FSub.h"

using namespace ir;

namespace {

template <typename Op>
class ConstantVisitorImpl final : public ConstantVisitor {
public:
    explicit ConstantVisitorImpl(const Constant &lhs) : lhs_(lhs) {}

    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitFloatConstant(const FloatConstant &rhs) override {
        visit<FloatConstant>(rhs);
    }

    void visitDoubleConstant(const DoubleConstant &rhs) override {
        visit<DoubleConstant>(rhs);
    }

private:
    const Constant &lhs_;
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename Const>
    void visit(const Const &rhs) {
        result_.emplace(std::make_unique<Const>(Op()(static_cast<const Const &>(lhs_).value(), rhs.value())));
    }
};

template <typename Op>
std::unique_ptr<Constant> foldImpl(const BinaryFloatingArithmeticOperator &I) {
    const Constant &lhs = static_cast<const Constant &>(*I.lhs()),
                   &rhs = static_cast<const Constant &>(*I.rhs());
    if (dynamic_cast<const PoisonValue *>(&lhs) || dynamic_cast<const PoisonValue *>(&rhs)) {
        return std::make_unique<PoisonValue>(I.type());
    }
    ConstantVisitorImpl<Op> visitor(lhs);
    rhs.accept(visitor);
    return visitor.takeResult();
}

} // namespace

std::unique_ptr<Constant> FAdd::fold() const {
    return foldImpl<ops::FAdd>(*this);
}

std::unique_ptr<Constant> FSub::fold() const {
    return foldImpl<ops::FSub>(*this);
}

std::unique_ptr<Constant> FMul::fold() const {
    return foldImpl<ops::FMul>(*this);
}

std::unique_ptr<Constant> FDiv::fold() const {
    return foldImpl<ops::FDiv>(*this);
}

std::unique_ptr<Constant> FRem::fold() const {
    return foldImpl<ops::FRem>(*this);
}
