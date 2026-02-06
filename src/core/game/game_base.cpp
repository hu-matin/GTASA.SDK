#include "core/game/game_base.h"
#include <Windows.h>

namespace GTASA {
    namespace SDK {

        uintptr_t GameBase::s_base = 0;
        bool GameBase::s_initialized = false;

        void GameBase::initialize()
        {
            if (s_initialized)
                return;

            // base address of gta_sa.exe
            s_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
            s_initialized = true;
        }

        uintptr_t GameBase::base()
        {
            return s_base;
        }

        uintptr_t GameBase::address(uintptr_t offset)
        {
            return s_base + offset;
        }

    } // namespace SDK
} // namespace GTASA
