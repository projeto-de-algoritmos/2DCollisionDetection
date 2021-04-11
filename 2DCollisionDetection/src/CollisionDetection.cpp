#include "CollisionDetection.hpp"
#include "RunningManager.hpp"
#include "QuadTree.hpp"

void ColDetect::EfficientCollisionDetection(const std::vector<Ball *> & balls, int32_t table_width, int32_t table_height)
{
    QuadTree tree = QuadTree(1, Rectangle(0, 0, table_width, table_height));

    for(auto ball : balls)
        tree.insert(ball);


    std::vector<Ball*> quadrantBalls;

    for(auto ball : balls){
        quadrantBalls = tree.retrieve(ball);

        for(auto qball : quadrantBalls){
            if(ball == qball)
                continue;
            if(Ball::ballsAreColliding(ball, qball)){
                ball->turnOnBallHighlight();
                qball->turnOnBallHighlight();

                if(RunningManager::PhysicsIsEnabled())
                    Ball::collideBalls(ball, qball);
            }
        }
    }
}

void ColDetect::NaiveCollisionDetection(const std::vector<Ball *> & balls) {
    // Algoritmo ingenuo O(N^2)
    for (int i = 0; i < (int) balls.size(); i++) {
        for (int j = i+1; j < (int) balls.size(); j++) {

            // Sinaliza mais uma query sobre uma bola
            RunningManager::IncrementOperationsPerfomed();
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
