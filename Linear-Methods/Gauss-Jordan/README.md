Gauss-Jordan Elimination

Gauss-Jordan Elimination is a direct method for solving a system of linear equations.

The augmented matrix is transformed into Reduced Row Echelon Form (RREF). The solution can then be obtained directly without backward substitution.

The program also determines whether the system has a unique solution, infinite solutions, or no solution.

Input

The program takes:

* Number of equations
* Augmented matrix

Example Input:

3
2 1 1 5
4 -6 0 -2
-2 7 2 9

Example Output:

The system has a unique solution.
Solution:
X1 = 1.0000
X2 = 1.0000
X3 = 3.0000
Verification:
Equation 1: 5.0000 = 5.0000 -> Satisfied
Equation 2: -2.0000 = -2.0000 -> Satisfied
Equation 3: 9.0000 = 9.0000 -> Satisfied
