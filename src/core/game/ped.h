#pragma once

#include "entity.h"
#include "core/math/vector3.h"

namespace GTASA {
    namespace SDK {
            class Ped : public Entity {
            public:
                using Entity::Entity;

                // Vector3 getPosition() const;
                void setPosition(const Vector3&);
                float getHealth() const;
                void setHealth(float amount);
                
                float getArmor() const;
                void setArmor(float amount);

                float getPosition();
            };

    }
}