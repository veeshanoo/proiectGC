#include <iostream>

#include <math.h>

 

void main()

{

    float slope, intercept;

    float x1, y1, x2, y2;

    float px, py;

    float left, top, right, bottom; // Bounding Box For Line Segment

    float dx, dy;

 

    std::cout << "Program to find whether the given point lies with in line segment:\n";

 

    std::cout << "Enter X1: ";

    std::cin >> x1;

 

    std::cout << "Enter Y1: ";

    std::cin >> y1;

 

    std::cout << "Enter X2: ";

    std::cin >> x2;

 

    std::cout << "Enter Y2: ";

    std::cin >> y2;

 

    std::cout << "Enter Point X: ";

    std::cin >> px;

 

    std::cout << "Enter Point Y: ";

    std::cin >> py;

 

    dx = x2 - x1;

    dy = y2 - y1;

 

    slope = dy / dx;

    // y = mx + c

    // intercept c = y - mx

    intercept = y1 - slope * x1; // which is same as y2 - slope * x2

 

    // For Bounding Box

    if(x1 < x2)

    {

        left = x1;

        right = x2;

    }

    else

    {

        left = x2;

        right = x1;

    }

    if(y1 < y2)

    {

        top = y1;

        bottom = y2;

    }

    else

    {

        top = y1;

        bottom = y2;

    }

 

 

    std::cout << "Equation of the line: ";

    std::cout << slope << "X " << ((intercept < 0) ? ' ' : '+') << intercept << "\n";

   

    if( slope * px + intercept > (py - 0.01) &&

        slope * px + intercept < (py + 0.01))

    {

        if( px >= left && px <= right && 

            py >= top && py <= bottom )

        {

            std::cout << "Given point lies in the line segment\n";

        }

        else

            std::cout << "Given point is outside the line segment\n";

 

    }

    else

        std::cout << "The point is outside the line segment\n";

   

}