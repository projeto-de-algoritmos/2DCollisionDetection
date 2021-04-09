#include "CollisionDetection.hpp"
#include "RunningManager.hpp"

void ColDetect::EfficientCollisionDetection(const std::vector<Ball *> & balls, int32_t table_width, int32_t table_height)
{
    // TODO
    // Detectar colisões entre as bolas presentes no vetor balls usando o algormto quad-tree
    // Se duas bolas estiver se colidindo, ativar o brilho de ambas: ball->turnOnBallHighlight()
    // e se a fisica estiver ativada, aplicar entre as duas bolas
}

void ColDetect::NaiveCollisionDetection(const std::vector<Ball *> & balls) {
    // Algoritmo ingenuo O(N^2)
    for (int i = 0; i < (int) balls.size(); i++) {
        for (int j = i+1; j < (int) balls.size(); j++) {

            if (Ball::ballsAreColliding(balls[i], balls[j])) {
                
                // Ativa o brilho de ambas as bolas
                balls[i]->turnOnBallHighlight();
                balls[j]->turnOnBallHighlight();

                // Se a fisica estiver habilitada, colidir as duas bolas
                if (RunningManager::PhysicsIsEnabled())
                    Ball::collideBalls(balls[i], balls[j]);
            }
        }
    }
}
