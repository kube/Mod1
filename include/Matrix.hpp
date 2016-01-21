#ifndef MATRIX_HPP
#define MATRIX_HPP

typedef enum
{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS
} AXIS;

namespace Matrix
{
	void		setIdentity(float *m);
	void		multiply(float *m1, float *m2);
	void		perspective(float *matrix, float fov, float aspect, float nearz, float farz);
	void		translate(float *matrix, float x, float y, float z);
	void		rotate(float *matrix, float angle, AXIS axis);
}


#endif
