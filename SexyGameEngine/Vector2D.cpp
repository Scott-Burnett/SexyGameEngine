#include "Vector2D.h"

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int x, int y) {
	this->x = x;
	this->y = y;
}

Vector2D::~Vector2D() {
}

Vector2D& Vector2D::Add(const Vector2D& v2) {
	this->x += v2.x;
	this->y += v2.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& v2) {
	this->x -= v2.x;
	this->y -= v2.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& v2) {
	this->x *= v2.x;
	this->y *= v2.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& v2) {
	this->x /= v2.x;
	this->y /= v2.y;

	return *this;
}

Vector2D& Vector2D::Rotate(int a) {
	int rx = (cos(a) * this->x) - (sin(a) * this->y);
	int ry = (sin(a) * this ->x) + (cos(a) * this->y);
	this->x = rx;
	this->y = ry;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}

Vector2D& operator*(Vector2D& v1, int i){
	return v1.Multiply({v1.x * i, v1.y * i});
}

Vector2D& Vector2D::operator+=(const Vector2D& v2) {
	return this->Add(v2);
}

Vector2D& Vector2D::operator-=(const Vector2D& v2) {
	return this->Subtract(v2);
}

Vector2D& Vector2D::operator*=(const Vector2D& v2) {
	return this->Multiply(v2);
}

Vector2D& Vector2D::operator/=(const Vector2D& v2) {
	return this->Divide(v2);
}

std::ostream& operator<< (std::ostream& stream, const Vector2D& vector) {
	stream << "(" << vector.x << "," << vector.y << ")";
	return stream;
}