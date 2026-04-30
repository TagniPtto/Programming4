#include "ServiceLocator.h"

namespace dae {
    std::unique_ptr<ISoundSystem> ServiceLocator::_ss_instance = nullptr;
}