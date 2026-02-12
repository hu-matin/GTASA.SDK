#pragma once

#include "core/script/script.h"
#include "core/events/event_bus.h"
#include "core/logging/logger.hpp"
#include "core/script/auto_register_script.h"

using namespace Logging;

namespace GTASA {
    namespace SDK {

        class AffinityScript : public Script {
        public:
            AffinityScript() {}

            virtual void onEvent(EventType type) override {
                if (type == EventType::Initialize) {
                    LOG_INFO("[AffinityService] initialized.");

                    HANDLE hProcess = GetCurrentProcess();
                    DWORD_PTR processAffinityMask = 1; // First CPU core
                    if (SetProcessAffinityMask(hProcess, processAffinityMask)) {
                        LOG_INFO("[AffinityService] Process affinity set to first CPU core.\n");
                    }
                    else {
                        LOG_ERROR("[AffinityService] Failed to set process affinity.\n");
                    }
                }
            }
        };

    }
}


namespace {
    GTASA::SDK::AutoRegisterScript<GTASA::SDK::AffinityScript> _autoReg;
}

