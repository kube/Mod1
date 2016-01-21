#include <Camera.hpp>
#include <cstring>
#include <cmath>

Camera::Camera()
: _rotSpeed(1.3)
, _moveSpeed(1.0)
{
	_p[0] = 0.0;
	_p[1] = 0.0;
	_p[2] = 20.0;

	_r[0] = 0.0;
	_r[1] = 0.0;
	_r[2] = 0.0;

	Matrix::setIdentity(_viewMatrix);
	Matrix::rotate(_viewMatrix, _r[0], X_AXIS);
	Matrix::rotate(_viewMatrix, _r[1], Y_AXIS);
	Matrix::rotate(_viewMatrix, _r[2], Z_AXIS);
	Matrix::translate(_viewMatrix, -_p[0], -_p[1], -_p[2]);

	std::memset(&keys, 0, 10 * sizeof(bool));
}

Camera::Camera(float px, float py, float pz, float rx, float ry, float rz)
: _rotSpeed(1.3)
, _moveSpeed(1.0)
{
	_p[0] = px;
	_p[1] = py;
	_p[2] = pz;

	_r[0] = rx;
	_r[1] = ry;
	_r[2] = rz;

	Matrix::setIdentity(_viewMatrix);
	Matrix::rotate(_viewMatrix, _r[0], X_AXIS);
	Matrix::rotate(_viewMatrix, _r[1], Y_AXIS);
	Matrix::rotate(_viewMatrix, _r[2], Z_AXIS);
	Matrix::translate(_viewMatrix, -_p[0], -_p[1], -_p[2]);
}

void
Camera::setP(float px, float py, float pz)
{
	_p[0] = px;
	_p[1] = py;
	_p[2] = pz;

	update();
}

void
Camera::setR(float rx, float ry, float rz)
{
	_r[0] = rx;
	_r[1] = ry;
	_r[2] = rz;

	update();
}

void
Camera::update()
{
	// Rotation
	if (keys.rRight && !keys.rLeft)
		_r[1] = ((_r[1] + _rotSpeed) >= 360.0) ? _r[1] + _rotSpeed - 360.0 : _r[1] + _rotSpeed;
	if (keys.rLeft && !keys.rRight)
		_r[1] = ((_r[1] + _rotSpeed) < 0.0) ? _r[1] - _rotSpeed + 360.0 : _r[1] - _rotSpeed;
	if (keys.rUp && !keys.rDown)
		_r[0] = ((_r[0] + _rotSpeed) >= 70.0) ? 70.0 : _r[0] + _rotSpeed;
	if (keys.rDown && !keys.rUp)
		_r[0] = ((_r[0] - _rotSpeed) < -70.0) ? -70.0 : _r[0] - _rotSpeed;

	// Position
	if (keys.mFront && !keys.mBack)
	{
		_p[0] += sin(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
		_p[2] += -cos(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
	}
	if (keys.mBack && !keys.mFront)
	{
		_p[0] += -sin(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
		_p[2] += cos(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
	}
	if (keys.mLeft && !keys.mRight)
	{
		_p[0] += -cos(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
		_p[2] += -sin(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
	}
	if (keys.mRight && !keys.mLeft)
	{
		_p[0] += cos(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
		_p[2] += sin(static_cast<float>(_r[1]) * M_PI / 180.0) * _moveSpeed;
	}
	if (keys.mUp && !keys.mDown)
		_p[1] += _moveSpeed;
	if (keys.mDown && !keys.mUp)
		_p[1] -= _moveSpeed;

	Matrix::setIdentity(_viewMatrix);
	Matrix::translate(_viewMatrix, -_p[0], -_p[1], -_p[2]);
	Matrix::rotate(_viewMatrix, _r[2], Z_AXIS);
	Matrix::rotate(_viewMatrix, _r[1], Y_AXIS);
	Matrix::rotate(_viewMatrix, _r[0], X_AXIS);
}

Camera::~Camera()
{
}
