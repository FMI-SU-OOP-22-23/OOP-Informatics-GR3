#include <time.h>

#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>

/*
**
**  задача 1
**
*/

bool saveArrayToBinaryFile(const char* filename, const int* arr, int size) {
  // Create an output file stream and open the file in binary mode
  std::ofstream outfile(filename, std::ios::binary);

  // Check if the file is open
  if (!outfile.is_open()) {
    std::cerr << "Failed to open the file!" << std::endl;
    return 1;
  }

  outfile.write(reinterpret_cast<const char*>(arr), sizeof(int) * size);
  // Close the file
  outfile.close();
}

int* generateRandomArray(int count) {
  int* res = new (std::nothrow) int[count];
  if (!res) {
    return nullptr;
  }

  for (int i = 0; i < count; i++) {
    res[i] = rand();
  }

  return res;
}

int findBiggestIntFromBinFile(const char* filename) {
  std::ifstream input(filename);

  if (!input.is_open()) {
    std::cerr << "Failed to open the file!" << std::endl;
    return INT_MIN;
  }

  int maxVal = INT_MIN;
  while (!input.eof()) {
    int tmp;
    input.read(reinterpret_cast<char*>(&tmp), sizeof(int));

    if (tmp > maxVal) {
      maxVal = tmp;
    }
  }

  input.close();

  return maxVal;
}

/*
**
**  задача 2
**
*/
enum Genre {
  UNKNOWN = -1,
  ACTION,
  DRAMA,
  COMEDY,
  ROMANCE,
  HORROR,
  THRILLER,
  ADVENTURE
};

struct Movie {
  char name[255];
  int year;
  float length;
  Genre type;
};

const int LIBRARY_SIZE = 128;
struct MovieLibrary {
  char name[255];
  Movie movies[LIBRARY_SIZE];
  int availableMoviesCnt;
};

/// here we pass it as a pointer because it might be array of movies
bool saveMoviesToBinFile(const char* filename, const Movie* movies, int count) {
  std::ofstream outfile(filename, std::ios::binary);

  // Check if the file is open
  if (!outfile.is_open()) {
    std::cerr << "Failed to open the file!" << std::endl;
    return false;
  }

  outfile.write(reinterpret_cast<const char*>(movies), sizeof(Movie) * count);
  // Close the file
  outfile.close();
  return true;
}

bool saveMovieLibraryToBinFile(const char* filename, const MovieLibrary& lib) {
  std::ofstream outfile(filename, std::ios::binary);

  // Check if the file is open
  if (!outfile.is_open()) {
    std::cerr << "Failed to open the file!" << std::endl;
    return false;
  }

  outfile.write(reinterpret_cast<const char*>(&lib), sizeof(MovieLibrary));
  // Close the file
  outfile.close();
  return true;
}

bool readMovieFromBinFile(const char* filename, Movie& inMovie) {
  std::ifstream input(filename);

  if (!input.is_open()) {
    std::cerr << "Failed to open the file!" << std::endl;
    return false;
  }

  input.read(reinterpret_cast<char*>(&inMovie), sizeof(Movie));
  input.close();
  return true;
}

/// analogically we can read the MovieLibrary as well

int main() {
  /*
  **
  **  задача 1
  **
  */
  const int NUM_INTS = 64;               // number of integers to generate
  const char* FILENAME = "numbers.dat";  // filename to save to
  srand(time(nullptr));

  int* arr = generateRandomArray(NUM_INTS);
  saveArrayToBinaryFile(FILENAME, arr, NUM_INTS);
  delete[] arr;

  std::cout << findBiggestIntFromBinFile(FILENAME);

  /*
  **
  **  задача 2
  **
  */
  Movie movies[] = {{"Titanic", 1997, 3.25, Genre::ROMANCE},
                    {"Die hard", 1988, 2.2, Genre::ACTION},
                    {"The last of us", 2023, 1, Genre::THRILLER},
                    {"Jurassic Park", 1993, 2.15, Genre::ADVENTURE},
                    {"Scream", 1996, 2, Genre::HORROR},
                    {"The notebook", 2004, 2, Genre::ROMANCE},
                    {"The silence of the lambs", 1991, 1.9, Genre::HORROR}};

  saveMoviesToBinFile("movies.bin", movies, 7);
  Movie m;
  readMovieFromBinFile("movies.bin", m);
}