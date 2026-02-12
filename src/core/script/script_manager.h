#pragma once

#include <vector>
#include <memory>

#include "script.h"
#include "vector"
#include "memory"

namespace GTASA {
    namespace SDK {

        class ScriptManager {
        public:
            static ScriptManager& instance();

            ScriptManager(const ScriptManager&) = delete;
            ScriptManager& operator=(const ScriptManager&) = delete;

            // ----------------------------
            // adding scripts
            // ----------------------------
            void add(std::unique_ptr<Script> script);

            // ----------------------------
            // Dispatch Events
            // ----------------------------
            void dispatchInitialize();
            void dispatchGameTick();
            void dispatchShutdown();

        private:
            ScriptManager() = default;
            ~ScriptManager() = default;

        private:
            std::vector<std::unique_ptr<Script>> m_scripts;
        };

    } // namespace SDK
}
