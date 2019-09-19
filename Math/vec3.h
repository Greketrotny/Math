#ifndef VEC3_H
#define VEC3_H

#include <math.h>	// sqrt(), sin(), cos()

namespace Math
{
	template <typename T> struct vec3
	{
		// -- fields -- //
	public:
		T x, y, z;

	public:
		// -- constructors -- //
		vec3()
			:x(0.0f),
			y(0.0f),
			z(0.0f)
		{
		}
		vec3(const vec3 &V)
			:x(V.x),
			y(V.y),
			z(V.z)
		{
		}
		vec3(vec3 &&V)
			:x(V.x),
			y(V.y),
			z(V.z)
		{
		}
		vec3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		~vec3()
		{
		}


		// -- static functions -- //
	public:
		static T DotProduct(const vec3 &V1, const vec3 &V2)
		{
			return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
		}
		static vec3 CrossProduct(const vec3 &V1, const vec3 &V2)
		{
			return vec3
			(
				V1.y * V2.z - V1.z * V2.y,
				V1.z * V2.x - V1.x * V2.z,
				V1.x * V2.y - V1.y * V2.x
			);
		}
		static T Similarity(const vec3 &V1, const vec3 &V2)
		{
			return DotProduct(V1, V2) / (V1.Magnitude() * V2.Magnitude());
		}
		static T Distance(const vec3 &V1, const vec3 &V2)
		{
			return (V1 - V2).Magnitude();
		}


		// -- non-static functions -- //
	public:
		T DotProduct(const vec3 &V)
		{
			return (this->x * V.x + this->y * V.y + this->z * V.z);
		}
		void CrossProduct(const vec3 &V)
		{
			this->x = this->y * V.z - this->z * V.y;
			this->y = this->z * V.x - this->x * V.z;
			this->z = this->x * V.y - this->y * V.x;
		}
		T Similarity(const vec3 &V)
		{
			return this->DotProduct(V) / (this->Magnitude() * V.Magnitude());
		}
		T Distance(const vec3 &V)
		{
			return (*this - V).Magnitude();
		}
		void Normalize()
		{
			T length = Magnitude();
			x /= length;
			y /= length;
			z /= length;
		}
		void Reverse()
		{
			x = -x;
			y = -y;
			z = -z;
		}
		void RotateX(T angle)
		{
			T newY = y * cos(angle) + z * sin(angle);
			z = y * -sin(angle) + z * cos(angle);
			y = newY;
		}
		void RotateY(T angle)
		{
			T newX = x * cos(angle) + z * -sin(angle);
			z = x * sin(angle) + z * cos(angle);
			x = newX;
		}
		void RotateZ(T angle)
		{
			T newX = x * cos(angle) + y * sin(angle);
			y = x * -sin(angle) + y * cos(angle);
			x = newX;
		}
		void Rotate(T rotationX, T rotationY, T rotationZ)
		{
			RotateX(rotationX);
			RotateY(rotationY);
			RotateZ(rotationZ);
		}
		

		// -- operators -- //
	public:
		vec3 operator+(const vec3 &V) const
		{
			return vec3(this->x + V.x, this->y + V.y, this->z + V.z);
		}
		vec3 operator-(const vec3 &V) const
		{
			return vec3(this->x - V.x, this->y - V.y, this->z - V.z);
		}
		vec3 operator*(T scalar) const
		{
			return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
		}
		vec3 operator/(T scalar) const
		{
			return vec3(this->x / scalar, this->y / scalar, this->z / scalar);
		}
		vec3& operator+=(const vec3 &V)
		{
			this->x += V.x;
			this->y += V.y;
			this->z += V.z;
			return *this;
		}
		vec3& operator-=(const vec3 &V)
		{
			this->x -= V.x;
			this->y -= V.y;
			this->z -= V.z;
			return *this;
		}
		vec3& operator*=(T scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			return *this;
		}
		vec3& operator/=(T scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			return *this;
		}
		vec3& operator=(const vec3 &V)
		{
			x = V.x;
			y = V.y;
			z = V.z;
			return *this;
		}
		vec3& operator=(vec3&& V)
		{
			x = V.x;
			y = V.y;
			z = V.z;
			return *this;
		}


		// -- getters and setters -- //
	public:
		void SetValues(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		T Magnitude() const
		{
			return (T)sqrt(x * x + y * y + z * z);
		}
	};
}

#endif // !VEC3_H