#include <iostream>
#include "RelatedNewsHeader.h"
#include "ScheduleProgrammeHeader.h"
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"

using namespace std;

int main() {
    addNote("Inception", "English", "2010-07-16", "2026-12-31");
    addNote("Avatar", "English", "2009-12-18", "2026-05-01");
    addNote("Dune", "English", "2021-10-22", "2027-01-01");

    cout << "Choose order:\n";
    cout << "1. Alphabetical\n2. Release Date\n";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) sortByName();
    else sortByReleaseDate();

    interactiveView();

    freeList();
}


//int main()
//{
//    
//    int choice;
//    cin >> choice;
//
//    cout << "1-News" << endl << "2-Schedule" << endl << "3-Up and Coming" << "anything else - end"; //the whole menu is a placeholder to establish a connection between the files
//
//        switch (choice) { //placeholder
//
//        case 1:
//            RelatedNewsF();
//            break;
//        case 2:
//            ScheduleProgrammeF();
//            break;
//        case 3:
//            UpcomingMoviesF();
//            break;
//        default:
//            return 0;
//
//        }
//
//}
