
      /*#######.           ##*
     ########",#:         ##***
   #########',##".       ##**:**
  ## ## ## .##',##.     ##** ::**
   ## ## ## # ##",#.   ##**   ::**
    ## ## ## ## ##'   ##**     ::**
     ## ## ## :##    ###########::**
      ## ## ## #     '::::::::::::*/

#include "Particle.hpp"

Particle::Particle()
: _velocity( Vec3(0.0, 0.0, 0.0) )
, _position( Vec3(0.0, 0.0, 0.0) )
{
}

Particle::Particle(const float px, const float py, const float pz, const float vx, const float vy, const float vz)
: _velocity( Vec3(vx, vy, vz) )
, _position( Vec3(px, py, pz) )
{
}

Particle::~Particle()
{
}
