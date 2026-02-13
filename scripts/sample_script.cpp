#pragma once

#include "core/script/script.h"
#include "core/events/event_bus.h"
#include "core/logging/logger.hpp"
#include "core/script/auto_register_script.h"
#include "core/game/player.h"
#include <string>

using namespace Logging;

namespace GTASA {
    namespace SDK {

        class SampleScript : public Script {
        public:
            SampleScript() {}

            virtual void onEvent(EventType type) override {
                switch (type)
                {   
                case GTASA::SDK::EventType::GameProcess:
                {
                    if (GetAsyncKeyState(VK_F5) & 1)
                    {
                        std::unique_ptr<Player> player = Player::getLocal();
                        if(!player || !player->isValid())
                            break;
                        player->setHealth(50.0f);
                        player->setArmor(50.0f);
                        float hp = player->getHealth();
                        float arm = player->getArmor();
                        LOG_INFO("Player Health: %.2f", hp);
                        LOG_INFO("Player Armor: %.2f", arm);

                        float pos = player->getPosition();
                        LOG_INFO("Player pos_x: %.2f", pos);
                    }

                    break;
                }

                case GTASA::SDK::EventType::Initialize:
                    LOG_INFO("Sample Script initialized.");
                    break;
                case GTASA::SDK::EventType::Shutdown:
                    break;
                default:
                    break;
                }
            }
        };

    }
}


namespace {
    GTASA::SDK::AutoRegisterScript<GTASA::SDK::SampleScript> _autoReg;
}

