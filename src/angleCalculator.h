#pragma once

#include <iostream>

#include <cmath>


double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

double angleBetweenPoints(int x1, int y1, int x2, int y2) {
    // differences
    int dx = x2 - x1;
    int dy = y2 - y1;
    // chat gpt ahh stuff
    double angleInRadians = std::atan2(dy, dx);
    double angleInDegrees = angleInRadians * (180.0 / M_PI);
    return angleInDegrees;
}

void angleToVelocity(double inputAngle, float *outputVelX, float *outputVelY) {
    *outputVelX = cos(degreesToRadians(inputAngle));
    *outputVelY = sin(degreesToRadians(inputAngle));
}
