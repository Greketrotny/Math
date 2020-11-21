#ifndef ANGLE_H
#define ANGLE_H

#include "constants.h"
#include <cmath>

namespace Math
{
	// angle units
	enum class angle_unit { rad, deg, rev };
	
	// base angle class with aritmetic
	template <typename derived_angle, typename T = float> struct base_angle
	{
	protected:
		T m_value;


	public:
		constexpr base_angle(const T& value)
			: m_value{ value }
		{}

		
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
	
	template <angle_unit U = angle_unit::rad, typename T = float> 
	struct angle;

	// angle class instances per angle type
	template <typename T> 
	struct angle<angle_unit::rad, T> : public base_angle<angle<angle_unit::rad, T>, T>
	{
	public:
		constexpr angle(const T& value = static_cast<T>(0.0))
			: base_angle<angle<angle_unit::rad, T>, T>(value)
		{}
		angle(const angle<angle_unit::rad, T>& other)
			: base_angle<angle<angle_unit::rad, T>, T>(other)
		{}
		angle(const angle<angle_unit::deg, T>& other)
			: base_angle<angle<angle_unit::rad, T>, T>(other.value() * constants<T>::pi / static_cast<T>(180.0))
		{}
		angle(const angle<angle_unit::rev, T>& other)
			: base_angle<angle<angle_unit::rad, T>, T>(other.value()* constants<T>::tau)
		{}
	};
	template <typename T> 
	struct angle<angle_unit::deg, T> : public base_angle<angle<angle_unit::deg, T>, T>
	{
	public:
		constexpr angle(const T& value = static_cast<T>(0.0))
			: base_angle<angle<angle_unit::deg, T>, T>(value)
		{}		
		angle(const angle<angle_unit::deg, T>& other)
			: base_angle<angle<angle_unit::deg, T>, T>(other.value())
		{}		
		angle(const angle<angle_unit::rad, T>& other)
			: base_angle<angle<angle_unit::deg, T>, T>(other.value()* static_cast<T>(180.0) / constants<T>::Pi)
		{}
		angle(const angle<angle_unit::rev, T>& other)
			: base_angle<angle<angle_unit::deg, T>, T>(other.value()* static_cast<T>(360.0))
		{}
	};
	template <typename T> 
	struct angle<angle_unit::rev, T> : public base_angle<angle<angle_unit::rev, T>, T>
	{
	public:
		constexpr angle(const T& value = static_cast<T>(0.0))
			: base_angle<angle<angle_unit::rev, T>, T>(value)
		{}
		angle(const angle<angle_unit::rev, T>& other)
			: base_angle<angle<angle_unit::rev, T>, T>(other.value())
		{}
		angle(const angle<angle_unit::rad, T>& other)
			: base_angle<angle<angle_unit::rev, T>, T>(other.value() / constants<T>::tau)
		{}
		angle(const angle<angle_unit::deg, T>& other)
			: base_angle<angle<angle_unit::rev, T>, T>(other.value() / static_cast<T>(360.0))
		{}
	};

	constexpr angle<angle_unit::rad, float> operator"" _radf(long double value)
	{
		return angle<angle_unit::rad, float>(value);
	}
	constexpr angle<angle_unit::deg, float> operator"" _degf(long double value)
	{
		return angle<angle_unit::deg, float>(value);
	}
	constexpr angle<angle_unit::rev, float> operator"" _revf(long double value)
	{
		return angle<angle_unit::rev, float>(value);
	}
}

#endif // !ANGLE_H