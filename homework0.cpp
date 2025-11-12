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

int main(int argc, char* argv[]){

    auto totalTimeStart = chrono::steady_clock::now();                  // start total time

    ifstream inFile;
    string fileName;
    string line;
    vector<Movie> movies;

    fileName = argv[1];
    if (strstr(fileName.c_str() , "..") || strchr(fileName.c_str() , '/') || strchr(fileName.c_str() , '\\')) {
        printf("Invalid filename.\n");
        return 1;
    }

    char fileBuffer[PATH_MAX];
    snprintf(fileBuffer, sizeof(fileBuffer), "/home/user/files/%s", fileName);
    inFile.open(fileBuffer);

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

    ofstream outFileByName;
    ofstream outFileByDate;
    int i = 0;

    while(argv[1][i] != '.'){                                       //  Create a string "fileName" based on
        fileName += argv[1][i];                                     //  command line file name
        i++;                           
    }

    string finalFileByName = fileName + "ByName.txt";               // use "fileName" to construct a final file name
    string finalFileByDate = fileName + "ByDate.txt";               // based on sort method

    outFileByName.open(finalFileByName);

    for(int i = 0; i < movies.size(); i++){
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

    for(int i = 0; i < movies.size(); i++){
        outFileByDate << movies.at(i).title << " (" << movies.at(i).year        // write movies ordered by year to appropriate file
        << ")" << movies.at(i).actors << endl;
    }

    outFileByDate.close();

    auto totalTimeEnd = chrono::steady_clock::now();                            // end timing for total time
    chrono::duration<double> totalTime = totalTimeEnd - totalTimeStart;
    cout << "Total time: " << totalTime.count() << endl;

    return 0;
}