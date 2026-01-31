#pragma once

#include "core/i_service.h"
#include "core/service_auto_register.h"
#include "Windows.h"

namespace GTASA {
	namespace SDK {

		class UpdateService : public IService {
		
		public:
			int Priority() const override { return 10; }

			void onInit() override;
			void onShutdown() override;

			void onUpdate() override;
		};
	}
}

