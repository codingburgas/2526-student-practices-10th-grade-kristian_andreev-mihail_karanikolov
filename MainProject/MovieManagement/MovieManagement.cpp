#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include "MovieManagement.h"   
#include "AccountManager.h"
#include "raylib.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "raylib.h"


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
    
    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        Rectangle backButton =
        {
            20.0f,
            120.0f,
            150.0f,
            50.0f
        };

        bool backHover =
            CheckCollisionPointRec(
                mouse,
                backButton
            );

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Blue ribbon
        DrawRectangle(
            0,
            0,
            1280,
            100,
            BLUE
        );

        DrawText(
            "Cinesity",
            1280 / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );

        DrawText(
            "Movies",
            570,
            130,
            35,
            BLACK
        );

        // Back button
        DrawRectangleRec(
            backButton,
            backHover ? DARKGRAY : GRAY
        );

        DrawText(
            "Back",
            65,
            135,
            25,
            WHITE
        );

        MOVIEINFO* temp = head;

        int y = 200;

        while (temp)
        {
            DrawRectangle(
                250,
                y,
                780,
                70,
                LIGHTGRAY
            );

            DrawText(
                ("Name: " + temp->name).c_str(),
                270,
                y + 10,
                20,
                BLACK
            );

            DrawText(
                ("Languages: " + temp->languages).c_str(),
                270,
                y + 35,
                20,
                BLACK
            );

            DrawText(
                ("Release: " + temp->releaseDate).c_str(),
                650,
                y + 10,
                20,
                BLACK
            );

            DrawText(
                ("Until: " + temp->streamingUntil).c_str(),
                650,
                y + 35,
                20,
                BLACK
            );

            y += 90;

            temp = temp->next;
        }

        EndDrawing();

        if (backHover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return;
        }
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

//  MODIFY / DELETE 
void updateNode(MOVIEINFO* node) {

    if (!node)
        return;


    string newName = node->name;
    string newLanguages = node->languages;
    string newRelease = node->releaseDate;
    string newUntil = node->streamingUntil;


    bool typingName = true;
    bool typingLanguages = false;
    bool typingRelease = false;
    bool typingUntil = false;


    Rectangle saveButton =
    {
        490.0f,
        600.0f,
        300.0f,
        60.0f
    };


    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();


        bool saveHover =
            CheckCollisionPointRec(
                mouse,
                saveButton
            );


        int key = GetCharPressed();



        // ================= NAME =================

        if (typingName)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    newName += (char)key;

                key = GetCharPressed();
            }


            if (IsKeyPressed(KEY_BACKSPACE) &&
                newName.length() > 0)
            {
                newName.pop_back();
            }


            if (IsKeyPressed(KEY_ENTER))
            {
                typingName = false;
                typingLanguages = true;
            }
        }



        // ================= LANGUAGES =================

        else if (typingLanguages)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    newLanguages += (char)key;

                key = GetCharPressed();
            }


            if (IsKeyPressed(KEY_BACKSPACE) &&
                newLanguages.length() > 0)
            {
                newLanguages.pop_back();
            }


            if (IsKeyPressed(KEY_ENTER))
            {
                typingLanguages = false;
                typingRelease = true;
            }
        }




        // ================= RELEASE =================

        else if (typingRelease)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    newRelease += (char)key;

                key = GetCharPressed();
            }


            if (IsKeyPressed(KEY_BACKSPACE) &&
                newRelease.length() > 0)
            {
                newRelease.pop_back();
            }


            if (IsKeyPressed(KEY_ENTER))
            {
                typingRelease = false;
                typingUntil = true;
            }
        }




        // ================= UNTIL =================

        else if (typingUntil)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    newUntil += (char)key;

                key = GetCharPressed();
            }


            if (IsKeyPressed(KEY_BACKSPACE) &&
                newUntil.length() > 0)
            {
                newUntil.pop_back();
            }
        }





        BeginDrawing();


        ClearBackground(RAYWHITE);



        // ribbon

        DrawRectangle(
            0,
            0,
            1280,
            100,
            BLUE
        );


        DrawText(
            "Cinesity",
            1280 / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );




        // panel

        DrawRectangle(
            300,
            150,
            680,
            550,
            LIGHTGRAY
        );



        DrawText(
            "Edit Movie",
            520,
            180,
            35,
            BLACK
        );



        // Name

        DrawText(
            "Movie Name",
            380,
            240,
            20,
            DARKGRAY
        );


        DrawRectangle(
            380,
            270,
            500,
            45,
            WHITE
        );


        DrawText(
            newName.c_str(),
            390,
            280,
            20,
            BLACK
        );





        // Languages

        DrawText(
            "Languages",
            380,
            330,
            20,
            DARKGRAY
        );


        DrawRectangle(
            380,
            360,
            500,
            45,
            WHITE
        );


        DrawText(
            newLanguages.c_str(),
            390,
            370,
            20,
            BLACK
        );





        // Release

        DrawText(
            "Release Date",
            380,
            420,
            20,
            DARKGRAY
        );


        DrawRectangle(
            380,
            450,
            500,
            45,
            WHITE
        );


        DrawText(
            newRelease.c_str(),
            390,
            460,
            20,
            BLACK
        );





        // Until

        DrawText(
            "Streaming Until",
            380,
            510,
            20,
            DARKGRAY
        );


        DrawRectangle(
            380,
            540,
            500,
            45,
            WHITE
        );


        DrawText(
            newUntil.c_str(),
            390,
            550,
            20,
            BLACK
        );




        // save button

        DrawRectangleRec(
            saveButton,
            saveHover ? DARKGRAY : GRAY
        );


        DrawText(
            "SAVE",
            saveButton.x +
            (saveButton.width -
                MeasureText("SAVE", 25)) / 2,
            saveButton.y + 18,
            25,
            WHITE
        );



        EndDrawing();





        if (saveHover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            node->name = newName;
            node->languages = newLanguages;
            node->releaseDate = newRelease;
            node->streamingUntil = newUntil;


            rewriteMoviesFile();


            return;
        }
    }

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


void AddMovie(int choice){

    string name = "";
    string lang = "";
    string release = "";
    string until = "";

    bool typingName = true;
    bool typingLang = false;
    bool typingRelease = false;
    bool typingUntil = false;

    Rectangle addButton =
    {
        490.0f,
        560.0f,
        300.0f,
        60.0f
    };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        bool addHover =
            CheckCollisionPointRec(
                mouse,
                addButton
            );

        int key = GetCharPressed();

        if (typingName)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    name += (char)key;

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) &&
                !name.empty())
            {
                name.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                typingName = false;
                typingLang = true;
            }
        }

        else if (typingLang)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    lang += (char)key;

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) &&
                !lang.empty())
            {
                lang.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                typingLang = false;
                typingRelease = true;
            }
        }

        else if (typingRelease)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    release += (char)key;

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) &&
                !release.empty())
            {
                release.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                typingRelease = false;
                typingUntil = true;
            }
        }

        else if (typingUntil)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    until += (char)key;

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) &&
                !until.empty())
            {
                until.pop_back();
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(
            0,
            0,
            1280,
            100,
            BLUE
        );

        DrawText(
            "Cinesity",
            1280 / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );

        DrawRectangle(
            300,
            150,
            680,
            500,
            LIGHTGRAY
        );

        DrawText(
            "Add Movie",
            540,
            180,
            35,
            BLACK
        );

        // Movie name
        DrawText(
            "Movie Name",
            380,
            240,
            20,
            DARKGRAY
        );

        DrawRectangle(
            380,
            270,
            500,
            45,
            WHITE
        );

        DrawText(
            name.c_str(),
            390,
            280,
            20,
            BLACK
        );

        // Languages
        DrawText(
            "Languages",
            380,
            330,
            20,
            DARKGRAY
        );

        DrawRectangle(
            380,
            360,
            500,
            45,
            WHITE
        );

        DrawText(
            lang.c_str(),
            390,
            370,
            20,
            BLACK
        );

        // Release Date
        DrawText(
            "Release Date",
            380,
            420,
            20,
            DARKGRAY
        );

        DrawRectangle(
            380,
            450,
            500,
            45,
            WHITE
        );

        DrawText(
            release.c_str(),
            390,
            460,
            20,
            BLACK
        );

        // Streaming Until
        DrawText(
            "Streaming Until",
            380,
            510,
            20,
            DARKGRAY
        );

        DrawRectangle(
            380,
            540,
            500,
            45,
            WHITE
        );

        DrawText(
            until.c_str(),
            390,
            550,
            20,
            BLACK
        );

        DrawRectangleRec(
            addButton,
            addHover ? DARKGRAY : GRAY
        );

        DrawText(
            "ADD MOVIE",
            addButton.x +
            (addButton.width -
                MeasureText("ADD MOVIE", 25)) / 2,
            addButton.y + 18,
            25,
            WHITE
        );

        EndDrawing();

        if (addHover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            addNote(
                name,
                lang,
                release,
                until
            );

            return;
        }
    }

}


void EditMovie(int choice) {

    string name = "";

    Rectangle findButton =
    {
        490,
        430,
        300,
        60
    };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        bool findHover =
            CheckCollisionPointRec(mouse, findButton);

        int key = GetCharPressed();

        while (key > 0)
        {
            if (key >= 32 && key <= 125)
                name += (char)key;

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) &&
            name.length() > 0)
        {
            name.pop_back();
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, 1280, 100, BLUE);

        DrawText(
            "Cinesity",
            1280 / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );

        DrawRectangle(
            340,
            180,
            600,
            300,
            LIGHTGRAY
        );

        DrawText(
            "Edit Movie",
            540,
            220,
            35,
            BLACK
        );

        DrawText(
            "Movie Name",
            440,
            280,
            20,
            DARKGRAY
        );

        DrawRectangle(
            440,
            310,
            400,
            50,
            WHITE
        );

        DrawText(
            name.c_str(),
            450,
            325,
            25,
            BLACK
        );

        DrawRectangleRec(
            findButton,
            findHover ? DARKGRAY : GRAY
        );

        DrawText(
            "FIND MOVIE",
            findButton.x +
            (findButton.width -
                MeasureText("FIND MOVIE", 25)) / 2,
            findButton.y + 18,
            25,
            WHITE
        );

        EndDrawing();

        if (findHover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            MOVIEINFO* movie =
                findMovieByName(name);

            if (movie)
            {
                updateNode(movie);
                return;
            }
        }
    }

}

void DeleteMovie(int choice) {

    string name = "";

    Rectangle deleteButton =
    {
        490.0f,
        430.0f,
        300.0f,
        60.0f
    };


    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();


        bool deleteHover =
            CheckCollisionPointRec(
                mouse,
                deleteButton
            );


        int key = GetCharPressed();



        while (key > 0)
        {
            if (key >= 32 && key <= 125)
                name += (char)key;

            key = GetCharPressed();
        }



        if (IsKeyPressed(KEY_BACKSPACE) &&
            name.length() > 0)
        {
            name.pop_back();
        }





        BeginDrawing();


        ClearBackground(RAYWHITE);



        // top ribbon

        DrawRectangle(
            0,
            0,
            1280,
            100,
            BLUE
        );


        DrawText(
            "Cinesity",
            1280 / 2 -
            MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );



        // panel

        DrawRectangle(
            340,
            180,
            600,
            300,
            LIGHTGRAY
        );



        DrawText(
            "Delete Movie",
            510,
            220,
            35,
            BLACK
        );



        DrawText(
            "Movie Name",
            440,
            280,
            20,
            DARKGRAY
        );



        DrawRectangle(
            440,
            310,
            400,
            50,
            WHITE
        );


        DrawText(
            name.c_str(),
            450,
            325,
            25,
            BLACK
        );




        DrawRectangleRec(
            deleteButton,
            deleteHover ? DARKGRAY : GRAY
        );


        DrawText(
            "DELETE",
            deleteButton.x +
            (deleteButton.width -
                MeasureText("DELETE", 25)) / 2,
            deleteButton.y + 18,
            25,
            WHITE
        );



        EndDrawing();





        if (deleteHover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            MOVIEINFO* movie =
                findMovieByName(name);


            if (movie)
            {
                deleteNode(movie);
            }


            return;
        }
    }

    
}






void movieMenu() {

    int choice = -1;

    Rectangle buttons[8];

    for (int i = 0; i < 8; i++)
    {
        buttons[i] =
        {
            440.0f,
            150.0f + i * 65.0f,
            400.0f,
            50.0f
        };
    }


    string options[8] =
    {
        "Add Movie",
        "Display Movies",
        "Edit Movie",
        "Delete Movie",
        "Sort By Name",
        "Sort By Release Date",
        "Reserve Seats",
        "Exit"
    };


    while (!WindowShouldClose())
    {

        Vector2 mouse = GetMousePosition();


        BeginDrawing();

        ClearBackground(RAYWHITE);


        DrawRectangle(
            0,
            0,
            1280,
            100,
            BLUE
        );


        DrawText(
            "Cinesity",
            1280 / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );


        for (int i = 0; i < 8; i++)
        {

            bool hover =
                CheckCollisionPointRec(
                    mouse,
                    buttons[i]
                );


            DrawRectangleRec(
                buttons[i],
                hover ? DARKGRAY : GRAY
            );


            DrawText(
                options[i].c_str(),
                buttons[i].x + 50,
                buttons[i].y + 12,
                25,
                WHITE
            );



            if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                choice = i + 1;
            }
        }


        EndDrawing();

        switch (choice) {

        case 1:
            AddMovie(choice);
            break;


        case 2:
            display();
            choice = -1;
            break;


        case 3:
            EditMovie(choice);
            break;



        case 4:
        
            DeleteMovie(choice);
            break;


        case 5:

            sortByName();
            choice = -1;
            break;



        case 6:

            sortByReleaseDate();
            choice = -1;
            break;



        case 7:

            reserveMovieSeats();
            choice = -1;
            break;



        case 8:
            return;


        }

        

    }

}




void reserveMovieSeats() {

    MOVIEINFO* selectedMovie = nullptr;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(
            0,
            0,
            1280,
            100,
            BLUE
        );

        DrawText(
            "Cinesity",
            1280 / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );

        DrawText(
            "Select a Movie",
            500,
            130,
            30,
            BLACK
        );

        if (IsKeyPressed(KEY_TAB)) {

            return;

        }

        MOVIEINFO* temp = head;

        int y = 200;

        while (temp)
        {
            Rectangle movieButton =
            {
                390.0f,
                (float)y,
                500.0f,
                50.0f
            };

            bool hover =
                CheckCollisionPointRec(
                    mouse,
                    movieButton
                );

            DrawRectangleRec(
                movieButton,
                hover ? DARKGRAY : GRAY
            );

            DrawText(
                temp->name.c_str(),
                420,
                y + 12,
                25,
                WHITE
            );

            if (hover &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedMovie = temp;
            }

            temp = temp->next;
            y += 70;
        }

        EndDrawing();

        if (selectedMovie)
        {
            TheatreSeatReservationFunc();
            return;
        }
    }
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