#pragma once

#include "core/i_service.h"
#include "core/service_auto_register.h"
#include "Windows.h"
#include "core/logging/logger.hpp"

namespace GTASA {
	namespace SDK {

		class AffinityService : public IService {

		public:
			int Priority() const override { return 0; }

			void onInit() override;
		};
	}
}

