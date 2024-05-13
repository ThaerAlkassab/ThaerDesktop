//+
SetFactory("OpenCASCADE");

// Define the points
Point(1) = {0, 0, 0, 1.0};
Point(2) = {200, 0, 0, 1.0};
Point(3) = {200, 100, 0, 1.0};
Point(4) = {0, 100, 0, 1.0};
Point(5) = {100, 50, 0, 1.0};
Point(6) = {100, 25, 0, 1.0};
Point(7) = {100, 75, 0, 1.0};

// Define the lines
Line(1) = {4, 1};
Line(2) = {3, 2};
Line(3) = {4, 3};
Line(4) = {1, 2};

// Define the circles
Circle(5) = {6, 5, 7};
Circle(6) = {7, 5, 6};

// Define the curve loops
Curve Loop(1) = {3, 2, -4, -1}; // Rectangle curve loop
Curve Loop(2) = {5, 6}; // Circle curve loop

// Define the surfaces
Plane Surface(1) = {1, 2}; // Surface between rectangle and circle

// Define physical groups
Physical Surface("body", 7) = {1}; // Combined surface is the "body"
Physical Curve("Left", 8) = {1}; // Left side of the rectangle
Physical Curve("Right", 9) = {2}; // Right side of the rectangle
Physical Curve("Circle", 10) = {5, 6}; // Circle curves

Physical Surface("load", 11) = {1};

Physical Point("supp", 1) = {6, 7};

Physical Line("path", 1) = {5, 6};


Mesh 2;
