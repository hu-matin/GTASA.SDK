#include "update_service.h"
#include "core/service_auto_register.h"
#include "core/logging/logger.hpp"

using namespace GTASA::SDK;
using namespace Logging;

namespace {
	AutoRegisterService<UpdateService> _autoRegister;
}

void GTASA::SDK::UpdateService::onInit()
{
	LOG_INFO("[UpdateService] Initialized\n");
}

void GTASA::SDK::UpdateService::onUpdate()
{
	// service loop
}

void UpdateService::onShutdown()
{
	OutputDebugStringA("[UpdateService] Shutdown\n");
}

