
      /*#######.           ##*
     ########",#:         ##***
   #########',##".       ##**:**
  ## ## ## .##',##.     ##** ::**
   ## ## ## # ##",#.   ##**   ::**
    ## ## ## ## ##'   ##**     ::**
     ## ## ## :##    ###########::**
      ## ## ## #     '::::::::::::*/

#include <cmath>
#include "Vec3.hpp"

Vec3::Vec3(float px, float py, float pz)
: x(px)
, y(py)
, z(pz)
, r(0.0)
, g(1.0)
, b(1.0)
, a(1.0)
{
}

Vec3::Vec3(const Vec3& rhs)
: x(rhs.x)
, y(rhs.y)
, z(rhs.z)
{
}

float
Vec3::norm()
{
	return sqrt(x * x + y * y + z * z);
}

float
Vec3::squareNorm()
{
	return x * x + y * y + z * z;
}

Vec3&
Vec3::operator=(const Vec3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vec3::~Vec3()
{
}
