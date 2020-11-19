#ifndef VEC2_H
#define VEC2_H

#include <math.h>

namespace Math
{
	template <typename T> struct vec2
	{
		// -- fields -- //
	public:
		T x, y;

	public:
		// -- constructors -- //
		vec2()
			:x(0.0f),
			y(0.0f)
		{
		}
		vec2(const vec2 &V)
			:x(V.x),
			y(V.y)
		{
		}
		vec2(vec2 &&V)
			:x(V.x),
			y(V.y)
		{
		}
		vec2(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		~vec2()
		{
		}


		// -- static functions -- //
	public:
		static T DotProduct(const vec2 &V1, const vec2 &V2)
		{
			return V1.x * V2.x + V1.y * V2.y;
		}
		static T Similarity(const vec2 &V1, const vec2 &V2)
		{
			return DotProduct(V1, V2) / (V1.Magnitude() * V2.Magnitude());
		}
		static T Distance(const vec2 &V1, const vec2 &V2)
		{
			return (V1 - V2).Magnitude();
		}


		// -- non-static functions -- //
	public:
		T DotProduct(const vec2 &V)
		{
			return (this->x * V.x + this->y * V.y);
		}
		T Similarity(const vec2 &V)
		{
			return this->DotProduct(V) / (this->Magnitude() * V.Magnitude());
		}
		T Distance(const vec2 &V)
		{
			return (*this - V).Magnitude();
		}
		void Normalize()
		{
			T length = Magnitude();
			x /= length;
			y /= length;
		}
		void Reverse()
		{
			x = -x;
			y = -y;
		}
		void Rotate(T angle)
		{
			T newX = x * cos(angle) - y * sin(angle);
			y = x * sin(angle) + y * cos(angle);
			x = newX;
		}


		// -- operators -- //
	public:
		vec2& operator=(const vec2 &V)
		{
			x = V.x;
			y = V.y;
			return *this;
		}
		vec2& operator=(vec2&& V)
		{
			x = V.x;
			y = V.y;
			return *this;
		}
		vec2 operator+(const vec2 &V) const
		{
			return vec2(this->x + V.x, this->y + V.y);
		}
		vec2 operator-(const vec2 &V) const
		{
			return vec2(this->x - V.x, this->y - V.y);
		}
		vec2 operator*(T scalar) const
		{
			return vec2(this->x * scalar, this->y * scalar);
		}
		vec2 operator/(T scalar) const
		{
			return vec2(this->x / scalar, this->y / scalar);
		}
		vec2& operator+=(const vec2 &V)
		{
			this->x += V.x;
			this->y += V.y;
			return *this;
		}
		vec2& operator-=(const vec2 &V)
		{
			this->x -= V.x;
			this->y -= V.y;
			return *this;
		}
		vec2& operator*=(T scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}
		vec2& operator/=(T scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}


		// -- getters and setters -- //
	public:
		void SetValues(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		T Magnitude() const
		{
			return (T)sqrt(x * x + y * y);
		}
	};
}

#endif // !VEC2_H