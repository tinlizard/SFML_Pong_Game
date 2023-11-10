#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <random>

class ballForPong {
    public:
        float x,y,width,height,radius;
   
        ballForPong(float x,float y,float width,float height,float radius) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->radius = radius;
        }
};

//function for generating either a negative or positive float value
float randomMultiplication(float input) {
    //generate a random number between 0 and 1. 
    int number1 = rand() % 2; 

    //if the number generated is 0, multiply the float input by -1. 
    if (number1 == 0) {
        input = input * -1.f; 
    }
    //else keep the float input the same
    else {
        input = input * 1.f; 
    }
    return input; 
}

//function for reversing both the x and y offset of the ball 
void reverseDirection(float& offsetX, float& offsetY) {
    offsetX = -offsetX;
    offsetY = -offsetY;
}

int main() {
    srand(time(0));
    int windowWidth = 800;
    int windowHeight = 600; 
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
    // define paddles
    sf::RectangleShape rectangle(sf::Vector2f(30.f, 180.f));
    sf::RectangleShape rectangle2(sf::Vector2f(30.f, 180.f));
    ballForPong ball1 = ballForPong(400.f, 100.f, 15.f, 15.f, 20.f);
    sf::CircleShape ball(ball1.radius);
    ball.setPosition(ball1.x,ball1.y);
    float ballOffsetX = randomMultiplication(0.05f); 
    float ballOffsetY = 0.05f; 
    float ballRadius = ball.getRadius();
    
    

    rectangle.setFillColor(sf::Color(255, 255, 255));
    rectangle.setPosition(10.f, 50.f);
    rectangle2.setPosition(750.f, 50.f);
    rectangle2.setFillColor(sf::Color(255, 255, 255));

    while (window.isOpen()) {
        sf::Vector2f ballPosition = ball.getPosition();
        sf::Event event;
        ball.move(ballOffsetX,ballOffsetY);
        std::cout << ballPosition.y << "\n";
        std::cout << "ball offset Y is " << ballOffsetY << "\n"; 
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    rectangle.move(0.f, 10.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    rectangle.move(0.f,-10.f); 
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    rectangle2.move(0.f, 10.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    rectangle2.move(0.f, -10.f); 
                } 
            }
        }
        if (ball.getGlobalBounds().intersects(rectangle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) {
            reverseDirection(ballOffsetX, ballOffsetY); 
        }
        
        /*
        * if the ball's y position is at the top of the screen, reverse the ball y direction and
        * make sure that the ball's position is reset to the original ball spawn point
        */
        
        if (ballPosition.y < 0.f) {
            ballOffsetY = -ballOffsetY;
            ball.setPosition(ballPosition.x, (ballPosition.y) + 20);
        }
        //if the ball's y position is greater than 600, set the ball back to its original spawn position
        if (ballPosition.y > 600) {
            ball.setPosition(ball1.x, ball1.y); 
        }
        
        
        window.clear(sf::Color::Black);
        window.draw(rectangle);
        window.draw(rectangle2); 
        window.draw(ball); 
        window.display();
    }

    return 0;
}
