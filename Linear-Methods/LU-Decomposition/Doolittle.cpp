/*
Input:
Enter number of equations: 3
Enter the augmented matrix:
2 1 1 5
4 -6 0 -2
-2 7 2 9
Output:
  The system has a unique solution.

Lower Triangular Matrix (L):
1.0000 0.0000 0.0000
2.0000 1.0000 0.0000
-1.0000 -1.0000 1.0000

Upper Triangular Matrix (U):
2.0000 1.0000 1.0000
0.0000 -8.0000 -2.0000
0.0000 0.0000 1.0000

Solution:
X1 = 1.0000
X2 = 1.0000
X3 = 3.0000

Verification:
Equation 1: 5.0000 = 5.0000 -> Satisfied
Equation 2: -2.0000 = -2.0000 -> Satisfied
Equation 3: 9.0000 = 9.0000 -> Satisfied

Solve another system? (y/n): n
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    char choice = 'y';

    while (choice == 'y' || choice == 'Y')
    {
        int n;
        cout << "Enter number of equations: ";
        cin >> n;

        double A[10][10], L[10][10] = {0}, U[10][10] = {0};
        double B[10], Z[10], X[10];

        // Input augmented matrix
        cout << "Enter the augmented matrix:\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> A[i][j];

            cin >> B[i];
        }

        // Temporary matrix for checking solution type
        double T[10][11];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                T[i][j] = A[i][j];

            T[i][n] = B[i];
        }

        // Gaussian Elimination
        int row = 0;

        for (int j = 0; j < n && row < n; j++)
        {
            int pivot = row;

            for (int i = row + 1; i < n; i++)
            {
                if (fabs(T[i][j]) > fabs(T[pivot][j]))
                    pivot = i;
            }

            if (fabs(T[pivot][j]) < 1e-9)
                continue;

            // Swap rows
            for (int k = 0; k <= n; k++)
            {
                double temp = T[row][k];
                T[row][k] = T[pivot][k];
                T[pivot][k] = temp;
            }

            // Eliminate
            for (int i = row + 1; i < n; i++)
            {
                double factor = T[i][j] / T[row][j];

                for (int k = j; k <= n; k++)
                    T[i][k] -= factor * T[row][k];
            }

            row++;
        }

        // Check no solution
        bool noSolution = false;

        for (int i = 0; i < n; i++)
        {
            bool allZero = true;

            for (int j = 0; j < n; j++)
            {
                if (fabs(T[i][j]) > 1e-9)
                {
                    allZero = false;
                    break;
                }
            }

            if (allZero && fabs(T[i][n]) > 1e-9)
            {
                noSolution = true;
                break;
            }
        }

        // No solution
        if (noSolution)
        {
            cout << "\nThe system has no solution.\n";
        }

        // Infinite solution
        else if (row < n)
        {
            cout << "\nThe system has infinite solutions.\n";
        }

        // Unique solution
        else
        {
            cout << "\nThe system has a unique solution.\n";

            // Doolittle: diagonal of L = 1
            for (int i = 0; i < n; i++)
                L[i][i] = 1;

            // LU Decomposition
            for (int j = 0; j < n; j++)
            {
                // Calculate U
                for (int i = 0; i <= j; i++)
                {
                    double sum = 0;

                    for (int k = 0; k < i; k++)
                        sum += L[i][k] * U[k][j];

                    U[i][j] = A[i][j] - sum;
                }

                // Calculate L
                for (int i = j + 1; i < n; i++)
                {
                    double sum = 0;

                    for (int k = 0; k < j; k++)
                        sum += L[i][k] * U[k][j];

                    L[i][j] =
                        (A[i][j] - sum) / U[j][j];
                }
            }

            // Print L
            cout << "\nLower Triangular Matrix (L):\n";

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    cout << fixed << setprecision(4)
                         << L[i][j] << " ";

                cout << endl;
            }

            // Print U
            cout << "\nUpper Triangular Matrix (U):\n";

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    cout << fixed << setprecision(4)
                         << U[i][j] << " ";

                cout << endl;
            }

            // Forward Substitution: LZ = B
            for (int i = 0; i < n; i++)
            {
                double sum = 0;

                for (int j = 0; j < i; j++)
                    sum += L[i][j] * Z[j];

                Z[i] = B[i] - sum;
            }

            // Backward Substitution: UX = Z
            for (int i = n - 1; i >= 0; i--)
            {
                double sum = 0;

                for (int j = i + 1; j < n; j++)
                    sum += U[i][j] * X[j];

                X[i] = (Z[i] - sum) / U[i][i];
            }

            // Print solution
            cout << "\nSolution:\n";

            for (int i = 0; i < n; i++)
                cout << "X" << i + 1 << " = "
                     << fixed << setprecision(4)
                     << X[i] << endl;

            // Verification
            cout << "\nVerification:\n";

            for (int i = 0; i < n; i++)
            {
                double result = 0;

                for (int j = 0; j < n; j++)
                    result += A[i][j] * X[j];

                cout << "Equation " << i + 1 << ": "
                     << result << " = " << B[i];

                if (fabs(result - B[i]) < 1e-6)
                    cout << " -> Satisfied";
                else
                    cout << " -> Not Satisfied";

                cout << endl;
            }
        }

        cout << "\nSolve another system? (y/n): ";
        cin >> choice;

        cout << endl;
    }

    return 0;
}
