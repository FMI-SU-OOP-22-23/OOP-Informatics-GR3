#include <iostream>

void sumThrow(int n) {
    if (n <= 0) {
        throw 0;
    } else {
        try {
            sumThrow(n - 1);
        } catch (int s) {
            throw s + n;
        }
    }
}

int main() {
  try {
    sumThrow(6);
  } catch (int e) {
    std::cout << "sum is: " << e;
  }
  return 0;
}