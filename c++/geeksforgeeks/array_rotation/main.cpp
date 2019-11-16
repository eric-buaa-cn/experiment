#include <iostream>

void print_array(int* arr, int size) {
    std::cout << "arr[";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i != size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// time: O(n), Space: O(n)
void array_rotation1(int* arr, int d, int size) {
    int* arr_target = new int[size];

    // [d, size)
    for (int i = d; i < size; ++i) {
        arr_target[i-d] = arr[i];
    }
    // [0, d)
    for (int i = 0; i < d; ++i) {
        arr_target[size-d+i] = arr[i];
    }

    // copy arr_target to arr
    for (int i = 0; i < size; ++i) {
        arr[i] = arr_target[i];
    }
    delete [] arr_target;
}

// time: O(d*n), space: O(1)
void array_rotation2(int* arr, int d, int size) {
    for (int i = 0; i < d; ++i) {
        int tmp = arr[0];

        for (int j = 1; j < size; ++j) {
            arr[j-1] = arr[j];
        }
        arr[size-1] = tmp;
    }
}

static int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else return gcd(b, a%b);
}

// time: O(n), space: O(1)
void array_rotation3(int* arr, int d, int size) {
    int g_c_d = gcd(size, d);

    for (int round = 0; round < g_c_d; ++round) {
        int tmp = arr[round];
        int slot = round;
        while (true) {
            int next_slot = slot + d;
            if (next_slot >= size) {
                next_slot -= size;
            }
            if (next_slot == round) {
                break;
            }

            arr[slot] = arr[next_slot];
            slot = next_slot;
        }
        arr[slot] = tmp;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    int d = 2;

    {
        int* arr_cpy = new int[n];
        for (int i = 0; i < n; ++i) {
            arr_cpy[i] = arr[i];
        }
        array_rotation1(arr_cpy, d, n);
        print_array(arr_cpy, n);
        delete [] arr_cpy;
    }

    {
        int* arr_cpy = new int[n];
        for (int i = 0; i < n; ++i) {
            arr_cpy[i] = arr[i];
        }
        array_rotation2(arr_cpy, d, n);
        print_array(arr_cpy, n);
        delete [] arr_cpy;
    }

    {
        int* arr_cpy = new int[n];
        for (int i = 0; i < n; ++i) {
            arr_cpy[i] = arr[i];
        }
        array_rotation3(arr_cpy, d, n);
        print_array(arr_cpy, n);
        delete [] arr_cpy;
    }
    return 0;
}