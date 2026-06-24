#include <iostream>
#include "RelatedNewsHeader.h"
#include "ScheduleProgrammeHeader.h"
#include "MainHeader.h"
#include "..\MovieManagement\MovieManagement.h"
#include "TheatreSeatsReservationHeader.h"
#include "..\MovieManagement\AccountManager.h"
#include "raylib.h"
#include <string>
#include "RegisterHeader.h"
#include "LoginHeader.h"
using namespace std;

int main()
{
    accManager.loadAccounts();

    int choice = 0;

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Cinesity");
    SetTargetFPS(60);

    Rectangle loginButton =
    {
        screenWidth / 2.0f - 150,
        screenHeight / 2.0f - 80,
        300,
        60
    };

    Rectangle registerButton =
    {
        screenWidth / 2.0f - 150,
        screenHeight / 2.0f + 20,
        300,
        60
    };

    Rectangle panel =
    {
        screenWidth / 2.0f - 220,
        screenHeight / 2.0f - 120,
        440,
        260
    };

    Color panelColor = { 220, 220, 220, 255 };

    while (!WindowShouldClose() && choice == 0)
    {
        Vector2 mousePos = GetMousePosition();

        bool loginHover = CheckCollisionPointRec(mousePos, loginButton);
        bool registerHover = CheckCollisionPointRec(mousePos, registerButton);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Blue ribbon
        DrawRectangle(0, 0, screenWidth, 100, BLUE);

        DrawText(
            "Cinesity",
            screenWidth / 2 - MeasureText("Cinesity", 40) / 2,
            30,
            40,
            WHITE
        );

        // Light gray panel
        DrawRectangleRec(panel, panelColor);

        // Login button
        DrawRectangleRec(
            loginButton,
            loginHover ? DARKGRAY : GRAY
        );

        DrawText(
            "Login",
            loginButton.x + (loginButton.width - MeasureText("Login", 30)) / 2,
            loginButton.y + 15,
            30,
            WHITE
        );

        // Register button
        DrawRectangleRec(
            registerButton,
            registerHover ? DARKGRAY : GRAY
        );

        DrawText(
            "Register",
            registerButton.x + (registerButton.width - MeasureText("Register", 30)) / 2,
            registerButton.y + 15,
            30,
            WHITE
        );

        EndDrawing();

        if (loginHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            choice = 1;
        }

        if (registerHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            choice = 2;
        }
    }

    

    string user, pass;

    while (!WindowShouldClose())
    {
        if (choice == 0)
        {
            Vector2 mousePos = GetMousePosition();

            bool loginHover = CheckCollisionPointRec(mousePos, loginButton);
            bool registerHover = CheckCollisionPointRec(mousePos, registerButton);


            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangle(0, 0, screenWidth, 100, BLUE);

            DrawText(
                "Cinesity",
                screenWidth / 2 - MeasureText("Cinesity", 40) / 2,
                30,
                40,
                WHITE
            );

            DrawRectangleRec(panel, panelColor);


            DrawRectangleRec(
                loginButton,
                loginHover ? DARKGRAY : GRAY
            );

            DrawText(
                "Login",
                loginButton.x + (loginButton.width - MeasureText("Login", 30)) / 2,
                loginButton.y + 15,
                30,
                WHITE
            );


            DrawRectangleRec(
                registerButton,
                registerHover ? DARKGRAY : GRAY
            );

            DrawText(
                "Register",
                registerButton.x + (registerButton.width - MeasureText("Register", 30)) / 2,
                registerButton.y + 15,
                30,
                WHITE
            );


            EndDrawing();


            if (loginHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                choice = 1;
            }

            if (registerHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                choice = 2;
            }
        }


        if (choice == 2)
        {
            RegisterPage(user, pass);

            choice = 0; // <-- this sends you back to menu
        }


        if (choice == 1)
        {
            LoginPage(user, pass);

            choice = 0; // <-- this sends you back to menu
        }
    }


    CloseWindow();
    return 0;
}