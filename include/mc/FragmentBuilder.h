#pragma once

#include <memory>
#include <utility>

#include "mc/Fragment.h"
#include "mc/Line.h"

namespace mc {

class FragmentBuilder {
public:
    FragmentBuilder() = default;

    FragmentBuilder(Fragment *function, Fragment::const_iterator pos)
        : function_(function), pos_(pos) {}

    void setPos(Fragment *function, Fragment::const_iterator pos) {
        function_ = function;
        pos_ = pos;
    }

    void setPos(Fragment *function) {
        setPos(function, function->end());
    }

    Line &add(std::unique_ptr<Line> line) {
        return function_->add(pos_, std::move(line));
    }

private:
    Fragment *function_{};
    Fragment::const_iterator pos_{};
};

} // namespace mc
