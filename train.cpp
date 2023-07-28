#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// Constants for the number of trains and seats
const int NUM_TRAINS = 3;
const int NUM_SEATS = 60;

// Structure to store train details
struct Train {
    string trainName;
    string source;
    string destination;
    int seats[NUM_SEATS];
};

// Function prototypes
void displayMenu();
void registerUser();
bool loginUser();
void bookTicket();
void displayTicket();
void editBooking();
void deleteTicket();

// Global variables
vector<Train> trains;
string currentUser;
string cname;

int main() {
    // Fabricated details for 3 trains
    trains.push_back({"Rajdhani Express", "Delhi", "Mumbai"});
    trains.push_back({"Garib Rath Express", "Chennai", "Kolkata"});
    trains.push_back({"Deccan Odyssey", "Bangalore", "Hyderabad"});

    int choice;
    bool loggedIn = false;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                if (!loggedIn) {
                    registerUser();
                } else {
                    cout << "You are already logged in!\n";
                }
                break;
            case 2:
                if (!loggedIn) {
                    loggedIn = loginUser();
                } else {
                    cout << "You are already logged in!\n";
                }
                break;
            case 3:
                if (loggedIn) {
                    bookTicket();
                } else {
                    cout << "Please login first!\n";
                }
                break;
            case 4:
                if (loggedIn) {
                    displayTicket();
                } else {
                    cout << "Please login first!\n";
                }
                break;
            case 5:
                if (loggedIn) {
                    editBooking();
                } else {
                    cout << "Please login first!\n";
                }
                break;
            case 6:
                if (loggedIn) {
                    deleteTicket();
                } else {
                    cout << "Please login first!\n";
                }
                break;
            case 7:
                cout << "Thank you for using the ticket booking system. Goodbye!\n";
                exit(0);
            case 8:
                if (loggedIn) {
                    currentUser = "";
                    loggedIn = false;
                    cout << "Logout successful!\n";
                } else {
                    cout << "You are not logged in!\n";
                }
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

void displayMenu() {
    cout << "======================\n";
    cout << "  Train Ticket System  \n";
    cout << "======================\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Book Ticket\n";
    cout << "4. Display Ticket\n";
    cout << "5. Edit Booking\n";
    cout << "6. Delete Ticket\n";
    cout << "7. Exit\n";
    cout << "8. Logout\n";
    cout << "Enter your choice: ";
}

void registerUser() {
    string username, password, name;
    cout << "Enter your desired username: ";
    getline(cin, username);
    cout << "Enter your desired password: ";
    getline(cin, password);
    cout << "Enter your name: ";
    getline(cin, name);

    // Save the user registration details to a file
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << username << " " << password << " " << name << endl;
        userFile.close();
        cout << "Registration successful! You can now login.\n";
    } else {
        cout << "Error: Unable to open file for user registration.\n";
    }
}

bool loginUser() {
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);

    // Check if the user exists in the registration file
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        string user, pass, nam;
        while (userFile >> user >> pass >> nam) {
            if (user == username && pass == password) {
                cname = nam;
                currentUser = username;
                cout << "Login successful!\n";
                return true;
            }
        }
        cout << "Invalid username or password. Please try again.\n";
        userFile.close();
    } else {
        cout << "Error: Unable to open file for user login.\n";
    }

    return false;
}

void bookTicket() {
    int trainIndex, seatNumber;
    cout << "Available trains:\n";
    for (int i = 0; i < NUM_TRAINS; i++) {
        cout << i + 1 << ". " << trains[i].trainName << " (" << trains[i].source << " to " << trains[i].destination << ")\n";
    }
    cout << "Select the train (1-" << NUM_TRAINS << "): ";
    cin >> trainIndex;
    trainIndex--;

    if (trainIndex < 0 || trainIndex >= NUM_TRAINS) {
        cout << "Invalid train selection.\n";
        return;
    }

    cout << "Available seats: ";
    cout << "\n-----------Select the Seat Number-----------\n";
    cout<<"\t           -:SEAT MATRIX:-        \n";
    cout<<"\t(U)    (M)        (L)    (L)    "
           "    (U)\n\n";
    cout<<"\t01    02        03\t04        "
           "05\n\n";
    cout<<"\t06    07        08\t09        "
           "10\n";
    cout<<"\t11    12        13\t14        "
           "15\n\n";
    cout<<"\t16    17        18\t19        "
           "20\n";
    cout<<"\t21    22        23\t24        "
           "25\n\n";
    cout<<"\t26    27        28\t29        "
           "30\n";
    cout<<"\t31    32        33\t34        "
           "35\n\n";
    cout<<"\t36    37        38\t39        "
           "40\n";
    cout<<"\t41    42        43\t44        "
           "45\n\n";
    cout<<"\t46    47        48\t49        "
           "50\n";
    cout<<"\t51    52        53\t54        "
           "55\n\n";
    cout<<"\t56    57        58\t59        "
           "60\n";
    cout << "\nSelect the seat (1-" << NUM_SEATS << "): ";
    cin >> seatNumber;
    seatNumber--;

    if (seatNumber < 0 || seatNumber >= NUM_SEATS || trains[trainIndex].seats[seatNumber] != 0) {
        cout << "Invalid seat selection or seat already booked.\n";
        return;
    }

    // Book the seat
    trains[trainIndex].seats[seatNumber] = 1;

    // Save the booking details to a file
    ofstream bookingFile(currentUser + ".txt", ios::app);
    if (bookingFile.is_open()) {
        bookingFile << "Passenger Name: "<< cname << " | " << trains[trainIndex].trainName << " | " << trains[trainIndex].source << " to " << trains[trainIndex].destination << " | " << "Seat Number: " << seatNumber + 1 << endl;
        bookingFile.close();
        cout << "Ticket booked successfully!\n";
    } else {
        cout << "Error: Unable to open file for booking.\n";
    }
}

void displayTicket() {
    string line;
    ifstream bookingFile(currentUser + ".txt");
    if (bookingFile.is_open()) {
        while (getline(bookingFile, line)) {
            cout << line << endl;
        }
        bookingFile.close();
    } else {
        cout << "No bookings found for this user.\n";
    }
}

void editBooking() {
    int ticketCount = 0;
    vector<string> tickets;

    // Read and store all existing booking details for the current user
    string line;
    ifstream bookingFile(currentUser + ".txt");
    if (bookingFile.is_open()) {
        while (getline(bookingFile, line)) {
            ticketCount++;
            tickets.push_back(line);
        }
        bookingFile.close();
    } else {
        cout << "No bookings found for this user.\n";
        return;
    }

    // Display existing tickets and prompt for selection
    cout << "Your booked tickets:\n";
    for (int i = 0; i < ticketCount; i++) {
        cout << i + 1 << ". " << tickets[i] << endl;
    }
    cout << "Select the ticket to edit (1-" << ticketCount << ") or enter 0 to cancel: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Edit canceled.\n";
        return;
    } else if (choice < 1 || choice > ticketCount) {
        cout << "Invalid ticket selection.\n";
        return;
    }

    // Ask for the new seat number
    int trainIndex = -1;
    int seatNumber;
    for (int i = 0; i < NUM_TRAINS; i++) {
        if (tickets[choice - 1].find(trains[i].trainName) != string::npos) {
            trainIndex = i;
            break;
        }
    }

    if (trainIndex == -1) {
        cout << "Invalid train information found in the ticket.\n";
        return;
    }

    cout << "Available seats: ";
    for (int i = 0; i < NUM_SEATS; i++) {
        if (trains[trainIndex].seats[i] == 0) {
            cout << i + 1 << " ";
        }
    }
    cout << "\nEnter the new seat number (1-" << NUM_SEATS << "): ";
    cin >> seatNumber;
    seatNumber--;

    if (seatNumber < 0 || seatNumber >= NUM_SEATS || trains[trainIndex].seats[seatNumber] != 0) {
        cout << "Invalid seat selection or seat already booked.\n";
        return;
    }

    // Update the booking details
    ofstream bookingFileUpdate(currentUser + ".txt");
    if (bookingFileUpdate.is_open()) {
        for (int i = 0; i < ticketCount; i++) {
            if (i == choice - 1) {
                bookingFileUpdate << "Passenger Name: "<< cname << " | " << trains[trainIndex].trainName << " | " << trains[trainIndex].source << " to " << trains[trainIndex].destination << " | " << "Seat Number: " << seatNumber + 1 << endl;
            } else {
                bookingFileUpdate << tickets[i] << endl;
            }
        }
        bookingFileUpdate.close();
        cout << "Ticket updated successfully!\n";
    } else {
        cout << "Error: Unable to open file for booking update.\n";
    }
}

void deleteTicket() {
    int ticketCount = 0;
    vector<string> tickets;

    // Read and store all existing booking details for the current user
    string line;
    ifstream bookingFile(currentUser + ".txt");
    if (bookingFile.is_open()) {
        while (getline(bookingFile, line)) {
            ticketCount++;
            tickets.push_back(line);
        }
        bookingFile.close();
    } else {
        cout << "No bookings found for this user.\n";
        return;
    }

    // Display existing tickets and prompt for selection
    cout << "Your booked tickets:\n";
    for (int i = 0; i < ticketCount; i++) {
        cout << i + 1 << ". " << tickets[i] << endl;
    }
    cout << "Select the ticket to delete (1-" << ticketCount << ") or enter 0 to cancel: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Deletion canceled.\n";
        return;
    } else if (choice < 1 || choice > ticketCount) {
        cout << "Invalid ticket selection.\n";
        return;
    }

    // Remove the selected ticket
    ofstream bookingFileUpdate(currentUser + ".txt");
    if (bookingFileUpdate.is_open()) {
        for (int i = 0; i < ticketCount; i++) {
            if (i != choice - 1) {
                bookingFileUpdate << tickets[i] << endl;
            }
        }
        bookingFileUpdate.close();
        cout << "Ticket deleted successfully!\n";
    } else {
        cout << "Error: Unable to open file for booking deletion.\n";
    }
}