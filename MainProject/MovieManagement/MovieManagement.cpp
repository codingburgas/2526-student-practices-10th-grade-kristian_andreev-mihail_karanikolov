#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include "MovieManagement.h"   
#include "raylib.h"
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;


// ================= GLOBAL POINTERS =================
MOVIEINFO* head = nullptr;
MOVIEINFO* tail = nullptr;

// ================= CORE METHODS =================
MOVIEINFO* createNode(const string& name, const string& languages, const string& releaseDate, const string& streamingUntil) {
    return new MOVIEINFO{ name, languages, releaseDate, streamingUntil, nullptr, nullptr };
}


void addNote(const string& name,
    const string& languages,
    const string& releaseDate,
    const string& streamingUntil) {

    MOVIEINFO* n = createNode(name, languages, releaseDate, streamingUntil);

    if (!head) {
        head = tail = n;
    }
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }

    saveMoviesToFile();
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

    cout << "New name: ";
    getline(cin, node->name);

    cout << "New languages: ";
    getline(cin, node->languages);

    cout << "New release date: ";
    getline(cin, node->releaseDate);

    cout << "New streaming until: ";
    getline(cin, node->streamingUntil);

    rewriteMoviesFile();
}

void deleteNode(MOVIEINFO* current) {

    if (!current) return;

    if (current == head) {

        head = current->next;

        if (head)
            head->prev = nullptr;
    }

    else if (current == tail) {

        tail = current->prev;

        if (tail)
            tail->next = nullptr;
    }

    else {

        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;

    rewriteMoviesFile();
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



MOVIEINFO* findMovieByName(const string& name) {

    MOVIEINFO* temp = head;

    while (temp) {

        if (temp->name == name) {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr;
}

void movieMenu() {

    int choice;

    do {

        cout << "\n===== MOVIE MANAGEMENT =====\n";
        cout << "1. Add Movie\n";
        cout << "2. Display Movies\n";
        cout << "3. Edit Movie\n";
        cout << "4. Delete Movie\n";
        cout << "5. Sort By Name\n";
        cout << "6. Sort By Release Date\n";
        cout << "7. Reserve Seats\n";
        cout << "0. Exit\n";

        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {

            string name, lang, release, until;

            cout << "Movie Name: ";
            getline(cin, name);

            cout << "Languages: ";
            getline(cin, lang);

            cout << "Release Date (YYYY-MM-DD): ";
            getline(cin, release);

            cout << "Streaming Until (YYYY-MM-DD): ";
            getline(cin, until);

            addNote(name, lang, release, until);

            cout << "Movie added successfully!\n";
        }

        else if (choice == 2) {

            display();
        }

        else if (choice == 3) {

            string name;

            cout << "Enter movie name to edit: ";
            getline(cin, name);

            MOVIEINFO* movie = findMovieByName(name);

            if (movie) {
                updateNode(movie);
                cout << "Movie updated!\n";
            }
            else {
                cout << "Movie not found!\n";
            }
        }

        else if (choice == 4) {

            string name;

            cout << "Enter movie name to delete: ";
            getline(cin, name);

            MOVIEINFO* movie = findMovieByName(name);

            if (movie) {
                deleteNode(movie);
                cout << "Movie deleted!\n";
            }
            else {
                cout << "Movie not found!\n";
            }
        }

        else if (choice == 5) {

            sortByName();
            cout << "Sorted alphabetically!\n";
        }

        else if (choice == 6) {

            sortByReleaseDate();
            cout << "Sorted by release date!\n";
        }

        else if (choice == 7) {

            reserveMovieSeats();
        }

    } while (choice != 0);
}







void reserveMovieSeats() {

    cout << "\n===== AVAILABLE MOVIES =====\n";

    display();

    string movieName;

    cout << "\nChoose movie: ";
    getline(cin, movieName);

    MOVIEINFO* movie = findMovieByName(movieName);

    if (!movie) {

        cout << "Movie not found!\n";
        return;
    }

    cout << "Opening reservation for: " << movie->name << endl;

    TheatreSeatReservationFunc();
}

void saveMoviesToFile() {

    ofstream file("movies.txt", ios::app);

    if (!file.is_open()) {
        cout << "Failed to open file!\n";
        return;
    }

    MOVIEINFO* temp = tail;

    if (temp) {

        file << temp->name << "|"
            << temp->languages << "|"
            << temp->releaseDate << "|"
            << temp->streamingUntil << "\n";
    }

    file.close();
}





void rewriteMoviesFile() {

    ofstream file("movies.txt");

    if (!file.is_open()) {
        cout << "Failed to rewrite file!\n";
        return;
    }

    MOVIEINFO* temp = head;

    while (temp) {

        file << temp->name << "|"
            << temp->languages << "|"
            << temp->releaseDate << "|"
            << temp->streamingUntil << "\n";

        temp = temp->next;
    }

    file.close();
}

void addMovieWithoutSaving(const string& name,
    const string& languages,
    const string& releaseDate,
    const string& streamingUntil) {

    MOVIEINFO* n = createNode(name, languages, releaseDate, streamingUntil);

    if (!head) {    
        head = tail = n;
    }
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

void loadMoviesFromFile() {

    ifstream file("movies.txt");

    if (!file.is_open()) {
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        string name;
        string language;
        string release;
        string until;

        getline(ss, name, '|');
        getline(ss, language, '|');
        getline(ss, release, '|');
        getline(ss, until, '|');

        addMovieWithoutSaving(name, language, release, until);
    }

    file.close();
}