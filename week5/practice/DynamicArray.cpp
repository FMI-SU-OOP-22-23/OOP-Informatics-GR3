#include <time.h>

#include <iostream>

class DynamicArray {
 public:
  /// G4 + constructor with parameter
  DynamicArray();
  DynamicArray(int cap);

  DynamicArray& operator=(const DynamicArray& other);
  DynamicArray(const DynamicArray& other);
  ~DynamicArray();

  /// help functions
 private:
  void copyFrom(const DynamicArray&);
  void clean();
  void resize(int);

  /// interface
 public:
  /// @brief adds new element at array's end
  /// @param el inserts the element in the array
  void pushBack(int el);

  /// @brief gets a value at wanted index
  /// @param idx
  /// @return the value at index
  int getAt(int idx) const;

  /// @brief sets a value at wanted index
  /// @param idx the position in the arr
  /// @param val the value to be set
  void setAt(int idx, int val);

  /// @brief removes the last element
  void popBack();

  /// @brief removes element on given index
  /// @param idx index
  /// @param keepOrder let the user to decide if should keep the ordering or
  /// just swap the idx and last element
  void removeAt(int idx, bool keepOrder = true);

  int getSize() const;
  int getCapacity() const;

  void printInfo() const;

 private:
  int* pData;
  int size;      // how many actual values are stored
  int capacity;  // what is the maximum allocated memory in given moment
};

// or = default in the declaration
DynamicArray::DynamicArray() : pData(nullptr), size(0), capacity(0) {}

// creates a dynamic array with wanted cap
DynamicArray::DynamicArray(int cap) : size(0), capacity(cap) {
  pData = new int[capacity];
}

DynamicArray::~DynamicArray() { clean(); }

void DynamicArray::clean() {
  delete[] pData;

  pData = nullptr;
  size = 0;
  capacity = 0;
}

void DynamicArray::copyFrom(const DynamicArray& other) {
  pData = new int[other.capacity];

  memcpy(pData, other.pData, other.size * sizeof(int));

  // or
  /*for (int i = 0; i < other.CurSize; i++) {
          data[i] = other.data[i];
  }*/

  size = other.size;
  capacity = other.capacity;
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : pData(nullptr), size(0), capacity(0) {
  copyFrom(other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
  if (this != &other) {
    clean();
    copyFrom(other);
  }

  return *this;
}

// allocates new memory for our buffer
// copies all old values
void DynamicArray::resize(int newCap) {
  int* temp = pData;

  // allocating new memory
  pData = new int[newCap];

  // copies all old values
  memcpy(pData, temp, size * sizeof(int));

  capacity = newCap;

  delete[] temp;
}

void DynamicArray::pushBack(int elem) {
  if (size >= capacity) {
    int newCap = (capacity == 0) ? 2 : capacity * 2;  // handles capacity 0
    resize(newCap);
  }

  pData[size++] = elem;
}

void DynamicArray::popBack() {
  if (size) {
    size--;
  } else {
    throw std::length_error("already empty!");
  }

  if (size * 2 <= capacity) {  // downsizing needed
    int newCap = ((size == 0) ? 0 : capacity / 2);
    resize(newCap);
  }
}

void DynamicArray::setAt(int idx, int val) {
  if (idx >= size) return;
  // throw std::out_of_range("out of range!");

  pData[idx] = val;
}

int DynamicArray::getAt(int idx) const {
  if (idx < 0 || idx >= size) {
    throw std::out_of_range("out of range!!!");
  }

  return pData[idx];
}

void DynamicArray::removeAt(int idx, bool keepOrder) {
  if (idx >= size || size == 1) {  // just removes the last elem
    popBack();
    return;
  }

  if (keepOrder) {
    memcpy(pData + idx, pData + idx + 1, (size - (idx + 1)) * sizeof(int));
    popBack();
    return;
  }

  // faster version O(1), but can be
  // unexpected from the user
  pData[idx] = pData[size - 1];
  popBack();
}

int DynamicArray::getSize() const { return size; }

int DynamicArray::getCapacity() const { return capacity; }

void DynamicArray::printInfo() const {
  std::cout << "obj at: Ox" << this << " buffer starts at: Ox" << pData
            << " length:" << size << " capacity:" << capacity << std::endl;
}

int main() {
  srand(time(nullptr));

  DynamicArray arr;
  for (int i = 0; i < 10; ++i) {
    arr.pushBack(random() % 1997 + 1);
  }
  arr.printInfo();

  for (int i = 0; i < arr.getSize(); ++i) {
    std::cout << arr.getAt(i) << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < 5; ++i) {
    arr.removeAt(i);
  }
  arr.printInfo();

  for (int i = 0; i < 5; ++i) {
    arr.pushBack(random() % 1997 + 1);
  }
  arr.printInfo();

  for (int i = 0; i < 5; ++i) {
    arr.setAt(i, i);
  }
  arr.printInfo();

  for (int i = 0; i < arr.getSize(); ++i) {
    std::cout << arr.getAt(i) << std::endl;
  }
  arr.printInfo();
}