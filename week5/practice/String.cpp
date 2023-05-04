#include <iostream>
#include <ostream>

class String {
 public:
  String();
  String(const char* str);
  String(const String& other) = delete;
  String& operator=(const String& other);
  ~String() { clean(); }

  unsigned int length() { return size; }
  const char* c_str() const { return buf; }
  const String& append(const String& other);

 private:
  void clean();
  void setString(const char* str);

  char* buf;
  int size;
};

String::String() : buf(new char[1]), size(1) { buf[0] = '\0'; }

String::String(const char* str) : buf(nullptr), size(0) { setString(str); }

const String& String::append(const String& other) {
  int tmpSize = size + other.size - 1;
  char* tmpBuff = new char[tmpSize];

  strcpy(tmpBuff, buf);
  strcat(tmpBuff, other.buf);

  clean();

  buf = tmpBuff;
  size = tmpSize;

  return *this;
}

String& String::operator=(const String& other) {
  if (this != &other) {
    clean();
    setString(other.buf);
  }

  return *this;
}

void String::clean() {
  if (buf != nullptr) {
    delete[] buf;
    buf = nullptr;
  }
  size = 0;
}

void String::setString(const char* str) {
  size = strlen(str) + 1;
  buf = new char[size];
  strcpy(buf, str);
}

int main() {
  String a("FirstName");
  String b(" LastName");
  std::cout << a.append(b).c_str() << " " << a.length();
  return 0;
}