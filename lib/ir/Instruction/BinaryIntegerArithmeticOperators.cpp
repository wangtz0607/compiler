#include <memory>
#include <optional>
#include <utility>

#include "common/OpException.h"
#include "common/ops/Add.h"
#include "common/ops/And.h"
#include "common/ops/ASHR.h"
#include "common/ops/LSHR.h"
#include "common/ops/Mul.h"
#include "common/ops/Or.h"
#include "common/ops/SDiv.h"
#include "common/ops/SHL.h"
#include "common/ops/SRem.h"
#include "common/ops/Sub.h"
#include "common/ops/UDiv.h"
#include "common/ops/URem.h"
#include "common/ops/Xor.h"
#include "ir/Constant.h"
#include "ir/Constant/I16Constant.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Constant/I32Constant.h"
#include "ir/Constant/I64Constant.h"
#include "ir/Constant/I8Constant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/Add.h"
#include "ir/Instruction/And.h"
#include "ir/Instruction/ASHR.h"
#include "ir/Instruction/BinaryIntegerArithmeticOperator.h"
#include "ir/Instruction/LSHR.h"
#include "ir/Instruction/Mul.h"
#include "ir/Instruction/Or.h"
#include "ir/Instruction/SDiv.h"
#include "ir/Instruction/SHL.h"
#include "ir/Instruction/SRem.h"
#include "ir/Instruction/Sub.h"
#include "ir/Instruction/UDiv.h"
#include "ir/Instruction/URem.h"
#include "ir/Instruction/Xor.h"
#include "ir/Type/I1.h"
#include "ir/Type/I16.h"
#include "ir/Type/I32.h"
#include "ir/Type/I64.h"
#include "ir/Type/I8.h"

using namespace ir;

namespace {

template <typename Op>
class ConstantVisitorImpl final : public ConstantVisitor {
public:
    explicit ConstantVisitorImpl(const Constant &lhs) : lhs_(lhs) {}

    std::unique_ptr<Constant> takeResult() {
        return std::move(result_.value());
    }

    void visitI1Constant(const I1Constant &rhs) override {
        visit<I1Constant, I1>(rhs);
    }

    void visitI8Constant(const I8Constant &rhs) override {
        visit<I8Constant, I8>(rhs);
    }

    void visitI16Constant(const I16Constant &rhs) override {
        visit<I16Constant, I16>(rhs);
    }

    void visitI32Constant(const I32Constant &rhs) override {
        visit<I32Constant, I32>(rhs);
    }

    void visitI64Constant(const I64Constant &rhs) override {
        visit<I64Constant, I64>(rhs);
    }

private:
    const Constant &lhs_;
    std::optional<std::unique_ptr<Constant>> result_;

    template <typename Const, typename Ty>
    void visit(const Const &rhs) {
        try {
            result_.emplace(std::make_unique<Const>(Op()(static_cast<const Const &>(lhs_).value(), rhs.value())));
        } catch (const OpException &) {
            result_.emplace(std::make_unique<PoisonValue>(std::make_unique<Ty>()));
        }
    }
};

template <typename Op>
std::unique_ptr<Constant> foldImpl(const BinaryIntegerArithmeticOperator &I) {
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

std::unique_ptr<Constant> Add::fold() const {
    return foldImpl<ops::Add>(*this);
}

std::unique_ptr<Constant> Sub::fold() const {
    return foldImpl<ops::Sub>(*this);
}

std::unique_ptr<Constant> Mul::fold() const {
    return foldImpl<ops::Mul>(*this);
}

std::unique_ptr<Constant> SDiv::fold() const {
    return foldImpl<ops::SDiv>(*this);
}

std::unique_ptr<Constant> UDiv::fold() const {
    return foldImpl<ops::UDiv>(*this);
}

std::unique_ptr<Constant> SRem::fold() const {
    return foldImpl<ops::SRem>(*this);
}

std::unique_ptr<Constant> URem::fold() const {
    return foldImpl<ops::URem>(*this);
}

std::unique_ptr<Constant> And::fold() const {
    return foldImpl<ops::And>(*this);
}

std::unique_ptr<Constant> Or::fold() const {
    return foldImpl<ops::Or>(*this);
}

std::unique_ptr<Constant> Xor::fold() const {
    return foldImpl<ops::Xor>(*this);
}

std::unique_ptr<Constant> SHL::fold() const {
    return foldImpl<ops::SHL>(*this);
}

std::unique_ptr<Constant> LSHR::fold() const {
    return foldImpl<ops::LSHR>(*this);
}

std::unique_ptr<Constant> ASHR::fold() const {
    return foldImpl<ops::ASHR>(*this);
}
