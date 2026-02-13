#include "ped.h"

using namespace GTASA::SDK;

float Ped::getHealth() const {
    if (!isValid()) return 0.0f;

    return *reinterpret_cast<float*>(
        (m_ptr) + Offsets::CPed::Health
    );
}

void GTASA::SDK::Ped::setHealth(float amount) {
    if (!isValid()) return;

    *reinterpret_cast<float*>(
        (m_ptr) + Offsets::CPed::Health
    ) = amount;
}

float GTASA::SDK::Ped::getArmor() const
{
        if (!isValid()) return 0.0f;

    return *reinterpret_cast<float*>(
        (m_ptr) + Offsets::CPed::Armor
    );
}

void GTASA::SDK::Ped::setArmor(float amount) {
    if (!isValid()) return;

    *reinterpret_cast<float*>(
        (m_ptr) + Offsets::CPed::Armor
    ) = amount;
}

float GTASA::SDK::Ped::getPosition()
{
            if (!isValid()) return 0.0f;

    return *reinterpret_cast<float*>(
        (m_ptr) + Offsets::CPed::pos_x
    );
}
