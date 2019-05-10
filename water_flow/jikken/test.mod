var x1 >= 0.0;
var x2 >= 0.0;

minimize Objective: - x1 - x2;

subject to C1:
	3 * x1 + 2 * x2 <= 12;

subject to C2:
	x1 + 2 * x2 <= 8;
