#pragma once

#include "core/script/script.h"
#include "core/events/event_bus.h"
#include "core/logging/logger.hpp"
#include "core/script/auto_register_script.h"

using namespace Logging;

namespace GTASA {
    namespace SDK {

        class SampleScript : public Script {
        public:
            SampleScript() {}

            virtual void onEvent(EventType type) override {
                switch (type)
                {   
                case GTASA::SDK::EventType::GameProcess:
                    break;
                case GTASA::SDK::EventType::Initialize:
                    LOG_INFO("Sample Script initialized.");
                    break;
                case GTASA::SDK::EventType::Shutdown:
                    break;
                default:
                    break;
                }
            }
        };

    }
}


namespace {
    GTASA::SDK::AutoRegisterScript<GTASA::SDK::SampleScript> _autoReg;
}

