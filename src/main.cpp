#include "raylib.h"
#include <vector>

const int screenWidth = 800;
const int screenHeight = 600;
const int cellSize = 10;
const int cols = screenWidth / cellSize;
const int rows = screenHeight / cellSize;

std::vector<int> grid(cols *rows, 0);

void PutSand() {
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    Vector2 mousePos = GetMousePosition();
    int x = mousePos.x / cellSize;
    int y = mousePos.y / cellSize;

    // Bounds check
    if (x >= 0 && x < cols && y >= 0 && y < rows) {
      grid[y * cols + x] = 1;
    }
  }
}

void Render() {
  BeginDrawing();
  ClearBackground(BLACK);

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      if (grid[y * cols + x] == 1) {
        DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, YELLOW);
      }
      // DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize,
      // DARKGRAY);
    }
  }

  DrawFPS(10, 10);
  EndDrawing();
}

void UpdatePhysics() {
  for (int y = rows - 2; y >= 0; y--) {
    for (int x = 0; x < cols; x++) {
      int i = y * cols + x;

      if (grid[i] == 1) {
        int below = (y + 1) * cols + x;
        int belowLeft = (y + 1) * cols + (x - 1);
        int belowRight = (y + 1) * cols + (x + 1);

        // Se o espaço abaixo estiver vazio, move
        if (grid[below] == 0) {
          grid[below] = 1;
          grid[i] = 0;
        } else {
          bool canRight = (x < cols - 1 && grid[belowRight] == 0);
          bool canLeft = (x > 0 && grid[belowLeft] == 0);
          if (canRight && canLeft) {
            if (GetRandomValue(0, 1) == 0) {
              grid[belowLeft] = 1;

            } else {

              grid[belowRight] = 1;
            }
            grid[i] = 0;
          } else if (canRight) {
            grid[belowRight] = 1;
            grid[i] = 0;
          } else if (canLeft) {
            grid[belowLeft] = 1;
            grid[i] = 0;
          }
        }
      }
    }
  }
}

int main() {
  InitWindow(screenWidth, screenHeight, "SandFall Grid");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
        IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      PutSand();
    }

    // --- Renderização ---
    Render();

    UpdatePhysics();
  }

  CloseWindow();
  return 0;
}
