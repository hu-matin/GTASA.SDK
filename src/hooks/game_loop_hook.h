#pragma once

#include "core/hook/i_hook.h"
#include "core/game/game_base.h"

namespace GTASA {
	namespace SDK {

		class GameLoopHook final : public IHook {
		public:
			virtual const char* getName() const override { return "GameLoopHook"; }

			virtual int Priority() const override { return 10; }

			virtual void install() override;

			virtual void uninstall() override;
		};

	}
}