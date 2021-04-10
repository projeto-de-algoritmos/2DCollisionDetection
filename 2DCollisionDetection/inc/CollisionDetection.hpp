#ifndef _COLLISION_DETECTION_HPP_
#define _COLLISION_DETECTION_HPP_

#include "Ball.hpp"

#include <cstdint>
#include <vector>

namespace ColDetect
{
        void EfficientCollisionDetection(const std::vector<Ball *> & balls, int32_t table_width, int32_t table_height);
            void NaiveCollisionDetection(const std::vector<Ball *> & balls);
}

#endif
