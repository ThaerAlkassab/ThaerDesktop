// Gmsh project created on Sun May 05 01:40:36 2024
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {200, 100, 0, 1.0};
//+
Point(3) = {0, 100, 0, 1.0};
//+
Point(4) = {200, 0, 0, 1.0};
//+
Point(5) = {50, 75, 0, 1.0};
//+
Point(6) = {50, 25, 0, 1.0};
//+
Point(7) = {150, 25, 0, 1.0};
//+
Point(8) = {150, 75, 0, 1.0};
//+
Point(9) = {150, 95, 0, 1.0};
//+
Point(10) = {150, 55, 0, 1.0};
//+
Point(11) = {150, 45, 0, 1.0};
//+
Point(12) = {150, 5, 0, 1.0};
//+
Point(13) = {50, 5, 0, 1.0};
//+
Point(14) = {50, 55, 0, 1.0};
//+
Point(15) = {50, 95, 0, 1.0};
//+
Circle(1) = {15, 5, 14};
//+
Circle(2) = {14, 5, 15};
//+
Point(16) = {50, 45, 0, 1.0};
//+
Circle(3) = {16, 6, 13};
//+
Circle(4) = {13, 6, 16};
//+
Circle(5) = {11, 7, 12};
//+
Circle(6) = {12, 7, 11};
//+
Circle(7) = {10, 8, 9};
//+
Circle(8) = {9, 8, 10};
//+
Curve Loop(1) = {2, 1};
//+
Line(9) = {1, 3};
//+
Line(10) = {3, 2};
//+
Line(11) = {2, 4};
//+
Line(12) = {4, 1};
//+
Curve Loop(2) = {10, 11, 12, 9};
//+
Curve Loop(3) = {1, 2};
//+
Curve Loop(4) = {7, 8};
//+
Curve Loop(5) = {6, 5};
//+
Curve Loop(6) = {3, 4};
//+
Plane Surface(1) = {2, 3, 4, 5, 6};
//+
Curve Loop(7) = {9, 10, 11, 12};
//+
Curve Loop(8) = {2, 1};
//+
Curve Loop(9) = {4, 3};
//+
Curve Loop(10) = {6, 5};
//+
Curve Loop(11) = {7, 8};
//+
Surface(2) = {7, 8, 9, 10, 11};
//+
Physical Curve("left", 13) = {9};
//+
Physical Curve("right", 14) = {11};
//+
Physical Surface("space", 15) = {1};

Mesh 2;