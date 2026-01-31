#include "sdk_runtime.h"
#include "logging/logger.hpp"

using namespace GTASA::SDK;
using namespace Logging;

SDKRuntime& SDKRuntime::instance()
{
	static SDKRuntime instance;
	return instance;
}

SDKRuntime::SDKRuntime()
	: m_initialized(false)
{
	return;
}

SDKRuntime::~SDKRuntime()
{
	if (m_initialized)
	{
		shutdown();
	}
}

void SDKRuntime::init()
{
	if (m_initialized) return;

	Logger::Instance().Start();

	LOG_INFO("[SDKRuntime] Initializing SDK Runtime...");

	ServiceRegistry::instance().sort();

	for (auto& service : ServiceRegistry::instance().getAll())
		service->onInit();

	m_initialized = true;
}

void SDKRuntime::shutdown()
{
	if (m_initialized)
	{
		for (auto& service : ServiceRegistry::instance().getAll())
			service->onShutdown();

		m_initialized = false;
	}
}

void SDKRuntime::DispatchUpdate() {
	for (auto& service : ServiceRegistry::instance().getAll())
		service->onUpdate();
}

void SDKRuntime::DispatchRender() {
	for (auto& service : ServiceRegistry::instance().getAll())
		service->onRender();
}
