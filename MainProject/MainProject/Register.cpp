#include <iostream>
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"
#include "TheatreSeatsReservationHeader.h"
#include "raylib.h"
#include <string>
#include "RegisterHeader.h"
#include "..\MovieManagement\AccountManager.h"

using namespace std;

static string errorMessage = "";

void RegisterPage(string user, string pass) {



    Rectangle panel =
    {
        340,
        180,
        600,
        350
    };

    Rectangle registerButton =
    {
        490,
        430,
        300,
        60
    };


    bool typingUser = true;
    bool typingPass = false;

    user = "";
    pass = "";

    Rectangle backButton =
    {
        20,
        20,
        120,
        40
    };


    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();


        bool backHover = CheckCollisionPointRec(mouse, backButton);

        if (backHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return;
        }


        bool registerHover =
            CheckCollisionPointRec(mouse, registerButton);


        int key = GetCharPressed();


        // Username typing
        if (typingUser)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    user += (char)key;

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && user.length() > 0)
            {
                user.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (user.empty() || isBlank(user)) {
                    errorMessage = "Username cannot be empty!";
                }
                else {
                    typingUser = false;
                    typingPass = true;
                }
            }

        }


        // Password typing
        if (typingPass)
        {
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                    pass += (char)key;

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && pass.length() > 0)
            {
                pass.pop_back();
            }
        }


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && registerHover)
        {
            bool success = accManager.registerAccount(user, pass);

            if (success) {
                accManager.loadAccounts();
                loadMoviesFromFile();
                CustomerMenu();
                freeList();
                return;
            }
            else {
                errorMessage = accManager.getLastError();
                typingUser = true;
                typingPass = false;
                pass = "";
            }
        }






        BeginDrawing();


        ClearBackground(RAYWHITE);


        // blue ribbon
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

        DrawRectangleRec(backButton, backHover ? DARKGRAY : GRAY);

        DrawText(
            "Back",
            backButton.x + 30,
            backButton.y + 10,
            20,
            WHITE
        );

        // panel
        DrawRectangleRec(
            panel,
            LIGHTGRAY
        );


        DrawText(
            "Register",
            565,
            220,
            35,
            BLACK
        );


        // username box
        DrawRectangle(
            440,
            290,
            400,
            50,
            WHITE
        );

        DrawText(
            user.c_str(),
            450,
            305,
            25,
            BLACK
        );


        DrawText(
            "Username",
            440,
            260,
            20,
            DARKGRAY
        );



        // password box
        DrawRectangle(
            440,
            370,
            400,
            50,
            WHITE
        );


        string hiddenPass(pass.length(), '*');


        DrawText(
            hiddenPass.c_str(),
            450,
            385,
            25,
            BLACK
        );


        DrawText(
            "Password",
            440,
            340,
            20,
            DARKGRAY
        );





        // register button
        DrawRectangleRec(
            registerButton,
            registerHover ? DARKGRAY : GRAY
        );


        DrawText(
            "REGISTER",
            registerButton.x +
            (registerButton.width -
                MeasureText("REGISTER", 25)) / 2,
            registerButton.y + 18,
            25,
            WHITE
        );

        if (!errorMessage.empty()) {
            DrawText(errorMessage.c_str(), 450, 440, 20, RED);
        }




        EndDrawing();
    }

    

}