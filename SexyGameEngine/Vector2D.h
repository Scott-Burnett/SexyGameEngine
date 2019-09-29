#pragma once
/*  Class to represent 2D Point Vector 
    Designed by: Let's Make Games
	    Youtube:    https://www.youtube.com/user/creaper
	    video:      https://www.youtube.com/watch?v=ESNN57ofa3w
*/
#include <iostream>

class Vector2D {
public:
	int x, y;

	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();

	Vector2D& Add(const Vector2D& v2);
	Vector2D& Subtract(const Vector2D& v2);
	Vector2D& Multiply(const Vector2D& v2);
	Vector2D& Divide(const Vector2D& v2);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& v2);
	Vector2D& operator-=(const Vector2D& v2);
	Vector2D& operator*=(const Vector2D& v2);
	Vector2D& operator/=(const Vector2D& v2);

	friend std::ostream& operator<< (std::ostream& stream, const Vector2D& vector);
};