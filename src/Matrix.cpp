#include "Matrix.hpp"
#include <cstring>
#include <cmath>

void
Matrix::setIdentity(float *m)
{
	m[0] = 1.0;
	m[1] = 0.0;
	m[2] = 0.0;
	m[3] = 0.0;
	m[4] = 0.0;
	m[5] = 1.0;
	m[6] = 0.0;
	m[7] = 0.0;
	m[8] = 0.0;
	m[9] = 0.0;
	m[10] = 1.0;
	m[11] = 0.0;
	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
}

void
Matrix::multiply(float *m1, float *m2)
{
	float	temp[16];
	int		x;
	int		y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			temp[y + (x*4)] = (m1[x*4] * m2[y]) +
								(m1[(x*4)+1] * m2[y+4]) +
								(m1[(x*4)+2] * m2[y+8]) +
								(m1[(x*4)+3] * m2[y+12]);
			y++;
		}
		x++;
	}
	std::memcpy(m1, temp, sizeof(float) << 4);
}

void
Matrix::perspective(float *matrix, float fov, float aspect, float nearz, float farz)
{
	float	range;

	range = tanf(fov * 0.00872664625) * nearz;
	std::memset(matrix, 0, sizeof(float) * 16);
	matrix[0] = (2 * nearz) / ((range * aspect) - (-range * aspect));
	matrix[5] = (2 * nearz) / (2 * range);
	matrix[10] = -(farz + nearz) / (farz - nearz);
	matrix[11] = -1;
	matrix[14] = -(2 * farz * nearz) / (farz - nearz);
}

void
Matrix::translate(float *matrix, float x, float y, float z)
{
	float	newmatrix[16];

	setIdentity(newmatrix);
	newmatrix[12] = x;
	newmatrix[13] = y;
	newmatrix[14] = z;
	multiply(matrix, newmatrix);
}

void
Matrix::rotate(float *matrix, float angle, AXIS axis)
{
	float	d2r;
	int		cos1[3];
	int		cos2[3];
	int		sin1[3];
	int		sin2[3];
	float	newmatrix[16];

	d2r = 0.0174532925199;
	cos1[0] = 5;
	cos1[1] = 0;
	cos1[2] = 0;
	cos2[0] = 10;
	cos2[1] = 10;
	cos2[2] = 5;
	sin1[0] = 6;
	sin1[1] = 2;
	sin1[2] = 1;
	sin2[0] = 9;
	sin2[1] = 8;
	sin2[2] = 4;
	setIdentity(newmatrix);
	newmatrix[cos1[axis]] = cos(d2r * angle);
	newmatrix[sin1[axis]] = -sin(d2r * angle);
	newmatrix[sin2[axis]] = -newmatrix[sin1[axis]];
	newmatrix[cos2[axis]] = newmatrix[cos1[axis]];
	multiply(matrix, newmatrix);
}
