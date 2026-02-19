#include <iostream>
#include "RelatedNewsHeader.h"
#include "ScheduleProgrammeHeader.h"
#include "UpcomingMoviesHeader.h"
#include "MainHeader.h"

using namespace std;

int main()
{
    
    int choice;
    cin >> choice;

    cout << "1-News" << endl << "2-Schedule" << endl << "3-Up and Coming" << "anything else - end"; //the whole menu is a placeholder to establish a connection between the files

        switch (choice) { //placeholder

        case 1:
            RelatedNewsF();
            break;
        case 2:
            ScheduleProgrammeF();
            break;
        case 3:
            UpcomingMoviesF();
            break;
        default:
            return 0;

        }

}
