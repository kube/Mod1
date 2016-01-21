#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Vec3.hpp"

class Particle
{
public:
	Particle();
	Particle(const float px, const float py, const float pz, const float vx = 0.0, const float vy = 0.0, const float vz = 0.0);
	Particle(const Particle& rhs);

	float	density() const				{ return _density; }
	float	pressure() const			{ return _pressure; }
	Vec3	pressureForce()				{ return _pressureForce; }
	Vec3	externalForce()				{ return _externalForce; }
	Vec3	viscosityForce()			{ return _viscosityForce; }
	Vec3	velocity()					{ return _velocity; }
	Vec3	position()					{ return _position; }

	void	setDensity(const float density)										{ _density = density; }
	void	setPressure(const float pressure)									{ _pressure = pressure; }
	void	setPressureForce(const float px, const float py, const float pz)	{ _pressureForce = Vec3(px, py, pz); }
	void	setExternalForce(const float ex, const float ey, const float ez)	{ _externalForce = Vec3(ex, ey, ez); }
	void	setViscosityForce(const float vx, const float vy, const float vz)	{ _viscosityForce = Vec3(vx, vy, vz); }
	void	setVelocity(const float vx, const float vy, const float vz)			{ _velocity = Vec3(vx, vy, vz); }
	void	setPosition(const float x, const float y, const float z)			{ _position = Vec3(x, y, z); }

	Particle& operator=(const Particle& rhs);

	~Particle();

private:
	float	_density;
	float	_pressure;
	Vec3	_pressureForce;
	Vec3	_externalForce;
	Vec3	_viscosityForce;
	Vec3	_velocity;
	Vec3	_position;
};

#endif
