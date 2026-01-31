#pragma once
#include "memory"
#include "vector"
#include <algorithm>
#include "i_service.h"


namespace GTASA {
	namespace SDK {
		class ServiceRegistry {
		public:
			static ServiceRegistry& instance();

			void add(IService* service);

			const std::vector<std::unique_ptr<IService>>& getAll() const;

			void sort();

		private:
			ServiceRegistry() = default;

		private:
			std::vector<std::unique_ptr<IService>> m_services;
		};
	}
}

