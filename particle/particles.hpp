#ifdef LOCALRAYLIB

    #include "raylib.h"

#else

    #include <raylib.h>

#endif

#include <math.h>
#include <vector>
#include <memory>



struct Particle 
{
    Texture2D texture;
    Vector2 position;
    Color color;
    float scale = 1, angle = 0, speed = 0, gravity = 0, lifeTime = 1;
};

struct PixelParticle 
{
    Vector2 position;
    Color color;
    int scale = 0;
    float angle = 0, speed = 0, gravity = 0, lifeTime = 1;
};

std::vector<std::unique_ptr<PixelParticle>> PixelParticles;
std::vector<std::unique_ptr<Particle>> Particles;


std::unique_ptr<Particle> CreateParticle(Texture2D tex, Vector2 pos, Color col, float speed, float gravity, int angle, float scale = 1, float lifeTime = 10) {
    std::unique_ptr<Particle> p = std::make_unique<Particle>(tex, pos, col, scale, angle, speed, gravity, lifeTime);
    Particles.push_back(p);
    return p;
}

std::unique_ptr<PixelParticle> CreatePixelParticle(Vector2 pos, Color col, float speed, float gravity, int angle, int scale = 1, float lifeTime = 10) {
    std::unique_ptr<PixelParticle> p = std::make_unique<PixelParticle>(pos, col, scale, angle, speed, gravity, lifeTime);
    PixelParticles.push_back(p);
    return p;
}

void DrawParticle(Particle &p) {
    DrawTexturePro(p.texture, {0, 0, (float)p.texture.width, (float)p.texture.height}, {p.position.x, p.position.y, (float)p.texture.width* p.scale, (float)p.texture.height * p.scale}, {(float)p.texture.width/2 * p.scale, (float)p.texture.height/2 * p.scale}, p.angle, p.color);
}
void DrawPixelParticle(PixelParticle &p) { 
    DrawRectanglePro({p.position.x, p.position.y, (float)p.scale, (float)p.scale}, {p.position.x + (p.scale / 2), p.position.y + (p.scale / 2)}, p.angle, p.color);
}

void UpdateParticles(Particle &p) {
    p.position.x += (cos(p.angle * PI /180)* p.speed);
    p.position.y += (sin(p.angle * PI /180)* p.speed);
    p.position.y += p.gravity * GetFrameTime();
    p.lifeTime -= GetFrameTime();
}

void UpdatePixelParticle(PixelParticle &p) {
    p.position.x += (cos(p.angle * PI / 180) * p.speed);
    p.position.y += (sin(p.angle * PI /180) * p.speed);
    p.position.y += p.gravity * GetFrameTime();
    p.lifeTime -= GetFrameTime();    
}

Color REffect(int x, int y, int z, int banding) {
    Color colorEffect = ColorFromHSV((float)(((x + y + z) * banding ) % 360 ), 0.75f, 0.9f); // straight up stolen from a raylib example
    return colorEffect;
}

void ParticlesClear() {
    Particles.clear();
}
void PixelParticlesClear() {
    PixelParticles.clear();
}

void DestroyParticles() {
    for (int i = 0; i < Particles.size(); i++) {
        if (Particles[i]->lifeTime <= 0) {
            Particles.erase(Particles.begin()+i);
        }
    }   
    for (int i = 0; i < PixelParticles.size(); i++) {  
        if (PixelParticles[i]->lifeTime <= 0) {
            PixelParticles.erase(PixelParticles.begin() + i);
        }
    }   
}
/*bool CheckCollisionParticles(PixelParticle* A, PixelParticle* B)
{
    bool C = false;
    if (CheckCollisionRecs(Rectangle{ (float)A->Position.x, (float)A->Position.y, (float)A->Size, (float)A->Size }, Rectangle{ (float)B->Position.x, (float)B->Position.y, (float)B->Size, (float)B->Size }))
    {
        C = true;
    }
    return C;
}*/
