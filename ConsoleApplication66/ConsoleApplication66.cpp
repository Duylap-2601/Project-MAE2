#include <iostream>
#include <vector>

using namespace std;

void getCofactor(vector<vector<double>>& mat, vector<vector<double>>& temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinant(vector<vector<double>>& mat, int n) {
    if (n == 1) return mat[0][0];

    vector<vector<double>> temp(n - 1, vector<double>(n - 1));
    double det = 0;
    int sign = 1;

    for (int f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }

    return det;
}

void adjoint(vector<vector<double>>& mat, vector<vector<double>>& adj, int n) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }

    vector<vector<double>> temp(n - 1, vector<double>(n - 1));
    int sign;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(mat, temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, n - 1));
        }
    }
}

bool inverse(vector<vector<double>>& mat, vector<vector<double>>& inv, int n) {
    double det = determinant(mat, n);
    if (det == 0) {
        cout << "Matrix is singular, cannot find its inverse" << endl;
        return false;
    }

    vector<vector<double>> adj(n, vector<double>(n));
    adjoint(mat, adj, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = adj[i][j] / det;
        }
    }

    return true;
}

int main() {
    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n;

    vector<vector<double>> mat(n, vector<double>(n));
    vector<vector<double>> inv(n, vector<double>(n));

    cout << "Enter the elements of the matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    double det = determinant(mat, n);
    cout << "The determinant of the matrix is: " << det << endl;

    if (inverse(mat, inv, n)) {
        cout << "The inverse of the matrix is:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << inv[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
