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

        double A[10][10], B[10], X[10];
        double OriginalA[10][10], OriginalB[10];

        cout << "Enter the augmented matrix:\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> A[i][j];
                OriginalA[i][j] = A[i][j];
            }

            cin >> B[i];
            OriginalB[i] = B[i];
        }

        // Gaussian Elimination
        for (int j = 0; j < n - 1; j++)
        {
            int pivot = j;

            for (int i = j + 1; i < n; i++)
            {
                if (fabs(A[i][j]) > fabs(A[pivot][j]))
                    pivot = i;
            }

            if (fabs(A[pivot][j]) < 1e-9)
                continue;

            // Swap rows
            for (int k = 0; k < n; k++)
            {
                double temp = A[j][k];
                A[j][k] = A[pivot][k];
                A[pivot][k] = temp;
            }

            double temp = B[j];
            B[j] = B[pivot];
            B[pivot] = temp;

            // Elimination
            for (int i = j + 1; i < n; i++)
            {
                double factor = A[i][j] / A[j][j];

                for (int k = j; k < n; k++)
                    A[i][k] -= factor * A[j][k];

                B[i] -= factor * B[j];
            }
        }

        // Check solution type
        bool noSolution = false;
        bool infiniteSolution = false;

        for (int i = 0; i < n; i++)
        {
            bool allZero = true;

            for (int j = 0; j < n; j++)
            {
                if (fabs(A[i][j]) > 1e-9)
                {
                    allZero = false;
                    break;
                }
            }

            if (allZero && fabs(B[i]) > 1e-9)
            {
                noSolution = true;
                break;
            }

            if (allZero && fabs(B[i]) < 1e-9)
                infiniteSolution = true;
        }

        // No Solution
        if (noSolution)
        {
            cout << "\nThe system has no solution.\n";
        }

        // Infinite Solution
        else if (infiniteSolution)
        {
            cout << "\nThe system has infinite solutions.\n";
        }

        // Unique Solution
        else
        {
            // Backward Substitution
            for (int i = n - 1; i >= 0; i--)
            {
                double sum = 0;

                for (int j = i + 1; j < n; j++)
                    sum += A[i][j] * X[j];

                X[i] = (B[i] - sum) / A[i][i];
            }

            cout << "\nThe system has a unique solution.\n";

            cout << "\nSolution:\n";

            for (int i = 0; i < n; i++)
            {
                cout << "X" << i + 1 << " = "
                     << fixed << setprecision(4)
                     << X[i] << endl;
            }

            // Verification using original matrix
            cout << "\nVerification:\n";

            for (int i = 0; i < n; i++)
            {
                double result = 0;

                for (int j = 0; j < n; j++)
                    result += OriginalA[i][j] * X[j];

                cout << "Equation " << i + 1 << ": "
                     << fixed << setprecision(4)
                     << result << " = " << OriginalB[i];

                if (fabs(result - OriginalB[i]) < 1e-6)
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
