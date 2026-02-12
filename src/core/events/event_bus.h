#pragma once

#include <unordered_map>
#include <vector>
#include "memory"

#include "event_type.h"
#include "core/script/script.h"

namespace GTASA {
    namespace SDK {

        class EventBus {
        public:
            static EventBus& instance();

            EventBus(const EventBus&) = delete;
            EventBus& operator=(const EventBus&) = delete;

            // add a script
            void add(std::unique_ptr<Script> script);

            // Dispatch an event
            void dispatch(EventType type);

        private:
            EventBus() = default;
            ~EventBus() = default;

        private:
            std::vector<std::unique_ptr<Script>> m_scripts;
        };

    }
}
