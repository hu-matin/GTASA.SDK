#include "game_loop_hook.h"
#include "core/hook/auto_hook.h"
#include "core/hook/hook_manager.h"
#include "core/sdk_runtime.h"
#include "core/logging/logger.hpp"

using namespace GTASA::SDK;
using namespace Logging;

namespace {

    // --------------------------------------------------
    // GTA function pointer
    // --------------------------------------------------
    using tProcessFrame = int(__cdecl*)(int command, int param);
    tProcessFrame oProcessFrame = nullptr;

    int __cdecl hk_ProcessFrame(int command, int param)
    {
        // command == 0x1a -> Frame processing
        if (command == 0x1a) {
            SDKRuntime::instance().dispatchRender();
        }

        return oProcessFrame(command, param);
    }

    using tScreenLoad = void(__stdcall*)(void*, LPCSTR);
    tScreenLoad oScreenLoad = nullptr;

    void __stdcall hk_ScreenLoad(void* param_1, LPCSTR param_2) {
        return oScreenLoad(param_1, param_2);
    }

} // anonymous namespace

// --------------------------------------------------
// IHook implementation
// --------------------------------------------------
void GameLoopHook::install()
{
    // Offset: 0x619b60 - 0x400000 = 0x219b60
    oProcessFrame = reinterpret_cast<tProcessFrame>(
        GameBase::address(0x00219b60)
        );

    HookManager::instance().addHook(
        reinterpret_cast<void**>(&oProcessFrame),
        reinterpret_cast<void*>(hk_ProcessFrame)
    );

    LOG_INFO("[GameLoopHook] Frame processor hooked!");

	// offset: 0x747660 - 0x400000 = 0x347660
    oScreenLoad = reinterpret_cast<tScreenLoad>(
        GameBase::address(0x00347660)
        );
    //HookManager::instance().addHook(
    //    reinterpret_cast<void**>(&oScreenLoad),
    //    reinterpret_cast<void*>(hk_ScreenLoad)
    //);

    LOG_INFO("");
}

void GameLoopHook::uninstall()
{
    // handled by HookManager
}

// --------------------------------------------------
// Auto register
// --------------------------------------------------
namespace {
    AutoHook<GameLoopHook> _autoGameLoopHook;
}
