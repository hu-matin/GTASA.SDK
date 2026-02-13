#pragma once

#include "ped.h"

namespace GTASA {
    namespace SDK {

        class Player : public Ped {
        public:
            using Ped::Ped;
            static std::unique_ptr<Player> getLocal();
        };

    }
}
