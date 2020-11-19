#ifndef VEC3_H
#define VEC3_H

#include <math.h>	// sqrt(), sinf(), cosf()
#include <stdint.h>

namespace Math
{
	template <typename T> struct vec3
	{
	public:
		T x, y, z;

	public:
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
		vec3(vec3 &&V) noexcept
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
		static vec3 Normalize(const vec3& v)
		{
			vec3 norm = v;
			norm.Normalize();
			return norm;
		}
		static vec3 Reverse(const vec3& v)
		{
			return vec3(
				-v.x,
				-v.y,
				-v.z);
		}


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
			T newY = y * cosf(angle) + z * sinf(angle);
			z = y * -sinf(angle) + z * cosf(angle);
			y = newY;
		}
		void RotateY(T angle)
		{
			T newX = x * cosf(angle) + z * -sinf(angle);
			z = x * sinf(angle) + z * cosf(angle);
			x = newX;
		}
		void RotateZ(T angle)
		{
			T newX = x * cosf(angle) + y * sinf(angle);
			y = x * -sinf(angle) + y * cosf(angle);
			x = newX;
		}
		void RotateXYZ(T rotationX, T rotationY, T rotationZ)
		{
			RotateX(rotationX);
			RotateY(rotationY);
			RotateZ(rotationZ);
		}
		void RotateXYZ(const vec3& rot)
		{
			RotateX(rot.x);
			RotateY(rot.y);
			RotateZ(rot.z);
		}
		void RotateZYX(T rotationX, T rotationY, T rotationZ)
		{
			RotateZ(rotationZ);
			RotateY(rotationY);
			RotateX(rotationX);
		}
		void RotateZYX(const vec3& rot)
		{
			RotateZ(rot.z);
			RotateY(rot.y);
			RotateX(rot.x);
		}
		

	public:
		vec3 operator-() const
		{
			return vec3(-this->x, -this->y, -this->z);
		}
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
		vec3 operator*(const vec3& scalar) const
		{
			return vec3(this->x * scalar.x, this->y * scalar.y, this->z * scalar.z);
		}
		vec3 operator/(T scalar) const
		{
			return vec3(this->x / scalar, this->y / scalar, this->z / scalar);
		}
		vec3 operator/(const vec3& scalar) const
		{
			return vec3(this->x / scalar.x, this->y / scalar.y, this->z / scalar.z);
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
		vec3& operator*=(const vec3& scalar)
		{
			this->x *= scalar.x;
			this->y *= scalar.y;
			this->z *= scalar.z;
			return *this;
		}
		vec3& operator/=(T scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			return *this;
		}
		vec3& operator/=(const vec3& scalar)
		{
			this->x /= scalar.x;
			this->y /= scalar.y;
			this->z /= scalar.z;
			return *this;
		}
		vec3& operator=(const vec3 &V)
		{
			x = V.x;
			y = V.y;
			z = V.z;
			return *this;
		}
		vec3& operator=(vec3&& V) noexcept
		{
			x = V.x;
			y = V.y;
			z = V.z;
			return *this;
		}


	public:
		void Set(T x, T y, T z)
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

	typedef vec3<float> vec3f;
	typedef vec3<double> vec3d;
	typedef vec3<int32_t> vec3i32;
	typedef vec3<uint32_t> vec3ui32;
}

#endif // !VEC3_H