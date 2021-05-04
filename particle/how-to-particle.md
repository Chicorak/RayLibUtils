# How to use
there are two types of particles: Pixel and Texture. Here is how to use the Texture 

There are two main functions to using the system:
AutoParticle
ParticleClear

The first main function is under the namespace poison and it draws and moves the particle it takes a particle type from the vector
and the second is a memory leak plug and you place the function before drawing or anywhere inside your gameplay loop and it takes no parameters

to actually make a particle you need to push it to a vector that have been created in the header its a pointer to a struct vector
heres how to push it in

Particles.push_back(new Particle{Texture, Vector2 Position, Color color; float size; int Speed; int Angle; int LifeTime;});
so we push back a new Particle with a Texture and a Vector2 type Position, with a raylib color type, next a size 1 is full size anyless shrinks it the rest is self explanitory

Example:
ParticleClear(); //right before drawing

for (auto &a : PixelParticles) AutoParticle(*a); // used to draw and modify the particle
