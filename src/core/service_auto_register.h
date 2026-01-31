#pragma once
#include "service_registry.h"

namespace GTASA {
    namespace SDK {

        template<typename T>
        class AutoRegisterService {
        public:
            AutoRegisterService() {
                ServiceRegistry::instance().add(new T());
            }
        };
    } // namespace SDK
} // namespace GTAS