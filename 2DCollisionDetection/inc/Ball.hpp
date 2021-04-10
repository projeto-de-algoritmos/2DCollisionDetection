#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "VisualComponent.hpp"
#include "SolidImage.hpp"
#include "Assets.hpp"
#include "Helpers.hpp"
#include "Vector2D.hpp"

#include <string>

class Ball
{
private:
    static void makePerfectContactBetweenBalls(Ball * ball1, Ball * ball2);

public:
    // It checks if two balls are colliding
    static bool ballsAreColliding(const Ball * ball1, const Ball * ball2);
    
    // Does some collision physics 8)
    static void collideBalls(Ball * ball1, Ball * ball2);

    
    // Ball x center coordinate
    double_t getXCoordinate() const noexcept;
    // Ball y center coordinate
    double_t getYCoordinate() const noexcept;
    // Ball velocity x
    double_t getXVelocity() const noexcept;
    // Ball velocity y
    double_t getYVelocity() const noexcept;
    // Ball Radius
    double_t getRadius() const noexcept;

    Vector2D getCenter() const noexcept;
    void setCenter(const Vector2D & center) noexcept;

    Vector2D getVelocity() const noexcept;
    void setVelocity(const Vector2D & velocity) noexcept;

    void hide();

    void show();

    // It makes ball shine
    void turnOnBallHighlight();
    // It makes ball normal
    void turnOffBallHighlight();
    
    void updateBallPosition(double_t frame_time);
    
    static Ball * newBall(double_t x_coordinate,
                          double_t y_coordinate,
                          double_t x_velocity,
                          double_t y_velocity,
                          double_t ball_radius = Assets::BALL_RADIUS,
                          std::string ball_texture_name = Assets::BALL_TEXTURE_NAME,
                          std::string ball_highlight_name = Assets::BALL_HIGHLIGHT_NAME);

private:
    Ball();
    ~Ball();

    double_t _ball_radius;
    Vector2D _center;
    Vector2D _velocity;

    SolidImage * _ball_texture;
    SolidImage * _ball_highlight;

protected:

};

#endif
