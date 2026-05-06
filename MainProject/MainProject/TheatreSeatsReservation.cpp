#include <iostream>
#include "TheatreSeatsReservationHeader.h"
#include "raylib.h"
#include "..\MovieManagement\MovieManagement.h"

using namespace std;

void TheatreSeatReservationFunc() {

    const int rows = 10;
    const int cols = 15;
    InitWindow(1000, 700, "Seat Selection");
    SetTargetFPS(60);

    SEATDETAILS seats[rows][cols];

    // Initialize seat data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            seats[r][c].state = 0;
            seats[r][c].row = r;
            seats[r][c].col = c;
        }
    }

    enum GameScreen { MENU, SEATS };
    GameScreen currentScreen = MENU;

    int spacing = 5;

    Rectangle confirmBtn = { 0, 0, 200, 50 };
    Rectangle openSeatsBtn = { 400, 300, 200, 60 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(BLACK);

        if (currentScreen == MENU) {

            DrawText("MAIN MENU", 400, 200, 30, WHITE);

            DrawRectangleRec(openSeatsBtn, DARKBLUE);
            DrawText("SELECT SEATS", 410, 320, 20, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(mouse, openSeatsBtn)) {
                currentScreen = SEATS;
            }

        }
        else if (currentScreen == SEATS) {

            DrawText("SELECT YOUR SEATS", 350, 30, 25, WHITE);

            // --- AUTO SCALE ---
            int gridWidth = 800;
            int gridHeight = 400;

            int seatSizeX = (gridWidth - (cols - 1) * spacing) / cols;
            int seatSizeY = (gridHeight - (rows - 1) * spacing) / rows;
            int seatSize = (seatSizeX < seatSizeY) ? seatSizeX : seatSizeY;

            int startX = (GetScreenWidth() - (cols * (seatSize + spacing))) / 2;
            int startY = 100;

            // --- DRAW + UPDATE SEATS ---
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {

                    // update rectangle every frame
                    seats[r][c].rect.x = startX + c * (seatSize + spacing);
                    seats[r][c].rect.y = startY + r * (seatSize + spacing);
                    seats[r][c].rect.width = seatSize;
                    seats[r][c].rect.height = seatSize;

                    Color color;

                    if (seats[r][c].state == 0) color = GREEN;
                    else if (seats[r][c].state == 1) color = WHITE;
                    else color = GRAY;

                    DrawRectangleRec(seats[r][c].rect, color);

                    // click logic
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                        CheckCollisionPointRec(mouse, seats[r][c].rect)) {

                        if (seats[r][c].state == 0) {
                            seats[r][c].state = 1;

                            // debug print
                            char rowLetter = 'A' + r;
                            int seatNumber = c + 1;
                            TraceLog(LOG_INFO, "Selected: %c%d", rowLetter, seatNumber);

                        }
                        else if (seats[r][c].state == 1) {
                            seats[r][c].state = 0;
                        }
                    }
                }
            }

            // --- CONFIRM BUTTON POSITION ---
            int gridBottom = startY + rows * (seatSize + spacing);

            confirmBtn.x = (GetScreenWidth() - confirmBtn.width) / 2;
            confirmBtn.y = gridBottom + 20;

            DrawRectangleRec(confirmBtn, BLUE);
            DrawText("CONFIRM", confirmBtn.x + 40, confirmBtn.y + 15, 20, WHITE);

            // --- CONFIRM LOGIC ---
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(mouse, confirmBtn)) {

                for (int r = 0; r < rows; r++) {
                    for (int c = 0; c < cols; c++) {
                        if (seats[r][c].state == 1) {
                            seats[r][c].state = 2;
                        }
                    }
                }

                currentScreen = MENU;
            }
        }

        EndDrawing();
    }

    CloseWindow();

}