#include "ir/Constant/FloatingConstant.h"

#include <memory>
#include <optional>
#include <utility>

#include "common/ops/FPTrunc.h"
#include "ir/Constant/DoubleConstant.h"
#include "ir/Constant/FloatConstant.h"
#include "ir/Type/Double.h"
#include "ir/Type/Float.h"
#include "ir/TypeVisitor.h"

using namespace ir;

namespace {

class TypeVisitorImpl final : public TypeVisitor {
public:
    explicit TypeVisitorImpl(double value) : value_(value) {}

    std::unique_ptr<FloatingConstant> takeResult() {
        return std::move(result_.value());
    }

    void visitFloat(const Float &) override {
        visit<FloatConstant, float>();
    }

    void visitDouble(const Double &) override {
        visit<DoubleConstant, double>();
    }

private:
    double value_;
    std::optional<std::unique_ptr<FloatingConstant>> result_;

    template <typename Const, typename To>
    void visit() {
        result_.emplace(std::make_unique<Const>(ops::FPTrunc<To>()(value_)));
    }
};

} // namespace

std::unique_ptr<FloatingConstant> ir::createFloatingConstant(std::unique_ptr<Type> type, double value) {
    TypeVisitorImpl visitor(value);
    type->accept(visitor);
    return visitor.takeResult();
}
