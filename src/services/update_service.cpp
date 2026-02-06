#include "update_service.h"
#include "core/service_auto_register.h"
#include "core/logging/logger.hpp"

using namespace GTASA::SDK;
using namespace Logging;

namespace {
	AutoRegisterService<UpdateService> _autoRegister;
}

void UpdateService::onInit()
{
	LOG_INFO("[UpdateService] Initialized");
}

void UpdateService::onUpdate()
{
	LOG_INFO("[UpdateService] tick()");
}

void UpdateService::onShutdown()
{
	LOG_INFO("[UpdateService] Shutdown");
}

