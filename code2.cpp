#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> //find function
#include <ctime> //to get the current date and next 5 days from the current date
#include <iomanip> //not being used
#include <cstdlib> //using for exit function
#include <regex>
#include "seatlayoutprinter.cpp"

using namespace std;

class BookingSystem {
public:
    void run() {
        if (!readCityData()) {
            cout << "Error reading city data." << endl;
            return;
        }

        selectCity();

        if (!readTheatreData()) {
            cout << "Error reading theatre data." << endl;
            return;
        }

        selectTheatre();

        if (!readMovieData()) {
            cout << "Error reading movie data." << endl;
            return;
        }

        selectMovie();

        selectDate();

        seatPrinter();

        selectSeats();

        printUserChoices();

        getUserInfo();

        storeUserInfo();
    }

private:
    vector<string> cities;
    string selectedCity;
    vector<string> theatres;
    string selectedTheatre;
    vector<string> movies;
    string selectedMovie;
    time_t selectedDate;
    vector<string> selectedSeats; //vector<string> is a dynamic array of strings
    string name;
    string phoneNumber;
    string paymentOption;

    bool readCityData() {
        ifstream dataFile("data_filtered.csv");
        if (!dataFile.is_open()) {
            cout << "Error opening data_filtered.csv file" << endl;
            return false;
        }

        string line;
        getline(dataFile, line); // skip header line
        while (getline(dataFile, line)) {
            string city = line.substr(0, line.find(","));
            if (find(cities.begin(), cities.end(), city) == cities.end()) {
                cities.push_back(city);
            }
        } //gets the city name from the csv file and stores it in the vector cities, unique values only.
        dataFile.close();
        return true;
    }

    void selectCity() {
        cout << "Select a city:" << endl;
        for (int i = 0; i < cities.size(); i++) {
            cout << i + 1 << ". " << cities[i] << endl;
        }

        int cityIndex;
        cout << "Enter the Number Corresponding to the City: ";
        cin >> cityIndex;
        selectedCity = cities[cityIndex - 1]; //number entered by user is used to select the city from the vector cities
    }

    bool readTheatreData() {
        ifstream theatreFile("data_filtered.csv");
        if (!theatreFile.is_open()) {
            cout << "Error opening data_filtered.csv file" << endl;
            return false;
        }

        string line;
        getline(theatreFile, line); // skip header line
        while (getline(theatreFile, line)) {
            string city = line.substr(0, line.find(","));
            if (city == selectedCity) {
                string theatre = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);
                if (find(theatres.begin(), theatres.end(), theatre) == theatres.end()) {
                    theatres.push_back(theatre);
                }
            }
        } //for the selected city, all the theatres are read from the csv file and added to the vector theatres
        theatreFile.close();
        return true;
    }

    void selectTheatre() {
        cout << "\nSelect a theatre:" << endl;
        for (int i = 0; i < theatres.size(); i++) {
            cout << i + 1 << ". " << theatres[i] << endl;
        }

        int theatreIndex;
        cout << "Enter the Number Corresponding to the theatre of choice: ";
        cin >> theatreIndex;
        selectedTheatre = theatres[theatreIndex - 1];
    } //indexing is used to select the theatre from the vector theatres

    bool readMovieData() {
        ifstream movieFile("moviefinal.csv");
        if (!movieFile.is_open()) {
            cout << "Error opening moviefinal.csv file" << endl;
            return false;
        }

        string line;
        getline(movieFile, line); // skip header line
        while (getline(movieFile, line)) {
            string movie = line.substr(0, line.find(","));
            movies.push_back(movie);
        }
        movieFile.close();
        return true;
    } //all the movies are read from the csv file and added to the vector movies

    void selectMovie() {
        cout << "\nSelect a movie:" << endl;
        for (int i = 0; i < movies.size(); i++) {
            cout << i + 1 << ". " << movies[i] << endl;
        }

        int movieIndex;
        cout << "Enter the Number Corresponding to the movie of choice: ";
        cin >> movieIndex;
        selectedMovie = movies[movieIndex - 1];
    } //indexing is used to select the movie from the vector movies

    void selectDate() {
        cout << "\nSelect a date:" << endl;
        time_t now = time(0);
        for (int i = 0; i < 5; i++) {
            tm* ltm = localtime(&now);
            ltm->tm_mday += i;
            mktime(ltm);
            cout << i + 1 << ". " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year + 1900 << endl;
        } //the next 5 days are printed and the user is asked to select a date

        int dateIndex;
        cout << "\nEnter the Number Corresponding to the date of choice: ";
        cin >> dateIndex;
        selectedDate = now + (dateIndex - 1) * 24 * 60 * 60;
    }

    void seatPrinter() {
        seatprinter();
    }

    void selectSeats() {
        cout << "Enter the number of seats you want to book:";
        int seats;
        cin >> seats;
        selectedSeats.resize(seats);
        for (int i = 0; i < seats; i++) {
            cout << "Enter the seat number:";
            cin >> selectedSeats[i];
        }
    }

    void printUserChoices() {
        cout << endl << "Selected city: " << selectedCity << endl;
        cout << "Selected theatre: " << selectedTheatre << endl;
        cout << "Selected movie: " << selectedMovie << endl;
        tm* ltm = localtime(&selectedDate);
        cout << "Selected date: " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year + 1900 << endl;
        cout << "Selected seats: ";
        for (const auto& seat : selectedSeats) {
            cout << seat << " ";
        }
    }

    void getUserInfo() {
        cout << "\nEnter your name: ";
        cin >> name;
        cout << "\nEnter your phone number: ";
        cin >> phoneNumber;
        std::regex indianPhoneNumberPattern("^[789]\\d{9}$"); //regex that checks whether the entered phone number
        //is a valid phone number or not.

        if (!std::regex_match(phoneNumber, indianPhoneNumberPattern)) {
            cout << "Invalid phone number. Program will terminate." << endl;
            exit(1);
        }

        cout << "\nSelect a payment option:" << endl;
        cout << "1. Cash on site" << endl;
        cout << "2. UPI" << endl;
        cout << "3. Debit card" << endl;
        cin >> paymentOption;

        int paymentOptionInt = std::stoi(paymentOption); //converting string to int

        if (paymentOptionInt < 1 || paymentOptionInt > 3) { //checking if the payment method is valid
            cout << "Payment failed: Invalid payment option selected." << endl;
            exit(1);
        }
    }   

    void storeUserInfo() {
        ofstream userInfoFile("ticket.txt");
        if (!userInfoFile.is_open()) {
            cout << "Error opening ticket.txt file" << endl;
            return;
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
        struct tm *ltm;
        ltm = localtime(&selectedDate);
        ltm = localtime(&selectedDate);
        userInfoFile << "Selected Date: " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year + 1900 << endl;
        userInfoFile << "Selected Seats: ";
        for (const auto& seat : selectedSeats) {
            userInfoFile << seat << " ";
        }
        userInfoFile.close(); //printing everything to the ticket.txt file
        printf("\nYour ticket has been booked. Please check ticket.txt for more details.\n");
    }
};

int main() {
    BookingSystem bookingSystem; //creating an object of the class BookingSystem
    bookingSystem.run(); //calling the run function
    return 0; 
}