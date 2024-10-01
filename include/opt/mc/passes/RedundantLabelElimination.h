#pragma once

#include "mc/Fragment.h"
#include "opt/mc/FragmentTransform.h"

namespace mc {

class RedundantLabelElimination final : public FragmentTransform {
public:
    bool runOnFragment(Fragment &fragment) override;
};

} // namespace mc
