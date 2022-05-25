# How to use
there are two types of particles: Pixel and Texture.

There are three main functions to using the system:
Particle creation
Particle rendering
Particle destruction

to actually make a particle, call a CreateParticle with the following parameters:
CreateParticle(Texture2D tex, Vector2 pos, Color col, float speed, float gravity, int angle, float scale, float lifeTime);
or
CreatePixelParticle(Vector2 pos, Color col, float speed, float gravity, int angle, int scale, float lifeTime)

They return a smart pointer to their respective types for you to manage if required otherwise you can ignore it as the other update functions automatically update the particles

Scale and lifetime automatically have pre defines if you not want to define those you dont have to

Rendering is tied to raylib as this repo includes other useful raylib functions however im just redoing this files because my old i felt my old implemention does fit my current skills with c++ anymore
and the header doesnt manage the particles as much anymore and exposes more 'guts' to the devloper

===

# Example :

```c++
#include "raylib.h"
// if you have raylib.h in your include dir then define LOCALRAYLIB before including particles
#define LOCALRAYLIB
#include "particles.hpp"
/* 
* particles automatically includes the following: 
*   math.h
*   vector
*/

// i could redo the header for it to no include any C++ standard libary and make it C compatible however i do not
// currently have any intrest in doing so however i could give pointers if you need help with it
// contact me on discord at: CodePoison#8413 or you can find me on the Raylib discord



#define ScreenWidth     1280
#define ScreenHeight    720

int main(){
    while (!WindowShouldClose()){
        CreatePixelParticle( Vector2{ ScreenWidth/2, ScreenHeight/2 }, GREEN, 10.0f, 8.0f, GetRandomValue(0, 360), 2, 10.0f );

        for (int i = 0; i < PixelParticles.size(); i++) {
            //header provides this ^^ to automatically manage particles
            UpdatePixelParticle(PixelParticles[i]);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
            for (int i = 0; i < PixelParticles.size(); i++) {
                DrawPixelParticle(*PixelParticles[i]);
            }

        EndDrawing();
        DestroyParticles();
    }

    CloseWindow();
}
```
