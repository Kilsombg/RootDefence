#ifndef __Vector2D__
#define __Vector2D__

#include<math.h>

/**
* Helper class representing Vector in 2D.
*/
class Vector2D
{
public:
	Vector2D(float x=0, float y=0);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	/**
	* Get length of the vector.
	*/
	float length();
	/**
	* Distance between two vectors.
	*/
	static float distance(const Vector2D& v1, const Vector2D& v2);
	/**
	* Distance between this vector and v2.
	*/
	float distanceTo(const Vector2D& v2);

	// operators overriding

	Vector2D operator+(const Vector2D& v2) const;

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);

	Vector2D operator*(float scalar);

	Vector2D& operator*=(float scalar);

	Vector2D operator-(const Vector2D& v2) const;

	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

	Vector2D operator/(float scalar);

	Vector2D& operator/=(float scalar);

	/**
	* Normalize vector.
	*/
	void normalize();

private:
	float m_x;
	float m_y;
};

#endif // !__Vector2D__
