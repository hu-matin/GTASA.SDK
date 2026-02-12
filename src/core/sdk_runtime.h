#pragma once
#include "memory"
#include <vector>
#include <algorithm>
#include "hook/hook_manager.h"
#include "hook/hook_registry.h"
#include "script/script.h"
#include "events/event_bus.h"


namespace GTASA {
	namespace SDK {

		class SDKRuntime {

		public:
			static SDKRuntime& instance();

			void init();
			void shutdown();

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