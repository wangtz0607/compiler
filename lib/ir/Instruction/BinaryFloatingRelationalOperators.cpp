#include <memory>
#include <optional>
#include <utility>

#include "common/ops/OEQ.h"
#include "common/ops/OGE.h"
#include "common/ops/OGT.h"
#include "common/ops/OLE.h"
#include "common/ops/OLT.h"
#include "common/ops/ONE.h"
#include "ir/Constant.h"
#include "ir/Constant/DoubleConstant.h"
#include "ir/Constant/FloatConstant.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/ConstantVisitor.h"
#include "ir/Instruction/BinaryFloatingRelationalOperator.h"
#include "ir/Instruction/FCmp.h"

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
        result_.emplace(std::make_unique<I1Constant>(Op()(static_cast<const Const &>(lhs_).value(), rhs.value())));
    }
};

template <typename Op>
std::unique_ptr<Constant> foldImpl(const BinaryFloatingRelationalOperator &I) {
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

std::unique_ptr<Constant> FCmp::fold() const {
    using enum Condition;
    switch (cond()) {
        case kOEQ: return foldImpl<ops::OEQ>(*this);
        case kONE: return foldImpl<ops::ONE>(*this);
        case kOLT: return foldImpl<ops::OLT>(*this);
        case kOGT: return foldImpl<ops::OGT>(*this);
        case kOLE: return foldImpl<ops::OLE>(*this);
        case kOGE: return foldImpl<ops::OGE>(*this);
        default: std::unreachable();
    }
}
