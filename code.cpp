#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "seatlayoutprinter.cpp"
using namespace std;

int main() {
    // Open data_filtered.csv file
    ifstream dataFile("data_filtered.csv");
    if (!dataFile.is_open()) {
        cout << "Error opening data_filtered.csv file" << endl;
        return 1;
    }

    // Read unique city names from the first column 'city' of data_filtered.csv
    vector<string> cities;
    string line;
    getline(dataFile, line); // skip header line
    while (getline(dataFile, line)) {
        string city = line.substr(0, line.find(","));
        if (find(cities.begin(), cities.end(), city) == cities.end()) {
            cities.push_back(city);
        }
    }
    dataFile.close();

    // Print unique city names and allow user to select a city
    cout << "Select a city:" << endl;
    for (int i = 0; i < cities.size(); i++) {
        cout << i+1 << ". " << cities[i] << endl;
    }
    int cityIndex;
    printf("Enter the Number Corresponding to the City: ");
    cin >> cityIndex;
    string selectedCity = cities[cityIndex-1];

    // Open data_filtered.csv file again to read theatres corresponding to selected city
    ifstream theatreFile("data_filtered.csv");
    if (!theatreFile.is_open()) {
        cout << "Error opening data_filtered.csv file" << endl;
        return 1;
    }

    // Read unique theatre names from the second column 'theatre_name' of data_filtered.csv corresponding to selected city
    vector<string> theatres;
    getline(theatreFile, line); // skip header line
    while (getline(theatreFile, line)) {
        string city = line.substr(0, line.find(","));
        if (city == selectedCity) {
            string theatre = line.substr(line.find(",")+1, line.find(",", line.find(",")+1)-line.find(",")-1);
            if (find(theatres.begin(), theatres.end(), theatre) == theatres.end()) {
                theatres.push_back(theatre);
            }
        }
    }
    theatreFile.close();

    // Print unique theatre names and allow user to select a theatre
    cout << "\nSelect a theatre:" << endl;
    for (int i = 0; i < theatres.size(); i++) {
        cout << i+1 << ". " << theatres[i] << endl;
    }
    int theatreIndex;
    printf("Enter the Number Corresponding to the theatre of choice: ");
    cin >> theatreIndex;
    string selectedTheatre = theatres[theatreIndex-1];

    // Open moviefinal.csv file
    ifstream movieFile("moviefinal.csv");
    if (!movieFile.is_open()) {
        cout << "Error opening moviefinal.csv file" << endl;
        return 1;
    }

    // Read movies available under 'Movie Name' column of moviefinal.csv
    vector<string> movies;
    getline(movieFile, line); // skip header line
    while (getline(movieFile, line)) {
        string movie = line.substr(0, line.find(","));
        movies.push_back(movie);
    }
    movieFile.close();

    // Print available movies and allow user to select a movie
    cout << "\nSelect a movie:" << endl;
    for (int i = 0; i < movies.size(); i++) {
        cout << i+1 << ". " << movies[i] << endl;
    }
    int movieIndex;
    printf("Enter the Number Corresponding to the movie of choice: ");
    cin >> movieIndex;
    string selectedMovie = movies[movieIndex-1];

    // Print available dates for the next 5 days and allow user to select a date
    cout << "\nSelect a date:" << endl;
    time_t now = time(0);
    for (int i = 0; i < 5; i++) {
        tm *ltm = localtime(&now);
        ltm->tm_mday += i;
        mktime(ltm);
        cout << i+1 << ". " << ltm->tm_mday << "/" << ltm->tm_mon+1 << "/" << ltm->tm_year+1900 << endl;
    }
    int dateIndex;
    printf("\nEnter the Number Corresponding to the date of choice: ");
    cin >> dateIndex;
    time_t selectedDate = now + (dateIndex-1)*24*60*60;

    seatprinter();
    printf("Enter the number of seats you want to book:");
    int seats;
    cin >> seats;
    string seatinfo[seats];
    for (int i = 0; i < seats; i++) {
        printf("Enter the seat number:");
        cin >> seatinfo[i];
    }

    // Print user's choices as formatted output
    cout << endl << "Selected city: " << selectedCity << endl;
    cout << "Selected theatre: " << selectedTheatre << endl;
    cout << "Selected movie: " << selectedMovie << endl;
    tm *ltm = localtime(&selectedDate);
    cout << "Selected date: " << ltm->tm_mday << "/" << ltm->tm_mon+1 << "/" << ltm->tm_year+1900 << endl;
    cout << "Selected seats: ";
    for (int i = 0; i < seats; i++) {
        cout << seatinfo[i] << " ";
    }

    // Get user's name and phone number
    string name, phoneNumber;
    cout << "\nEnter your name: ";
    cin >> name;
    cout << "\nEnter your phone number: ";
    cin >> phoneNumber;

    // Get user's payment option
    string paymentOption;
    cout << "\nSelect a payment option:" << endl;
    cout << "1. Cash on site" << endl;
    cout << "2. UPI" << endl;
    cout << "3. Debit card" << endl;
    cin >> paymentOption;

    // Store user's information, selected city, selected theatre, selected movie, selected date and payment option
    ofstream userInfoFile("user_info.txt");
    if (!userInfoFile.is_open()) {
        cout << "Error opening user_info.txt file" << endl;
        return 1;
    }
    userInfoFile << "Name: " << name << endl;
    userInfoFile << "Phone number: " << phoneNumber << endl;
    userInfoFile << "Payment option: ";
    if (paymentOption == "1") {
        userInfoFile << "Cash on site" << endl;
    } else if (paymentOption == "2") {
        userInfoFile << "UPI" << endl;
    } else if (paymentOption == "3") {
        userInfoFile << "Debit card" << endl;
    } else {
        userInfoFile << "Invalid payment option" << endl;
    }
    userInfoFile << "Selected City: " << selectedCity << endl;
    userInfoFile << "Selected Theatre: " << selectedTheatre << endl;
    userInfoFile << "Selected Movie: " << selectedMovie << endl;
    ltm = localtime(&selectedDate);
    userInfoFile << "Selected Date: " << ltm->tm_mday << "/" << ltm->tm_mon+1 << "/" << ltm->tm_year+1900 << endl;
    userInfoFile << "Selected Seats: ";
    for (int i = 0; i < seats; i++) {
        userInfoFile << seatinfo[i] << " ";
    }
    userInfoFile.close();

    return 0;
}
