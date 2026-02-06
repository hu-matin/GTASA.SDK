#pragma once
#include "i_service.h"
#include "memory"
#include <vector>
#include <algorithm>
#include "service_registry.h"
#include "hook/hook_manager.h"
#include "hook/hook_registry.h"

namespace GTASA {
	namespace SDK {

		class SDKRuntime {

		public:
			static SDKRuntime& instance();

			void init();
			void shutdown();

			void dispatchUpdate();
			void dispatchRender();

			SDKRuntime(const SDKRuntime&) = delete;
			SDKRuntime& operator=(const SDKRuntime&) = delete;

		private:
			SDKRuntime();
			~SDKRuntime();

		private:	
			bool m_initialized;
		};
	} // namespace SDK
} // namespace GTASA