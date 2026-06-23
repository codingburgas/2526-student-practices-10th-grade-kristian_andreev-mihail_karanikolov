#include <iostream>
#include "RelatedNewsHeader.h"
#include "ScheduleProgrammeHeader.h"
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"
#include "TheatreSeatsReservationHeader.h"
#include "..\MovieManagement\AccountManager.h"

using namespace std;

int main() {
    accManager.loadAccounts();

    int choice;

    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();

    string user, pass;

    if (choice == 2) {

        cout << "Choose Username: ";
        getline(cin, user);

        cout << "Choose Password: ";
        getline(cin, pass);

        accManager.registerAccount(user, pass);

        return 0; // restart program and login
    }

    cout << "Username: ";
    getline(cin, user);

    cout << "Password: ";
    getline(cin, pass);

    if (!accManager.login(user, pass)) {
        cout << "Invalid login!\n";
        return 0;
    }

    accManager.displayUserBanner();

    loadMoviesFromFile();
    movieMenu();
    freeList();

    return 0;
}