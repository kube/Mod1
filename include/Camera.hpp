#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Matrix.hpp>

typedef struct	s_Keys
{
	bool	mFront;
	bool	mBack;
	bool	mLeft;
	bool	mRight;
	bool	mUp;
	bool	mDown;

	bool	rLeft;
	bool	rRight;
	bool	rUp;
	bool	rDown;
}				Keys;

class Camera
{
public:
	Camera();
	Camera(float px, float py, float pz, float rx = 0, float ry = 0, float rz = 0);
	~Camera();

	float*	p() { return _p; }
	float*	r() { return _r; }
	float*	view() { return _viewMatrix; }

	void	setP(float px, float py, float pz);
	void	setR(float rx, float ry, float rz);
	void	update();


	Keys	keys;

private:
	float	_p[3];
	float	_r[3];
	float	_viewMatrix[16];

	float	_rotSpeed;
	float	_moveSpeed;
};

#endif
