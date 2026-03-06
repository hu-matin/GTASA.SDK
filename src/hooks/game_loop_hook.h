#pragma once

#include "core/hook/i_hook.h"
#include "core/game/game_base.h"
#include "core/hook/auto_hook.h"
#include "core/hook/hook_manager.h"
#include "core/sdk_runtime.h"
#include "core/logging/logger.hpp"

namespace GTASA {
	namespace SDK {

		class GameLoopHook final : public IHook {
		public:
			virtual const char* getName() const override { return "GameLoopHook"; }

			virtual int Priority() const override { return 10; }

			virtual void install() override;

			virtual void uninstall() override;
		};

		namespace Events {
			class ProcessFrameEvent : public BaseEvent {
				public:
				int command;
				int param;

				ProcessFrameEvent(int command, int param) 
				: command(command), param(param) {}

				virtual const char* getName() const { return "ProcessFrameEvent"; }
			};
		}
	}
}