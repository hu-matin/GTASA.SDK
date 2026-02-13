#pragma once

#include "entity.h"
#include "matrix.h"

namespace GTASA {
    namespace SDK {
            class Ped : public Entity {
            public:
                using Entity::Entity;
                // 117027A8 - 0x540 = 11702268
                /*
                    1186B038
                    1170227C - 11702268 = 0x14
                */
                std::unique_ptr<Matrix> getMatrix() const;

                
                float getHealth() const;
                void setHealth(float amount);
                
                float getArmor() const;
                void setArmor(float amount);

            };

    }
}