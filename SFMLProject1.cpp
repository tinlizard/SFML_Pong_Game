#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <random>

//class for ball... could've been a struct instead but whatever it is what it is
class ballForPong {
    public:
        float x,y,width,height,radius;
        
        //constructor for ball
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
    //print statement for debugging purposes
    std::cout << "The number generated randomly is " << number1 << "\n";
    return input; 
}

//function for reversing both the x and y offset of the ball 
void reverseDirection(float& offset) {
    offset = -offset;
}

//main function
int main() {
    //randomize values using srand and time, also define window height and width
    srand(time(0));
    int windowWidth = 800;
    int windowHeight = 600; 
    //setup window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
    // define paddles
    sf::RectangleShape rectangle(sf::Vector2f(30.f, 180.f));
    sf::RectangleShape rectangle2(sf::Vector2f(30.f, 180.f));
    //make ball object
    ballForPong ball1 = ballForPong(400.f, 100.f, 15.f, 15.f, 20.f);
    sf::CircleShape ball(ball1.radius);
    //set position, initial offset of the ball to be random when the ball is first spawned
    ball.setPosition(ball1.x,ball1.y);
    float ballOffsetX = randomMultiplication(0.05f); 
    float ballOffsetY = 0.05f; 
    float ballRadius = ball.getRadius();

    //intialize scores
    int leftPaddleScore = 0; 
    int rightPaddleScore = 0; 

    //set color and positions of paddles
    rectangle.setFillColor(sf::Color(255, 255, 255));
    rectangle.setPosition(10.f, 50.f);
    rectangle2.setPosition(750.f, 50.f);
    rectangle2.setFillColor(sf::Color(255, 255, 255));

    //main window loop
    while (window.isOpen()) {
        sf::Vector2f ballPosition = ball.getPosition();
        sf::Event event;
        ball.move(ballOffsetX,ballOffsetY);
        
        //main event loop
        while (window.pollEvent(event)) {
            //exit on close
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //check for key presses to move paddles
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
        if (ball.getGlobalBounds().intersects(rectangle.getGlobalBounds())) {
            //multiply previous Y offset for the ball by 1 or -1, then set ball offset Y to the new value of ball offset Y
            float newBallOffsetY = randomMultiplication(ballOffsetY);
            ballOffsetY = newBallOffsetY; 
            //reverse ball direction and set ball position to be 0.01 units from the paddle to prevent constant collision with paddle
            reverseDirection(ballOffsetX);
            ball.setPosition(ballPosition.x + 0.01, ballPosition.y); 

        }
        if (ball.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) {
            //same code as for the left paddle but for the right paddle instead
            float newBallOffsetY = randomMultiplication(ballOffsetY);
            ballOffsetY = newBallOffsetY;
            reverseDirection(ballOffsetX);
            ball.setPosition(ballPosition.x - 0.01, ballPosition.y);
        }
        
        //if the ball's y position is at the top of the screen, reverse the ball y direction 
        if (ballPosition.y < 0.f) {
            reverseDirection(ballOffsetY);
            ball.setPosition(ballPosition.x, (ballPosition.y) + 20);
        }
        //if the ball's y position is greater than 600, knock the ball back upwards
        if (ballPosition.y > 600) {
            reverseDirection(ballOffsetY); 
            ball.setPosition(ballPosition.x, (ballPosition.y) - 20);
        }
        /*
        check if the ball's x position is less than the left paddle or greater than the right rectangle and if the ball y positon is less than the top or bottom of the screen.
        if it is, reset the ball position to the original position
        */
        if ((ballPosition.x < rectangle.getPosition().x) && (ballPosition.y > 0.f || ballPosition.y <600.f)) {
            ball.setPosition(ball1.x, ball1.y);
            //increment right paddle score if the ball goes off the left side of the screen
            rightPaddleScore++; 
            std::cout << "The right paddle score is " << rightPaddleScore << "\n"; 

        }
        //same code but for right paddle
        if ((ballPosition.x > rectangle2.getPosition().x) && (ballPosition.y > 0.f || ballPosition.y < 600.f)) {
            ball.setPosition(ball1.x, ball1.y);
            //increment left paddle score if the ball goes off the right side of the screen
            leftPaddleScore++; 
            std::cout << "The left paddle score is " << leftPaddleScore << "\n"; 
        }
        
        //draw objects to screen
        window.clear(sf::Color::Black);
        window.draw(rectangle);
        window.draw(rectangle2); 
        window.draw(ball); 
        window.display();
    }

    return 0;
}
