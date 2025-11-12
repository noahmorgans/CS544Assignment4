/*
    Name: Noah Morgans
    Email: nmorgans@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Instructions to Compile: "g++ homework0.cpp -std=c++11"
    Instructions to Execute: "./a.out **filename**"
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstring>
using namespace std;

class Movie{

    public:

    string title;
    int year;
    string actors;

    Movie(){
            this->title = "";
            this->year = 0;                        // default constructor
            this->actors = "";
    }

    Movie(string fileLine){

        int idx = 0;
        string yr;

        while(fileLine.at(idx + 1) != '('){
        this->title += fileLine.at(idx);                // read fileLine until '('
        idx++;                                          // to get movie title
        }

        idx += 2;

        while(fileLine.at(idx) != ')'){
            yr += fileLine.at(idx);                     // read fileLine until ')'
            idx++;                                      // to get year
        }

        this->year = stoi(yr);
        idx++;

        while(idx < fileLine.size()){           
            this->actors += fileLine.at(idx);           // read rest of fileLine
            idx++;                                      // to get actors
        }
    }

};

// Validate filename to prevent path traversal attacks
bool isValidFilename(const string& filename) {
    // Check for path traversal patterns
    if (filename.find("..") != string::npos) {
        return false;
    }
    
    // Check for absolute paths or directory separators
    if (filename.find('/') != string::npos || filename.find('\\') != string::npos) {
        return false;
    }
    
    // Check if filename is empty
    if (filename.empty()) {
        return false;
    }
    
    return true;
}

// Extract base filename without path and extension
string getBaseFilename(const char* filepath) {
    string filename = filepath;
    
    // Find last directory separator (if any)
    size_t lastSlash = filename.find_last_of("/\\");
    if (lastSlash != string::npos) {
        filename = filename.substr(lastSlash + 1);
    }
    
    // Remove extension
    size_t lastDot = filename.find_last_of('.');
    if (lastDot != string::npos) {
        filename = filename.substr(0, lastDot);
    }
    
    return filename;
}

int main(int argc, char* argv[]){

    if (argc < 2) {
        cerr << "Error: No input file specified" << endl;
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    auto totalTimeStart = chrono::steady_clock::now();                  // start total time

    ifstream inFile;
    string line;
    vector<Movie> movies;

    inFile.open(argv[1]);
    
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    auto startTime = chrono::steady_clock::now();                       // start timing for creating collections

    while(getline(inFile, line)){                                       //  Construct an object of class
        movies.push_back(Movie(line));                                  //  "Movie" then add to back
    }                                                                   //   of vector "movies"

    auto endTime = chrono::steady_clock::now();                         // end timing for creating collections
    chrono::duration<double> time = endTime - startTime;

    cout << "Total number of movies: " << movies.size() << endl;
    cout << "Time to create collection: " << time.count() << endl;

    inFile.close();

    startTime = chrono::steady_clock::now();                                        // start timing for sorting by title
    
    sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b) {
            if(a.title != b.title)
                return a.title < b.title;                                           // sort objects of class "movie"
            else                                                                    // by title first, then year
                return a.year < b.year;                                             // using a lambda function
        }   
    );

    endTime = chrono::steady_clock::now();                                          // stop timing for sorting by title
    time = endTime - startTime;

    cout << "Time take to sort by title: " << time.count() << endl;

    // Extract and validate base filename
    string fileName = getBaseFilename(argv[1]);
    
    // Validate the extracted filename
    if (!isValidFilename(fileName)) {
        cerr << "Error: Invalid filename detected (possible path traversal attempt)" << endl;
        return 1;
    }

    string finalFileByName = fileName + "ByName.txt";               // use "fileName" to construct a final file name
    string finalFileByDate = fileName + "ByDate.txt";               // based on sort method

    ofstream outFileByName;
    ofstream outFileByDate;

    outFileByName.open(finalFileByName);
    
    if (!outFileByName.is_open()) {
        cerr << "Error: Could not create output file " << finalFileByName << endl;
        return 1;
    }

    for(size_t i = 0; i < movies.size(); i++){
        outFileByName << movies.at(i).title << " (" << movies.at(i).year        // write movies ordered by title to appropriate file
        << ")" << movies.at(i).actors << endl;
    }

    outFileByName.close();

    startTime = chrono::steady_clock::now();                                        // start timing for sorting by date

    sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b) {
            if (a.year != b.year)
                return a.year < b.year;                                             // sort objects of class "Movie"
            else                                                                    // by date first, then title
                return a.title < b.title;                                           // using a lambda function           
        }                                                                           
    );

    endTime = chrono::steady_clock::now();                                         // end timing for sorting by date
    time = endTime - startTime;

    cout << "Time to sort by date: " << time.count() << endl;

    outFileByDate.open(finalFileByDate);
    
    if (!outFileByDate.is_open()) {
        cerr << "Error: Could not create output file " << finalFileByDate << endl;
        return 1;
    }

    for(size_t i = 0; i < movies.size(); i++){
        outFileByDate << movies.at(i).title << " (" << movies.at(i).year        // write movies ordered by year to appropriate file
        << ")" << movies.at(i).actors << endl;
    }

    outFileByDate.close();

    auto totalTimeEnd = chrono::steady_clock::now();                            // end timing for total time
    chrono::duration<double> totalTime = totalTimeEnd - totalTimeStart;
    cout << "Total time: " << totalTime.count() << endl;

    return 0;
}