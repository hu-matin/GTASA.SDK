#pragma once
#include "memory"
#include "vector"
#include <algorithm>
#include "i_hook.h"

namespace GTASA {
	namespace SDK {
		class HookRegistry {
		public:
			static HookRegistry& instance();

			void add(IHook* service);

			const std::vector<std::unique_ptr<IHook>>& getAll() const;

			void sort();

		private:
			HookRegistry() = default;

		private:
			std::vector<std::unique_ptr<IHook>> m_hooks;
		};
	}
}

