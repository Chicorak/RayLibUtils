#pragma once
#include "raylib.h"
#include <math.h>
#include <vector>
#include <memory>
//Particals have a randomized angle and lifetime


//place inside vector or array
struct Particle 
{
    Texture2D texture;
    Vector2 position;
    Color color;
    int Speed;
    int Angle;
    int LifeTime;
};
//Vector2 position; Color color; int size; int Speed; int Angle; int LifeTime;
struct PixelParticle 
{
    Vector2 position;
    Color color;
    int Size;
    int Speed;
    int Angle;
    int LifeTime;
};

std::vector<PixelParticle*> PixelParticles;
std::vector<Particle*> Particles;

//Used to Draw Particle
namespace Poison
{
    void DrawParticle(Texture2D Texture, Vector2 ParticlePosition, int Angle, int Speed, Color color)
    {
        ParticlePosition.x += (cos(Angle * PI /180)* Speed);
        ParticlePosition.y += (sin(Angle * PI /180)* Speed);
        DrawTexture(Texture, ParticlePosition.x, ParticlePosition.y, WHITE);
    }
    //Make Your Own Particle system and draw it using this helpful function
    void DrawProParticle(Texture2D Texture, Vector2 ParticlePosition, int Speed, int Rotation, int Scale, Color color)
    {
        DrawTextureEx(Texture, ParticlePosition, Rotation, Scale, color);
    }
    //Place Between StartDraw() and EndDraw()
    void AutoParticle(Particle &Particle)
    {
        Particle.position.x += (cos(Particle.Angle * PI /180)* Particle.Speed);
        Particle.position.y += (sin(Particle.Angle * PI /180)* Particle.Speed);
        Particle.LifeTime--;
        if(Particle.LifeTime >= 0)
            DrawTextureV(Particle.texture, Particle.position, Particle.color);
    }
    //Place Between StartDraw() and EndDraw()
    void AutoPixelParticle(PixelParticle &Particle)
    {
        Particle.position.x += (cos(Particle.Angle * PI /180)* Particle.Speed);
        Particle.position.y += (sin(Particle.Angle * PI /180)* Particle.Speed);
        Particle.LifeTime--;
        if(Particle.LifeTime >= 0)
            DrawRectangleV(Particle.position, Vector2{(float)Particle.Size, (float)Particle.Size}, Particle.color);      
    }
    Color REffect(int x, int y, int z)
    {
        Color colorEffect = ColorFromHSV((float)(((x + y + z)*18)%360), 0.75f, 0.9f);
        return colorEffect;
    }
}
void ParticleClear()
{
    for (int i = Particles.size() - 1; i >= 0; i--)
    {
        if (Particles[i]->LifeTime == 0) 
        {
            delete Particles[i];
            Particles.erase(Particles.begin()+i);
        }
    }   
    for (int i = PixelParticles.size() - 1; i >= 0; i--)
    {  
        if (PixelParticles[i]->LifeTime == 0) 
        {
            delete PixelParticles[i];
            PixelParticles.erase(PixelParticles.begin() + i);
        }
    }   
}
