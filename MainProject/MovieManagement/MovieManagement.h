#pragma once
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

struct MOVIEINFO{
    string name;
    string languages;   
    string releaseDate;
    string streamingUntil;

    MOVIEINFO* prev;
    MOVIEINFO* next;
};

void freeList();

void addNote(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil);

void display();

void deleteNode(MOVIEINFO* current);

void upcomingMovies();

void sortByName();

void sortByReleaseDate();

void interactiveView(); // This is declared in ScheduleProgrammeHeader.h to avoid circular dependency

void swapData(MOVIEINFO* a, MOVIEINFO* b);

MOVIEINFO* createNode(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil);

bool isCurrentlyStreaming(MOVIEINFO * m, const string & currentDate);

void updateNode(MOVIEINFO * node);

string getCurrentDate();

