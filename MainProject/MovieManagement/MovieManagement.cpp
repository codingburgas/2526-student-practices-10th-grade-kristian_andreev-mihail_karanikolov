#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include "MovieManagement.h"   
#include "raylib.h"


using namespace std;


// ================= GLOBAL POINTERS =================
MOVIEINFO* head = nullptr;
MOVIEINFO* tail = nullptr;

// ================= CORE METHODS =================
MOVIEINFO* createNode(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil) {
    return new MOVIEINFO{ name, languages, releaseDate, streamingUntil, nullptr, nullptr };
}


void addNote(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil) {
    MOVIEINFO* n = createNode(name, languages, releaseDate, streamingUntil);

    if (!head) head = tail = n;
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

// ================= DISPLAY =================
void display() {
    MOVIEINFO* temp = head;
    while (temp) {
        cout << "Name: " << temp->name
            << " | Languages: " << temp->languages
            << " | Release: " << temp->releaseDate
            << " | Until: " << temp->streamingUntil << "\n";
        temp = temp->next;
    }
}

// ================= SORTING =================
void swapData(MOVIEINFO* a, MOVIEINFO* b) {
    swap(a->name, b->name);
    swap(a->languages, b->languages);
    swap(a->releaseDate, b->releaseDate);
    swap(a->streamingUntil, b->streamingUntil);
}

void sortByName() {
    for (MOVIEINFO* i = head; i; i = i->next)
        for (MOVIEINFO* j = i->next; j; j = j->next)
            if (i->name > j->name)
                swapData(i, j);
}

void sortByReleaseDate() {
    for (MOVIEINFO* i = head; i; i = i->next)
        for (MOVIEINFO* j = i->next; j; j = j->next)
            if (i->releaseDate > j->releaseDate)
                swapData(i, j);
}

// ================= TIME =================
string getCurrentDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    char buf[11];
    sprintf_s(buf, sizeof(buf), "%04d-%02d-%02d", 1900 + ltm.tm_year, 1 + ltm.tm_mon, ltm.tm_mday);
    return string(buf);
}

bool isCurrentlyStreaming(MOVIEINFO* m, const string& currentDate) {
    return (m->releaseDate <= currentDate && m->streamingUntil >= currentDate);
}

void upcomingMovies() {
    string currentDate = getCurrentDate();

    cout << "Upcoming Movies:\n";
    MOVIEINFO* temp = head;

    while (temp) {
        if (temp->releaseDate > currentDate) {
            cout << temp->name << " | " << temp->releaseDate << endl;
        }
        temp = temp->next;
    }
}

void currentlyStreaming() {
    string currentDate = getCurrentDate();

    cout << "Currently Streaming:\n";
    MOVIEINFO* temp = head;

    while (temp) {
        if (isCurrentlyStreaming(temp, currentDate)) {
            cout << temp->name << endl;
        }
        temp = temp->next;
    }
}

// ================= MODIFY / DELETE =================
void updateNode(MOVIEINFO* node) {
    if (!node) return;

    cout << "New name: "; getline(cin, node->name);
    cout << "New languages: "; getline(cin, node->languages);
    cout << "New release date: "; getline(cin, node->releaseDate);
    cout << "New streaming until: "; getline(cin, node->streamingUntil);
}

void deleteNode(MOVIEINFO* current) {
    if (!current) return;

    if (current == head) {
        head = current->next;
        if (head) head->prev = nullptr;
    }
    else if (current == tail) {
        tail = current->prev;
        if (tail) tail->next = nullptr;
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
}

// ================= INTERACTIVE =================
void interactiveView() {
    MOVIEINFO* temp = head;

    while (temp) {
        cout << "\n----------------------\n";
        cout << "Name: " << temp->name << endl;
        cout << "Languages: " << temp->languages << endl;
        cout << "Release: " << temp->releaseDate << endl;
        cout << "Streaming Until: " << temp->streamingUntil << endl;

        cout << "[1] Next  [2] Delete  [3] Modify  [0] Exit\n";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) temp = temp->next;
        else if (choice == 2) {
            MOVIEINFO* toDelete = temp;
            temp = temp->next;
            deleteNode(toDelete);
        }
        else if (choice == 3) updateNode(temp);
        else break;
    }
}

// ================= CLEANUP =================
void freeList() {
    MOVIEINFO* cur = head;
    while (cur) {
        MOVIEINFO* t = cur;
        cur = cur->next;
        delete t;
    }
}


//========SAVE============
void SaveMovieData() {



}
