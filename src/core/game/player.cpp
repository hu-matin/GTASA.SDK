#include "player.h"

using namespace GTASA::SDK;

std::unique_ptr<Player> Player::getLocal() {
    uintptr_t pedAddress = 
        *reinterpret_cast<uintptr_t*>(
            GameBase::address(Offsets::Globals::LocalPlayer)
        );
        
    if (!pedAddress)
    return nullptr;

    return std::make_unique<Player>(pedAddress);
}