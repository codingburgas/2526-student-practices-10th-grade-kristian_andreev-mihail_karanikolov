#include <iostream>
#include "RelatedNewsHeader.h"
#include "ScheduleProgrammeHeader.h"
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"
#include "TheatreSeatsReservationHeader.h"


using namespace std;

int main() {
    addNote("Inception", "English", "2010-07-16", "2026-12-31");
    addNote("Avatar", "English", "2009-12-18", "2026-05-01");
    addNote("Dune", "English", "2021-10-22", "2027-01-01");

    cout << "Choose order:\n";
    cout << "1. Alphabetical\n2. Release Date\n3.Seat Reservation";

    int choice;
    cin >> choice;
    cin.ignore();

    switch(choice){
    case 1:
        sortByName();
        interactiveView();

        freeList();
        break;

    case 2:
        sortByReleaseDate();
        interactiveView();

        freeList();
        break;

    case 3:
        TheatreSeatReservationFunc();
        break;
    
    }

    

    
}

