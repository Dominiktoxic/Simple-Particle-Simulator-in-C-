#include <iostream>
#include <raylib.h>
#include <cmath>

const int screenWidth = 800;
const int screenHeight = 800;

class Particles {
    public:
        Vector2 particles[500];
        int numParticles = 500;
        Vector2 direction;

        Particles() {
            for (int i = 0; i < numParticles - 1; i++) {
                particles[i].x = GetRandomValue(0, screenWidth);
                particles[i].y = GetRandomValue(0, screenHeight);
            }
        }

        void Draw() {
            for (int i = 0; i < numParticles - 1; i++) {
                DrawCircle(particles[i].x, particles[i].y, 3, BLACK);
            }
        }

        void Update(Vector2 mousePos) {
            Draw();

            float maxSpeed = 1.0f;
            float range = 300.0f;

            for (int i = 0; i < numParticles; i++) {
                float dx = mousePos.x - particles[i].x;
                float dy = mousePos.y - particles[i].y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance <= range) {
                    direction.x = dx / distance;
                    direction.y = dy / distance;

                    float speed = maxSpeed * (1.0f - distance / range);

                    particles[i].x += direction.x * speed;
                    particles[i].y += direction.y * speed;
                }
            }
        }
};

int main() {

    InitWindow(screenWidth, screenHeight, "Particle Simulator");
    SetTargetFPS(60);

    Particles particles;
    Vector2 mousePos;

    while (WindowShouldClose() == false){
        BeginDrawing();

        ClearBackground(WHITE);
        
        mousePos = GetMousePosition();
        particles.Update(mousePos);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}