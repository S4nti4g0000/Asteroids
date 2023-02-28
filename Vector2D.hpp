#pragma once

#include <cmath>
#include <ostream>

class Vector2D
{

public:	

	Vector2D() noexcept
	{}

	Vector2D(const Vector2D &v)
		:x_(v.getX()), y_(v.getY())
	{}

	Vector2D(Vector2D&& v)
		:x_(v.getX()), y_(v.getY())
	{}

	Vector2D(float x, float y)
		:x_(x), y_(y)
	{}

	~Vector2D()
	{}

	//----

	inline float getX() const
	{
		return x_;
	}

	inline float getY() const
	{
		return y_;
	}

	inline float getLength() const
	{
		return sqrt(x_ * x_ + y_ * y_);
	}

	//----

	inline void setX(float x)
	{
		x_ = x;
	}

	inline void setY(float y)
	{
		y_ = y;
	}

	inline void set(float x, float y)
	{
		x_ = x;
		y_ = y;
	}

	inline void set(const Vector2D& v)
	{
		x_ = v.x_;
		y_ = v.y_;
	}

	inline void set(Vector2D&& v)
	{
		x_ = v.x_;
		y_ = v.y_;
	}

	inline void set(const Vector2D* v)
	{
		x_ = v->x_;
		y_ = v->y_;
	}

	inline Vector2D& operator = (const Vector2D& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	//----

	inline float magnitude() const
	{
		return sqrtf(powf(x_, 2) + powf(y_, 2));
	}

	inline Vector2D normalize() const
	{
		return *this / magnitude();
	}

	Vector2D rotate(float deg) const;

	Vector2D getNormalized()
	{
		float len = getLength();
		if (len == 0)
		{
			return Vector2D(0, 0);
		}
		else
		{
			return Vector2D(x_ / len, y_ / len);
		}
	}

	float angle(const Vector2D& v) const;

	//----


	inline Vector2D operator/(float d) const
	{
		return Vector2D(x_ / d, y_ / d);
	}
	
	inline Vector2D operator*(float d) const
	{
		return Vector2D(x_ * d, y_ * d);
	}

	inline Vector2D operator*(const Vector2D& d) const
	{
		return Vector2D(x_ * d.x_, y_ * d.y_);
	}

	Vector2D operator+=(Vector2D& v)
	{
		x_ += v.x_;
		y_ += v.y_;

		return *this;
	}

	//-

	inline Vector2D operator+(const Vector2D& v) const
	{
		return Vector2D(x_ + v.x_, y_ + v.y_);
	}
	
	inline Vector2D operator-(const Vector2D& v) const
	{
		return Vector2D(x_ - v.x_, y_ - v.y_);
	}


	//----


private:

	float x_;
	float y_;


};