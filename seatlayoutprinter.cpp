#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int RECLINER_ROWS = 1;
const int RECLINER_SEATS_PER_ROW = 8;
const int EXECUTIVE_ROWS = 4;
const int EXECUTIVE_SEATS_PER_ROW = 8;
const int PLATINUM_ROWS = 7;
const int PLATINUM_SEATS_PER_ROW = 10;
const int REGULAR_ROWS = 5;
const int REGULAR_SEATS_PER_ROW = 11;

const string SEATS_FILE = "seats.csv";

void printSeatingLayout(char seatingLayout[][REGULAR_SEATS_PER_ROW]) {
    cout << "Seating Layout:" << endl;
    for (int i = 0; i < RECLINER_ROWS; i++) { //iterating over the number of rows
        printf("\t\t"); //spacing between seats
        for (int j = 0; j < RECLINER_SEATS_PER_ROW; j++) { //iterating over each seat in a row
            cout << setw(4) << "[" << (char)('A' + i) << j+1 << "]"; //printing an identifier for each seat X1
            if (seatingLayout[i][j] == 'X') { 
                cout << "[X]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < EXECUTIVE_ROWS; i++) {
        printf("\t\t");
        for (int j = 0; j < EXECUTIVE_SEATS_PER_ROW; j++) {
            cout << setw(4) << "[" << (char)('C' + i) << j+1 << "]";
            if (seatingLayout[RECLINER_ROWS+i][j] == 'X') {
                cout << "[X]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < PLATINUM_ROWS; i++) {
        printf("    ");
        for (int j = 0; j < PLATINUM_SEATS_PER_ROW; j++) {
            cout << setw(4) << "[" << (char)('E' + i) << j+1 << "]";
            if (seatingLayout[RECLINER_ROWS+EXECUTIVE_ROWS+i][j] == 'X') {
                cout << "[X]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < REGULAR_ROWS; i++) {
        for (int j = 0; j < REGULAR_SEATS_PER_ROW; j++) {
            cout << setw(4) << "[" << (char)('G' + i) << j+1 << "]";
            if (seatingLayout[RECLINER_ROWS+EXECUTIVE_ROWS+PLATINUM_ROWS+i][j] == 'X') {
                cout << "[X]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
}

int seatprinter() {
    char seatingLayout[RECLINER_ROWS+EXECUTIVE_ROWS+PLATINUM_ROWS+REGULAR_ROWS][REGULAR_SEATS_PER_ROW];
    //a two dimensional array
    for (int i = 0; i < RECLINER_ROWS; i++) {
        for (int j = 0; j < RECLINER_SEATS_PER_ROW; j++) {
            seatingLayout[i][j] = ' ';
        }
    }
    for (int i = 0; i < EXECUTIVE_ROWS; i++) {
        for (int j = 0; j < EXECUTIVE_SEATS_PER_ROW; j++) {
            seatingLayout[RECLINER_ROWS+i][j] = ' ';
        }
    }
    for (int i = 0; i < PLATINUM_ROWS; i++) {
        for (int j = 0; j < PLATINUM_SEATS_PER_ROW; j++) {
            seatingLayout[RECLINER_ROWS+EXECUTIVE_ROWS+i][j] = ' ';
        }
    }
    for (int i = 0; i < REGULAR_ROWS; i++) {
        for (int j = 0; j < REGULAR_SEATS_PER_ROW; j++) {
            seatingLayout[RECLINER_ROWS+EXECUTIVE_ROWS+PLATINUM_ROWS+i][j] = ' ';
        }
    }

    srand(time(NULL)); // seed the random number generator with the current time

    int totalSeats = RECLINER_ROWS*RECLINER_SEATS_PER_ROW + EXECUTIVE_ROWS*EXECUTIVE_SEATS_PER_ROW + PLATINUM_ROWS*PLATINUM_SEATS_PER_ROW + REGULAR_ROWS*REGULAR_SEATS_PER_ROW;
    int numFilledSeats = totalSeats * (rand() % 21 + 40) / 100; // randomly fill the theatre by about 40 to 60%
    for (int i = 0; i < numFilledSeats; i++) {
        int row = rand() % (RECLINER_ROWS+EXECUTIVE_ROWS+PLATINUM_ROWS+REGULAR_ROWS);
        int seatNum = rand() % REGULAR_SEATS_PER_ROW;
        if (seatingLayout[row][seatNum] == ' ') {
            seatingLayout[row][seatNum] = 'X';
        } else {
            i--;
        }
    }

    printSeatingLayout(seatingLayout);
    printf("\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                 SCREEN HERE                                                       ");
    return 0;
}
