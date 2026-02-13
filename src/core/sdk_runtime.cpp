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
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_initialized) return;

	Logger::Instance().Start();

	LOG_INFO("[SDKRuntime] Initializing SDK Runtime...");


	GameBase::initialize();


	LOG_INFO("[SDKRuntime] Initializing scripts...");
	EventBus::instance().dispatch(EventType::Initialize);
	LOG_INFO("[SDKRuntime] Scripts initialized successfully.");

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
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!m_initialized) return;
		
		LOG_INFO("[SDKRuntime] Shutting down SDK Runtime...");
		
		// Disable hooks first
		HookManager::instance().disableHooks();
		
		// Dispatch shutdown event
		EventBus::instance().dispatch(EventType::Shutdown);
		
		m_initialized = false;
	}
	
	// Stop logger after releasing the lock to avoid any potential issues
	Logger::Instance().Stop();
}

