#pragma once
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

struct NODE {
    string name;
    string languages;   
    string releaseDate;
    string streamingUntil;

    NODE* prev;
    NODE* next;
};

void freeList();

void addNote(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil);

void display();

void deleteNode(NODE* current);

void upcomingMovies();

void sortByName();

void sortByReleaseDate();

void interactiveView(); // This is declared in ScheduleProgrammeHeader.h to avoid circular dependency

void swapData(NODE* a, NODE* b);

NODE* createNode(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil);

bool isCurrentlyStreaming(NODE * m, const string & currentDate);

void updateNode(NODE * node);

string getCurrentDate();

