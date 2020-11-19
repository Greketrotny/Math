#ifndef ANGLE_H
#define ANGLE_H

#include "constants.h"
#include <cmath>

namespace Math
{
	// angle units
	enum AngleUnit { rad, deg, rev };
	
	// base angle class with aritmetic
	template <typename derived_angle, typename T = float> struct base_angle
	{
	protected:
		T m_value;


	public:
		base_angle() = default;

		
	public:
		derived_angle operator-() const
		{
			return derived_angle(-this->m_value);
		}
		derived_angle operator+(const derived_angle& angle) const 
		{
			return derived_angle(this->m_value + angle.m_value);
		}
		derived_angle operator-(const derived_angle& angle) const 
		{
			return derived_angle(this->m_value - angle.m_value);
		}
		derived_angle operator*(const T& scalar) const
		{
			return derived_angle(this->m_value * scalar);
		}
		derived_angle operator/(const T& scalar) const
		{
			return derived_angle(this->m_value / scalar);
		}
		T operator%(const derived_angle& angle) const
		{
			return std::remainder<T, T>(this->m_value, angle.m_value);
		}
		derived_angle& operator+=(const derived_angle& angle)
		{
			this->m_value += angle.m_value;
			return *(static_cast<derived_angle*>(this));
		}
		derived_angle& operator-=(const derived_angle& angle)
		{
			this->m_value -= angle.m_value;
			return *(static_cast<derived_angle*>(this));
		}
		derived_angle& operator*=(const T& scalar)
		{
			this->m_value *= scalar;
			return *(static_cast<derived_angle*>(this));
		}
		derived_angle& operator/=(const T& scalar)
		{
			this->m_value /= scalar;
			return *(static_cast<derived_angle*>(this));
		}
		derived_angle& operator=(const derived_angle& angle)
		{
			this->m_value = angle.m_value;
			return *(static_cast<derived_angle*>(this));
		}
		derived_angle& operator=(const T& m_value)
		{
			this->m_value = m_value;
			return *(static_cast<derived_angle*>(this));
		}
		bool operator==(const derived_angle& angle) const
		{
			return this->m_value == angle.m_value;
		}
		bool operator!=(const derived_angle& angle) const
		{
			return this->m_value != angle.m_value;
		}
		bool operator<(const derived_angle& angle) const
		{
			return (this->m_value < angle.m_value);
		}
		bool operator>(const derived_angle& angle) const
		{
			return (this->m_value > angle.m_value);
		}
		bool operator<=(const derived_angle& angle) const
		{
			return (this->m_value <= angle.m_value);
		}
		bool operator>=(const derived_angle& angle) const
		{
			return (this->m_value >= angle.m_value);
		}


	public:
		const T value() const
		{
			return m_value;
		}
		T& value()
		{
			return m_value;
		}
	};
	template <AngleUnit U = AngleUnit::rad, typename T = float> struct angle : public base_angle<angle<U, T>, T> {};

	// angle class instances per angle type
	template <typename T> struct angle<AngleUnit::rad, T> : public base_angle<angle<AngleUnit::rad, T>, T>
	{
	public:
		angle(const T& value = static_cast<T>(0.0))
		{
			this->m_value = value;
		}
		angle(const angle<rad, T>& angle)
		{
			this->m_value = angle.m_value;
		}

		angle(const angle<deg, T>& angle)
		{
			this->m_value = angle.value() * constants<T>::pi / static_cast<T>(180.0);
		}
		angle(const angle<rev, T>& angle)
		{
			this->m_value = angle.value() * constants<T>::tau;
		}
	};
	template <typename T> struct angle<AngleUnit::deg, T> : public base_angle<angle<AngleUnit::deg, T>, T>
	{
	public:
		angle(const T& value = static_cast<T>(0.0))
		{
			this->m_value = value;
		}		
		angle(const angle<deg, T>& angle)
		{
			this->m_value = angle.m_value;
		}
		
		angle(const angle<rad, T>& angle)
		{
			this->m_value = angle.value() * static_cast<T>(180.0) / constants<T>::Pi;
		}
		angle(const angle<rev, T>& angle)
		{
			this->m_value = angle.value() * static_cast<T>(360.0);
		}
	};
	template <typename T> struct angle<AngleUnit::rev, T> : public base_angle<angle<AngleUnit::rev, T>, T>
	{
	public:
		angle(const T& value = static_cast<T>(0.0))
		{
			this->m_value = value;
		}
		angle(const angle<rev, T>& angle)
		{
			this->m_value = angle.m_value;
		}

		angle(const angle<rad, T>& angle)
		{
			this->m_value = angle.value() / constants<T>::tau;
		}
		angle(const angle<deg, T>& angle)
		{
			this->m_value = angle.value() / static_cast<T>(360.0);
		}
	};
}

#endif // !ANGLE_H