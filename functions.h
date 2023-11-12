#pragma once

//pong ball class
class ballForPong {
public:
    float x, y, width, height, radius;

    //constructor for ball
    ballForPong(float x, float y, float width, float height, float radius) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->radius = radius;
    }
};

float randomMultiplication(float input);
void reverseDirection(float& offset);
