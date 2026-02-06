#pragma once

#include "i_hook.h"
#include "hook_registry.h"

namespace GTASA {
    namespace SDK {

        template<typename T>
        class AutoHook {
        public:
            AutoHook() {
                HookRegistry::instance().add(new T());
            }
        };
    } // namespace SDK
} // namespace GTAS