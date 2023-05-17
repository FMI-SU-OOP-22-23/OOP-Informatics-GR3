#include <iostream>
#include <fstream>
#include <cstring>

// task 1

struct Point
{
    float x,y;
};

/// @brief Reads points from given filename
/// @param filename 
/// @param points output param in for reading points
/// @param size ouput param with count of points read
bool readPoints(const char* filename, Point*& points /*out*/, int& size/*out*/) {

    std::ifstream in(filename, std::ios::binary);
    if(!in) { //first check if we've opened the file
        std::cerr << "Error: Couldn't open file: " << filename << std::endl;
        return false;
    }
    
    // find file size so we can count the points
    in.seekg(0, std::ios::end);
    int fileSize = in.tellg();
    in.seekg(0, std::ios::beg);

    size = fileSize/sizeof(Point);
    if(!in.good()) {
        std::cerr << "Error: file broken\n";
        return false;
    }

    try {
        points = new Point[size];
    } catch (const std::bad_alloc&) {
        in.close();
        return false;
    }

    in.read(reinterpret_cast<char*>(points), size*sizeof(Point));
    in.close();
    return true;
}

/// @brief Finds the center of gravity of given points
/// @param points pointer to the points
/// @param size count of points
/// @return the center of gravity as a Point object
Point centerOfGravity(const Point* points, int size) {
    Point center{0.f, 0.f};

    for(int i = 0; i < size; ++i) {
        center.x += points[i].x;
        center.y += points[i].y;
    }

    center.x /= float(size);
    center.y /= float(size);

    return center;
}

/// @brief Gets the distance between two points squared
/// @param a point
/// @param b point
/// @return 
double getDistanceSq(const Point& a, const Point& b) {
    return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
}

/// @brief finds and prints the three furthest points from center
/// @param points 
/// @param size 
void printFurthestThree(const Point* points, int size) {
    if (size < 3) {
        std::cerr << "There are less than 3 points.\n";
        return;
    }

    Point center = centerOfGravity(points, size);
    Point furthest[3] = {center,};
    std::cout << center.x << "  " << center.y << std::endl;

    for (int i = 0; i < size; ++i) {
        double distanceFromCenter = getDistanceSq(center, points[i]);
        if (distanceFromCenter > 
           getDistanceSq(center,furthest[0])) {
            furthest[2] = furthest[1];
            furthest[1] = furthest[0];
            furthest[0] = points[i];
           } else if (distanceFromCenter > 
           getDistanceSq(center,furthest[1])) {
            furthest[2] = furthest[1];
            furthest[1] = points[i];
           } else if (distanceFromCenter > 
           getDistanceSq(center,furthest[2])) {
            furthest[2] = points[i];
           }
    }

    std::cout << "Point 1: x: " << furthest[0].x << " y: " << furthest[0].y << std::endl;
    std::cout << "Point 2: x: " << furthest[1].x << " y: " << furthest[1].y << std::endl;
    std::cout << "Point 3: x: " << furthest[2].x << " y: " << furthest[2].y << std::endl;
}

/// @brief check whether point is inside a circle
/// @param p point
/// @param circleCenter point to the circle center
/// @param radius of the center
bool isInCircle(const Point& p, const Point& circleCenter, float radius) {
    return getDistanceSq(p, circleCenter) <= radius * radius;
}

/// @brief prints all the points in the array
/// @param points 
/// @param size 
void printPoints(const Point* points, int size) {
    for(int i = 0; i < size; ++i) {
        std::cout << "Point x: " << points[i].x << " y: " << points[i].y << std::endl;
    }
}

/// @brief writes some points in a binary file
/// @param filename 
bool writeToBinFile(const char* filename) {
    Point points[] = {
        {1.2f, 3.4f},
        {5.6f, 7.8f},
        {9.0f, 1.2f},
        {3.4f, 5.6f},
        {2.0f, 4.0f},
        {6.0f, 8.0f},
        {0.5f, 1.5f}
    };

    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        std::cerr << "Error opening the file." << std::endl;
        return false;
    }

    // Write the array of points to the file
    outfile.write(reinterpret_cast<const char*>(points), sizeof(points));

    // Close the file
    outfile.close();

    std::cout << "Binary file " << filename << " created successfully." << std::endl;
    return true;

}

/// @brief replaces the points outside the circle with the center of the circle
/// @param center 
/// @param radius 
/// @param points 
/// @param size 
void replacePointsOutsideCircle(const Point& center, float radius, Point* points, int size) {
    for (int i = 0; i < size; ++i) {
        if(!isInCircle(points[i], center, radius)) {
            points[i] = center;
        }
    }
}
/// end of task 1

/// task 2

/// @brief class representing Person with names, yearOfBirth and gender
struct Person
{
public:
    // Parameterized constructor
    Person(const char* newName, const char* newSurname, int newYearOfBirth, bool newIsMale)
        : name(nullptr), surname(nullptr), yearOfBirth(newYearOfBirth), isMale(newIsMale)
    {
        if (!setName(newName)){ /*we should probably throw or say sth here*/};
        if (!setSurname(newName)){ /*we should probably throw or say sth here*/};
    }

    // Destructor
    ~Person() {
        delete[] name;
        delete[] surname;
    }

    // Copy constructor
    Person(const Person& other)
        : name(nullptr), surname(nullptr), yearOfBirth(other.yearOfBirth), isMale(other.isMale)
    {
        setName(other.name);
        setSurname(other.surname);
    }

    // Copy assignment operator
    Person& operator=(const Person& other) {
        if (this != &other) {
            setName(other.name);
            setSurname(other.surname);
            yearOfBirth = other.yearOfBirth;
            isMale = other.isMale;
        }
        return *this;
    }

    const char* getName() const {
        return name;
    }

    bool setName(const char* newName) {
        if(!isValidName(newName)) { return false; }

        // in this way we will not brake the object in case of exception
        try {
            char* nameTmp = new char[strlen(newName) + 1];
            strcpy(nameTmp, newName);
            delete[] name;
            name = nameTmp;
            return true;
        } catch (const std::bad_alloc&) {
            /// we may want to rethrow, log or do sth else here
            return false;
        }
    }

    const char* getSurname() const {
        return surname;
    }

    bool setSurname(const char* newSurname) {
        if(!isValidName(newSurname)) { return false; }

        // in this way we will not brake the object in case of exception
        try {
            char* surnameTmp = new char[std::strlen(newSurname) + 1];
            std::strcpy(surnameTmp, newSurname);
            delete[] surname;
            surname = surnameTmp;
            return true;
        } catch (const std::bad_alloc&) {
            /// we may want to rethrow, log or do sth else here
            return false;
        }
    }

    int getYearOfBirth() const {
        return yearOfBirth;
    }

    bool setYearOfBirth(int newYearOfBirth) {
        if (!isValidYearOfBirth(newYearOfBirth)) {
            return false;
        }
        yearOfBirth = newYearOfBirth;
        return true;
    }

    bool isMaleGender() const {
        return isMale;
    }

    bool isFemaleGender() const {
        return !isMale;
    }

    void setIsMale(bool newIsMale) {
        isMale = newIsMale;
    }

private:
    bool isValidYearOfBirth(int year) { return year >= 1900 && year <= 2023; }

    /// we should probably check for spaces as well
    bool isValidName(const char* name) { return name != nullptr && name[0] != '\0'; }

    char* name;
    char* surname;
    bool isMale;
    int yearOfBirth;
};

/// @brief struct representing car, we don't need anything from G4 as there 
/// are no resources to manage explicitly
struct Car {
    char brand[128];
    Person owner;
    int year;
};

bool saveCarsToTextFile(const char* filename, Car* cars, int size) {
    std::ofstream out(filename);

    if(!out) {
        std::cerr << "Error: Openning file failed!\n";
        return false;
    }

    out << size << std::endl; //write the cars count first
    int i = 0;
    while(i < size && out) {
        out << cars[i].brand << std::endl;
        out << cars[i].owner.getName() << std::endl;
        out << cars[i].owner.getSurname() << std::endl;
        out << cars[i].owner.isMaleGender() << std::endl;
        out << cars[i].owner.getYearOfBirth() << std::endl;
        out << cars[i].year << std::endl;
        ++i;
    }

    if(!out) {
        std::cerr << "An error occured after writting!\n";
        return false;
    }

    out.close();
    return true;
}

int main() {
/// task 1
    const char* filename = "points.dat";
    if (!writeToBinFile(filename)) {
        std::cerr << "Couldn't write file!";
        return 1;
    }

    int size = 0;
    Point* points = nullptr;
    if (!readPoints(filename, points, size)) {
        std::cerr << "Couldn't read file!";
        return 1;
    }

    printPoints(points, size);
    printFurthestThree(points, size);

    float radius = 0;
    std::cin >> radius;

    replacePointsOutsideCircle(centerOfGravity(points, size), radius, points, size);
    printPoints(points, size);
    delete[] points;
/// end of task 1

/// task 2
    Person ivan("ivan", "ivanov", 1928, true);
    Person maria("maria", "marinova", 1234, false);

    Car lambo{"lambo", ivan, 2023};
    Car ferrari{"ferrari", maria, 2022};

    Car cars[] = {lambo, ferrari};

    if (!saveCarsToTextFile("cars.txt", cars, 2)) {
        std::cerr << "Couldn't write file!";
        return 1;
    }
/// end of task 2

    return 0;
}