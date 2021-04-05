#include "Ball.hpp"
#include "Assets.hpp"
#include "SolidImage.hpp"

bool Ball::ballsAreColliding(const Ball * ball1, const Ball * ball2)
{
    double_t x1 = ball1->getXCoordinate();
    double_t y1 = ball1->getYCoordinate();

    double_t x2 = ball2->getXCoordinate();
    double_t y2 = ball2->getYCoordinate();

    int32_t distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

    return distance <= (ball1->getRadius() + ball2->getRadius()) * (ball1->getRadius() + ball2->getRadius());
}

double_t Ball::getXCoordinate() const noexcept
{
    return _x_coordinate;
}

double_t Ball::getYCoordinate() const noexcept
{
    return _y_coordinate;
}

double_t Ball::getRadius() const noexcept
{
    return _ball_radius;
}

void Ball::turnOnBallHighlight()
{
    _ball_highlight->show();
}

void Ball::turnOffBallHighlight()
{
    _ball_highlight->hide();
}

void Ball::updateBallPosition(double_t frame_time)
{
    _x_coordinate += _x_velocity * frame_time;
    _y_coordinate += _y_velocity * frame_time;

    if (_x_coordinate - _ball_radius < 0.0) {
        _x_coordinate = _ball_radius;
        _x_velocity = -_x_velocity;
    }
    else if (_x_coordinate + _ball_radius > double_t(Assets::WINDOW_WIDTH)) {
        _x_coordinate = double_t(Assets::WINDOW_WIDTH) - _ball_radius;
        _x_velocity = -_x_velocity;
    }

    if (_y_coordinate - _ball_radius < 0.0) {
        _y_coordinate = _ball_radius;
        _y_velocity = -_y_velocity;
    }
    else if (_y_coordinate + _ball_radius > double_t(Assets::WINDOW_HEIGHT)) {
        _y_coordinate = double_t(Assets::WINDOW_HEIGHT) - _ball_radius;
        _y_velocity = -_y_velocity;
    }

    _ball_texture->setGlobalX(_x_coordinate - _ball_radius);
    _ball_texture->setGlobalY(_y_coordinate - _ball_radius);
}

Ball * Ball::newBall(double_t x_coordinate,
                     double_t y_coordinate,
                     double_t x_velocity,
                     double_t y_velocity,
                     double_t ball_radius,
                     std::string ball_texture_name,
                     std::string ball_highlight_name)
{
    Ball * ball = new Ball();
    ball->_x_velocity = x_velocity;
    ball->_y_velocity = y_velocity;
    ball->_x_coordinate = x_coordinate;
    ball->_y_coordinate = y_coordinate;
    ball->_ball_radius = ball_radius;

    ball->_ball_texture = SolidImage::newSolidImage(ball_texture_name, 2*ball_radius, 2*ball_radius);
    ball->_ball_texture->setRelativeX(0);
    ball->_ball_texture->setRelativeY(0);

    ball->_ball_highlight = SolidImage::newSolidImage(ball_highlight_name, 2*ball_radius, 2*ball_radius);
    ball->_ball_highlight->setParent(ball->_ball_texture);
    ball->_ball_highlight->hide();
    ball->_ball_highlight->setRelativeX(0);
    ball->_ball_highlight->setRelativeY(0);

    return ball;
}

Ball::Ball()
{

}

Ball::~Ball()
{

}