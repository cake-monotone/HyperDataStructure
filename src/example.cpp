#include<iostream>
#include"hyper_array.cpp"

using namespace std;

int main(void) {
    hyper_array<int, 3> array(3, 3, 3);

    for (int i = 0; i < 3; i ++) {
        array[i][i][i] = 1;
    }

    // Print Qube!!
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            for (int k = 0; k < 3; k ++)
                cout << array[i][j][k] << ' ';
            cout << endl;
        }
        cout << endl;
    }
    
    cout << array.size(3) << endl; // 3

    return 0;
}

