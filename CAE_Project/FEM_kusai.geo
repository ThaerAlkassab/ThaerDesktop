// Gmsh project created on Sun May 05 02:09:53 2024
SetFactory("OpenCASCADE");

// Define points
Point(1) = {0, 0, 0, 1.0};
Point(2) = {200, 0, 0, 1.0};
Point(3) = {200, 100, 0, 1.0};
Point(4) = {0, 100, 0, 1.0};
Point(5) = {50, 5, 0, 1.0};
Point(6) = {50, 25, 0, 1.0};
Point(7) = {50, 45, 0, 1.0};
Point(8) = {50, 55, 0, 1.0};
Point(9) = {50, 75, 0, 1.0};
Point(10) = {50, 95, 0, 1.0};
Point(11) = {150, 95, 0, 1.0};
Point(12) = {150, 75, 0, 1.0};
Point(13) = {150, 55, 0, 1.0};
Point(14) = {150, 45, 0, 1.0};
Point(15) = {150, 45, 0, 1.0};
Point(16) = {150, 25, 0, 1.0};
Point(17) = {150, 5, 0, 1.0};

// Define lines
Line(1) = {4, 1};
Line(2) = {1, 2};
Line(3) = {2, 3};
Line(4) = {3, 4};

// Define circles
Circle(5) = {10, 9, 8};
Circle(6) = {8, 9, 10};
Circle(7) = {7, 6, 5};
Circle(8) = {5, 6, 7};
Circle(9) = {11, 12, 13};
Circle(10) = {13, 12, 11};
Circle(11) = {14, 16, 17};
Circle(12) = {17, 16, 14};

// Define curve loops
Curve Loop(1) = {4, 1, 2, 3};
Curve Loop(2) = {5, 6};
Curve Loop(3) = {10, 9};
Curve Loop(4) = {12, 11};
Curve Loop(5) = {7, 8};

// Define plane surface
Plane Surface(1) = {1, 2, 3, 4, 5};

// Define physical entities
Physical Curve("left", 13) = {1};
Physical Curve("right", 14) = {3};
Physical Surface("body", 15) = {1};
Physical Surface("load", 11) = {1};
Physical Point("supp", 1) = {6, 7};
Physical Line("path", 1) = {5, 6};

// Generate mesh
Mesh 2;
