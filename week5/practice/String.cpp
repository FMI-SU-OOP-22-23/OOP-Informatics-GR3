#include <iostream>
#include <ostream>

class String {
 public:
  String() : buf(new char[1]), size(1) { buf[0] = '\0'; }

  String(const char* str) { setString(str); }

  String(const String& other) { setString(other.buf); }

  String& operator=(const String& other) {
    if (this != &other) {
      clean();
      setString(other.buf);
    }

    return *this;
  }

  unsigned int length() { return size; }

  const char* c_str() const { return buf; }

  const String& append(const String& other) {
    int tmpSize = size + other.size - 1;
    char* tmpBuff = new char[tmpSize];

    strcpy(tmpBuff, buf);
    strcat(tmpBuff, other.buf);

    clean();

    buf = tmpBuff;
    size = tmpSize;

    return *this;
  }

  ~String() { clean(); }

 private:
  void clean() {
    if (buf != nullptr) {
      delete[] buf;
      buf = nullptr;
    }
    size = 0;
  }

  void setString(const char* str) {
    size = strlen(str) + 1;
    buf = new char[size];
    strcpy(buf, str);
    buf[size] = '\0';
  }

  char* buf;
  int size;
};

int main() {
  String a("FirstName");
  String b(" LastName");
  std::cout << a.append(b).c_str() << " " << a.length();
  return 0;
}