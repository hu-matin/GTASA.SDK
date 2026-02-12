#include "script_manager.h"

using namespace GTASA::SDK;

ScriptManager& ScriptManager::instance() {
    static ScriptManager instance;
    return instance;
}

void ScriptManager::add(std::unique_ptr<Script> script) {
    if (script) {
        m_scripts.push_back(std::move(script));
    }
}