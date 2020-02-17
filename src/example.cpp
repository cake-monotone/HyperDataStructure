#include<iostream>
#include<functional>
#include"hyper_array.cpp"

using namespace std;

int main(void) {
    auto assign_from_stdin = [](int &var) -> void {
        //cin >> var;
        var = 3;
    };

    array<size_t, 3> sizes = { 3, 3, 3 };

    hyper_array<int, 3> array(assign_from_stdin, sizes);

    // Print Cube!!
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            for (int k = 0; k < 3; k ++)
                cout << array[i][j][k] << ' ';
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

