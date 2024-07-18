#include <iostream>
#include <vector>

using namespace std;

// Hàm lấy ma trận con của phần tử mat[p][q] trong temp[][]
void getCofactor(vector<vector<double>>& matrix, vector<vector<double>>& cofactorArray, int p, int q, int n) {
    int i = 0, j = 0; // Khởi tạo chỉ số cho ma trận temp

    // Lặp qua từng phần tử của ma trận
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Chỉ sao chép các phần tử không nằm trong hàng và cột cho trước
            if (row != p && col != q) {
                cofactorArray[i][j++] = mat[row][col]; // Sao chép phần tử vào temp

                // Đã điền hết hàng, chuyển sang hàng tiếp theo trong temp
                if (j == n - 1) {
                    j = 0; // Đặt lại chỉ số cột
                    i++;   // Chuyển sang hàng tiếp theo
                }
            }
        }
    }
}

// Hàm đệ quy để tìm định thức của một ma trận
double determinant(vector<vector<double>>& matrix, int n) {
    if (n == 1) return matrix[0][0]; // Trường hợp cơ bản cho ma trận 1x1

    vector<vector<double>> cofactorArray(n - 1, vector<double>(n - 1)); // Ma trận tạm thời để lưu các ma trận con
    double det = 0; // Khởi tạo định thức
    int sign = 1;   // Khởi tạo dấu cho khai triển phần tử con

    // Vòng lặp để tìm định thức sử dụng các phần tử con
    for (int f = 0; f < n; f++) {
        getCofactor(mat, cofactorArray, 0, f, n); // Lấy phần tử con của mat[0][f]
        det += sign * matrix[0][f] * determinant(cofactorArray, n - 1); // Thêm phần tử con vào định thức
        sign = -sign; // Đổi dấu
    }

    return det; // Trả về giá trị định thức
}

// Hàm để tìm ma trận phụ hợp của mat và lưu vào adj
void adjoint(vector<vector<double>>& matrix, vector<vector<double>>& adj, int n) {
    if (n == 1) { // Trường hợp cơ bản cho ma trận 1x1
        adj[0][0] = 1;
        return;
    }

    vector<vector<double>> cofactorArray(n - 1, vector<double>(n - 1)); // Ma trận tạm thời để lưu các phần tử con
    int sign;

    // Vòng lặp để tìm ma trận phụ hợp bằng cách tính các phần tử con và dấu của chúng
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(mat, cofactorArray, i, j, n); // Lấy phần tử con của mat[i][j]
            sign = ((i + j) % 2 == 0) ? 1 : -1; // Dấu cho phần tử con
            adj[j][i] = (sign) * (determinant(cofactorArray, n - 1)); // Lưu ma trận phụ hợp
        }
    }
}

// Hàm để tìm ma trận nghịch đảo của mat và lưu vào inv
bool inverse(vector<vector<double>>& matrix, vector<vector<double>>& inv, int n) {
    double det = determinant(matrix, n); // Tính định thức của ma trận
    if (det == 0) { // Nếu định thức bằng 0, ma trận suy biến và không có ma trận nghịch đảo
        cout << "Matrix is singular, cannot find its inverse" << endl;
        return false;
    }

    vector<vector<double>> adj(n, vector<double>(n)); // Để lưu ma trận phụ hợp
    adjoint(matrix, adj, n); // Tìm ma trận phụ hợp

    // Tính ma trận nghịch đảo theo công thức: inv = adj / det
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = adj[i][j] / det; // Lưu từng phần tử của ma trận nghịch đảo
        }
    }

    return true; // Trả về true chỉ ra rằng đã tìm được ma trận nghịch đảo
}

int main() {
    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n; // Nhập kích thước của ma trận

    vector<vector<double>> matrix(n, vector<double>(n)); // Ma trận để lưu dữ liệu nhập vào
    vector<vector<double>> inv(n, vector<double>(n)); // Ma trận để lưu ma trận nghịch đảo

    cout << "Enter the elements of the matrix:\n";
    for (int i = 0; i < n; i++) { // Nhập các phần tử của ma trận
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    double det = determinant(matrix, n); // Tính định thức của ma trận
    cout << "The determinant of the matrix is: " << det << endl;

    if (inverse(matrix, inv, n)) { // Nếu tồn tại ma trận nghịch đảo, in ra nó
        cout << "The inverse of the matrix is:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << inv[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0; // Kết thúc chương trình
}
