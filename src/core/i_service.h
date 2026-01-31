#pragma once

namespace GTASA {
	namespace SDK {
		class IService {
		public:
			
			virtual ~IService() = default;
			
			virtual int Priority() const { return 100; }

			virtual void onInit() {};
			virtual void onShutdown() {};

			virtual void onUpdate() {};
			virtual void onRender() {};
		};
	}
}