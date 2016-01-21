
      /*#######.           ##*
     ########",#:         ##***
   #########',##".       ##**:**
  ## ## ## .##',##.     ##** ::**
   ## ## ## # ##",#.   ##**   ::**
    ## ## ## ## ##'   ##**     ::**
     ## ## ## :##    ###########::**
      ## ## ## #     '::::::::::::*/

#ifndef VEC3_HPP
#define VEC3_HPP

class Vec3
{
public:
	Vec3(const Vec3& rhs);
	Vec3(float px = 0, float py = 0, float pz = 0);

	float	norm();
	float	squareNorm();

	Vec3&	operator=(const Vec3& rhs);

	~Vec3();

	float	x;
	float	y;
	float	z;

	float	r;
	float	g;
	float	b;
	float	a;
};

#endif
