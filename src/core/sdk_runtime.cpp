#include "sdk_runtime.h"
#include "logging/logger.hpp"
#include "core/game/game_base.h"

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


	GameBase::initialize();


	LOG_INFO("[SDKRuntime] Initializing services...");
	ServiceRegistry::instance().sort();

	for (auto& service : ServiceRegistry::instance().getAll())
		service->onInit();
	LOG_INFO("[SDKRuntime] Services initialized successfully.");


	LOG_INFO("[SDKRuntime] Installing hooks...");
	HookRegistry::instance().sort();

	for (auto& hook : HookRegistry::instance().getAll())
		if (hook->isEnabled())
			hook->install();	

	LOG_INFO("[SDKRuntime] Hooks installed successfully.");

	HookManager::instance().enableHooks();

	m_initialized = true;
	LOG_INFO("[SDKRuntime] SDK Runtime initialized successfully.");
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

void SDKRuntime::dispatchUpdate() {
	for (auto& service : ServiceRegistry::instance().getAll())
		service->onUpdate();
}

void SDKRuntime::dispatchRender() {
	for (auto& service : ServiceRegistry::instance().getAll())
		service->onRender();
}
