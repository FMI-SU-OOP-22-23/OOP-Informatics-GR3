#include <fstream>
#include <iostream>

/*
**
**  задача 1
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

void serializeMovie(const Movie &movie, const char *filename) {
  // Open the file for writing
  std::ofstream outfile(filename);

  // Write the movie data to the file
  if (outfile.is_open()) {
    outfile << movie.year << " " << movie.length << " " << movie.type << " "
            << movie.name << "\n";
  } else {
    std::cerr << "Error opening file for writing\n";
  }

  // Close the file
  outfile.close();
}

void streamInMovie(Movie &movie, std::istream &in) {
  int movieGenre = -1;
  in >> movie.year >> movie.length >> movieGenre;
  movie.type = Genre(movieGenre);
  in.ignore();  // Ignore the space before the name
  in.getline(movie.name, 255);
}

void deserializeMovie(Movie &movie, const char *filename) {
  // Open the file for reading
  std::ifstream infile(filename);

  // Read the movie data from the file
  if (infile.is_open()) {
    streamInMovie(movie, infile);
  } else {
    std::cerr << "Error opening file for reading\n";
  }

  // Close the file
  infile.close();
}

/// in this way we can print both in file and in std::cout
void streamOutMovie(const Movie &m, std::ostream &out) {
  out << m.type << " " << m.length << " " << m.year << " " << m.name
      << std::endl;
}

bool storeMovies(const Movie *movies, int cnt, const char *filename) {
  // Open the file for writing
  std::ofstream outfile(filename);

  // Write the movie data to the file
  if (outfile.is_open()) {
    for (int i = 0; i < cnt; ++i) {
      streamOutMovie(movies[i], outfile);
    }
  } else {
    std::cout << "Error opening file for writing\n";
    return false;
  }

  return true;
}

/*
**
**  задача 2
**
*/

const int LIBRARY_SIZE = 128;
struct MovieLibrary {
  char name[255];
  Movie movies[LIBRARY_SIZE];
  int availableMoviesCnt;
};

void readLibraryMovies(MovieLibrary &lib, const char *filename) {
  std::ifstream input(filename);

  if (input) {
    int i = 0;
    while (!input.eof() && i < LIBRARY_SIZE) {
      streamInMovie(lib.movies[i++], input);
    }
    lib.availableMoviesCnt = i;
  } else {
    std::cerr << "Error opening file for reading\n";
  }
}

void initMovieLibrary(MovieLibrary &lib, const char *libName, const char *filename) {
  // we should be sure that this will be less 255 symbols
  strcpy(lib.name, libName);
  readLibraryMovies(lib, filename);
}

bool addMovieInLibrary(const Movie &m, MovieLibrary &lib) {
  if (lib.availableMoviesCnt >= LIBRARY_SIZE) {
    std::cerr << "The library shelve is full!";
    return false;
  }

  lib.movies[lib.availableMoviesCnt++] = m;
  return true;
}

Movie findLongestMovie(const MovieLibrary &lib) {
  float minLen = -1;
  int longestMovieIndex = 0;
  for (int i = 0; i < lib.availableMoviesCnt; ++i) {
    /// think for a better way of comparing floating numbers
    /// and why will this way won't work in all cases
    if (lib.movies[i].length > minLen) {
      minLen = lib.movies[i].length;
      longestMovieIndex = i;
    }
  }

  return lib.movies[longestMovieIndex];
}

int main(int argc, char *argv[]) {
  const Movie movies[] = {
      {"Titanic", 1997, 3.25, Genre::ROMANCE},
      {"Die hard", 1988, 2.2, Genre::ACTION},
      {"The last of us", 2023, 1, Genre::THRILLER},
      {"Jurassic Park", 1993, 2.15, Genre::ADVENTURE},
      {"Scream", 1996, 2, Genre::HORROR},
      {"The notebook", 2004, 2, Genre::ROMANCE},
      {"The silence of the lambs", 1991, 1.9, Genre::HORROR},
  };

  MovieLibrary lib;
  initMovieLibrary(lib, "movies.txt");

  Movie m = {"American pie", 2001, 1.8, Genre::COMEDY};
  addMovieInLibrary(m, lib);

  streamOutMovie(findLongestMovie(lib), std::cout);

  return 0;
}