#include <iostream>
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"
#include "TheatreSeatsReservationHeader.h"
#include "..\MovieManagement\AccountManager.h"
#include "raylib.h"
#include <string>
#include "LoginHeader.h"

using namespace std;


void LoginPage(string user, string pass) {

    Rectangle panel =
    {
        340,
        180,
        600,
        350
    };


    Rectangle loginButton =
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


    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        Rectangle backButton = { 20, 20, 120, 40 };
        bool backHover = CheckCollisionPointRec(mouse, backButton);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && backHover)
        {
            return;
        }


        bool loginHover =
            CheckCollisionPointRec(mouse, loginButton);



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


            if (IsKeyPressed(KEY_BACKSPACE) &&
                user.length() > 0)
            {
                user.pop_back();
            }


            if (IsKeyPressed(KEY_ENTER))
            {
                typingUser = false;
                typingPass = true;
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


            if (IsKeyPressed(KEY_BACKSPACE) &&
                pass.length() > 0)
            {
                pass.pop_back();
            }
        }





        // Login button

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
            && loginHover)
        {

            if (!accManager.login(user, pass))
            {
                cout << "Invalid login!\n";
            }
            else
            {
                loadMoviesFromFile();      // make sure movies are in memory

                // admin (rank "user" or "admin") → full menu
                if (accManager.getCurrentRank() == "user" || accManager.getCurrentRank() == "admin")
                {
                    movieMenu();
                    freeList();
                }
                // customer → limited menu, auto display + sort + reserve
                else if (accManager.getCurrentRank() == "customer")
                {
                    loadMoviesFromFile();
                    CustomerMenu();
                    freeList();
                }


                return;    // go back to main window loop after menu exits
            }



            return;
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
            1280 / 2 -
            MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );



        DrawRectangleRec(backButton, backHover ? DARKGRAY : GRAY);
        DrawText("< Back", 35, 30, 24, WHITE);


        // panel

        DrawRectangleRec(
            panel,
            LIGHTGRAY
        );






        DrawText(
            "Login",
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







        // login button


        DrawRectangleRec(
            loginButton,
            loginHover ? DARKGRAY : GRAY
        );



        DrawText(
            "LOGIN",
            loginButton.x +
            (loginButton.width -
                MeasureText("LOGIN", 25)) / 2,
            loginButton.y + 18,
            25,
            WHITE
        );

        DrawRectangleRec(backButton, backHover ? DARKGRAY : GRAY);
        DrawText("Back", backButton.x + 30, backButton.y + 10, 20, WHITE);



        EndDrawing();

    }

}