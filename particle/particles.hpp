#ifdef LOCALRAYLIB

    #include "raylib.h"

#else

    #include <raylib.h>

#endif

#include <math.h>
#include <vector>


enum Type {
    TYPE_NONE, // catch
    TYPE_CUSTOM, // user defined
    TYPE_SMOKE, //pezzza's work youtube guide follow basically 
    TYPE_FIRE, // custom fire not very accurate however a nice effect nonetheless
    TYPE_EXPLOSION // WIP
};


class Particle 
{
public:
    //  Texture2D tex, Vector2 pos, Color col, float scale, float rotation, float angle, float speed, float gravity, float lifeTime =
    Particle(Type type, Texture2D tex, Vector2 pos, Color col, float scale, float rotation, float angle, float speed, float gravity, float lifeTime = 1) {
        this->type = type;
        this->texture = tex;
        this->position = pos;
        this->color = col;
        this->scale = scale;
        this->rotation = rotation;
        this->angle = angle;
        this->speed = speed;
        this->gravity = gravity;
        this->lifeTime = lifeTime;
    }
    Type type;
    Texture2D texture;
    Vector2 position;
    Color color;
    float scale = 1, rotation = 0, angle = 0, speed = 0, gravity = 0, lifeTime = 1;
};

class PixelParticle 
{
public:

    PixelParticle(Type type, Vector2 pos, Color col, float scale, float rotation, float angle, float speed, float gravity, float lifeTime = 1) {
        this->type = type;
        this->position = pos;
        this->color = col;
        this->scale = scale;
        this->rotation = rotation;
        this->angle = angle;
        this->speed = speed;
        this->gravity = gravity;
        this->lifeTime = lifeTime;
    }
    Type type;
    Vector2 position;
    Color color;
    float scale = 0, rotation = 0, angle = 0, speed = 0, gravity = 0, lifeTime = 1;
};

std::vector<PixelParticle*> PixelParticles;
std::vector<Particle*> Particles;

//clamp function
float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Texture2D tex, Vector2 pos, Color col, float speed, float gravity, float rotation, int angle, float scale, float lifeTime
Particle* CreateParticle(Texture2D tex, Vector2 pos, Color col, float speed, float gravity, float rotation, int angle, float scale = 1, float lifeTime = 10) {
    Particle* p = new Particle(TYPE_CUSTOM, tex, pos, col, scale, rotation, angle, speed, gravity, lifeTime);
    Particles.push_back(p);
    return p;
}

//Vector2 pos, Color col, float speed, float gravity, float rotation, int angle, int scale , float lifeTime
PixelParticle* CreatePixelParticle(Vector2 pos, Color col, float speed, float gravity, float rotation, int angle, int scale = 1, float lifeTime = 10) {
    PixelParticle* p = new PixelParticle(TYPE_CUSTOM, pos, col, scale, rotation, angle, speed, gravity, lifeTime);
    PixelParticles.push_back(p);
    return p;
}

PixelParticle* CreatePixelParticleType(Type type, Vector2 pos, Color col, float speed, float angle, float lifeTime) {
    float scale;
    float rotation;
    float gravity = 0;

    switch (type) {
    case TYPE_SMOKE:
        angle += GetRandomValue(-25, 25);
        scale = 5;
        rotation = 0.0f;
        gravity = -4.0f;
        break;

    case TYPE_FIRE:
        angle += GetRandomValue(-55, 55);
        scale = 15;
        rotation = 0.0f;
        col.g = 125;
        gravity = -22.0f;
        break;

    case TYPE_EXPLOSION:
        scale = 0.2f;
        rotation = 0.0f;
        break;
    
    default:
        TraceLog(LOG_ERROR, "NO TYPE DEFINED IN PIXEL PARTICLE CREATION / CUSTOM PARTICLE DEFINE");
        col = Color{255, 0, 0, 255};
        scale = 1000;
        rotation = 1000.0f;
        gravity = 0.0f;
        break;
    }

    PixelParticle* p = new PixelParticle(type, pos, col, scale, rotation, angle, speed, gravity, lifeTime);
    PixelParticles.push_back(p);
    return p;

}

void CreateExplosion(Vector2 pos, Color col, float size, float lifeTime = 10) {
    col.a = 2;
    //create a lot of explosion type particles 
    for (float i = 0; i < 36; i+=1.0f) {
        CreatePixelParticleType(TYPE_EXPLOSION, pos, col, size, i * 10, lifeTime);
    }

    col.a = 2;
    for (float i = 0; i < 36; i+=0.5f) {
        CreatePixelParticleType(TYPE_EXPLOSION, pos, col, size - 1, i * 10, lifeTime);
    }
}

// POINTER REQUIRED PARTICLE TO DRAW
void DrawParticle(Particle p) {
    DrawTexturePro(p.texture, {0, 0, (float)p.texture.width, (float)p.texture.height}, {p.position.x, p.position.y, (float)p.texture.width* p.scale, (float)p.texture.height * p.scale}, {(float)p.texture.width/2 * p.scale, (float)p.texture.height/2 * p.scale}, p.rotation, p.color);
}
// POINTER REQUIRED PIXELPARTICLE TO DRAW
void DrawPixelParticle(PixelParticle p) { 
    DrawRectanglePro({p.position.x, p.position.y, (float)p.scale, (float)p.scale}, {(float)p.scale/2, (float) p.scale/2}, p.rotation, p.color);
}

void UpdateParticles(Particle *p) {
    p->position.x += (cos(p->angle * PI /180)* p->speed);
    p->position.y += (sin(p->angle * PI /180)* p->speed);
    p->position.y += (p->gravity * 10.0f) * GetFrameTime();
    p->lifeTime -= GetFrameTime();
}

void UpdatePixelParticle(PixelParticle *p) {
    switch (p->type)
    {
    case TYPE_SMOKE:
        p->rotation += GetRandomValue(1, 6);
        p->color.a = Clamp(p->color.a - (GetFrameTime() * 255), 0, 255);
        //if (p->color.a > 2) p->color.a -= 2.0f; else p->color.a = 0;
        p->scale += 0.55f;
        p->speed *= 0.98f;
        break;

    case TYPE_FIRE:
        p->rotation += GetRandomValue(1, 2);
        p->color.r = Clamp(p->color.r - 1.2f, 0, 255);
        p->color.g = Clamp(p->color.g - 4, 0, 255);
        p->color.b = Clamp(p->color.b + 0.5f, 0, 255);
        p->scale = Clamp(p->scale - 0.14f, 0, 100);
        p->speed *= 0.98f;
        break;
    
    case TYPE_EXPLOSION:
        p->color.a = Clamp(pow(p->color.a, 2) * (GetFrameTime() * 45), 0, 255);
        if (p->color.a >= 250 && p->scale >= 50) p->lifeTime = 0.0f;
        p->scale += 0.8f * (GetFrameTime() * 50);
        p->speed *= 0.92f;
        break;

    default:
        break;
    }
    p->position.x += (cos(p->angle * PI / 180) * p->speed);
    p->position.y += (sin(p->angle * PI / 180) * p->speed);
    p->position.y += (p->gravity * 10.0f)* GetFrameTime();
    p->lifeTime -= GetFrameTime();    
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
    for (size_t i = 0; i < Particles.size(); i++) {
        if (Particles[i]->lifeTime <= 0) {
            delete Particles[i];
            Particles.erase(Particles.begin()+i);
        }
    }   
    for (size_t i = 0; i < PixelParticles.size(); i++) {  
        if (PixelParticles[i]->lifeTime <= 0) {
            delete PixelParticles[i];
            PixelParticles.erase(PixelParticles.begin() + i);
        }
    }   
}
