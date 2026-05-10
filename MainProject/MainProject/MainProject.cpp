#include <iostream>
#include "RelatedNewsHeader.h"
#include "ScheduleProgrammeHeader.h"
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"
#include "TheatreSeatsReservationHeader.h"


using namespace std;

int main() {

    loadMoviesFromFile();

    movieMenu();

    freeList();

    return 0;
}