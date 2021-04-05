#ifndef _COLLSION_DETECTION_HPP_
#define _COLLISION_DETECTION_HPP_

#include "Ball.hpp"

#include <cstdint>
#include <vector>

namespace ColDetect
{
    void EfficientCollisionDetection(std::vector<Ball *> balls, int32_t table_width, int32_t table_height)
    {
        // TODO
        // Detectar colisões entre as bolas presentes no vetor balls usando o algormto quad-tree
        // Se duas bolas estiver se colidindo, ativar o brilho de ambas: ball->turnOnBallHighlight()
    }

    void NaiveCollisionDetection(std::vector<Ball *> balls) {
        // Algoritmo ingenuo O(N^2)
        for (int i = 0; i < (int) balls.size(); i++) {
            for (int j = i+1; j < (int) balls.size(); j++) {

                if (Ball::ballsAreColliding(balls[i], balls[j])) {
                    balls[i]->turnOnBallHighlight();
                    balls[j]->turnOnBallHighlight();
                }
            }
        }
    }
}

#endif