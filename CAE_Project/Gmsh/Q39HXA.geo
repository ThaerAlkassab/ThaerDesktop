//+
SetFactory("OpenCASCADE");
Rectangle(1) = {0, 0, 0, 100, 50, 0};
//+
Physical Curve("Left", 5) = {4};
//+
Physical Curve("right", 6) = {2};
//+
Physical Surface("body", 7) = {1};

Mesh 2;