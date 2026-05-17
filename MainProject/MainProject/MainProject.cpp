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

    string user, pass;

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