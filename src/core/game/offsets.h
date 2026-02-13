#pragma once 
#include <cstdint>

namespace GTASA {
    namespace SDK {

        namespace Offsets
        {
            namespace Globals {
                constexpr uintptr_t LocalPlayer = 0x0076F3B8;
            }
            
            namespace CPed {
                constexpr uintptr_t Health = 0x540;
                constexpr uintptr_t Armor = 0x548;
                constexpr uintptr_t Matrix = 0x14;
            }

            namespace Matrix {
                constexpr uintptr_t pos_x = 0x30;
                constexpr uintptr_t pos_y = 0x34;
                constexpr uintptr_t pos_z = 0x38;
            }
        } // namespace Offsets
        
    }
}