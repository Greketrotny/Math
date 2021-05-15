#ifndef ANGLE_H
#define ANGLE_H

#include "constants.h"
#include <cmath>

namespace Math
{
	// angle units
	enum class angle_unit { rad, deg, rev };

	// base angle class with aritmetic
	template <angle_unit U, typename T = float> struct angle
	{
	private:
		template<typename T, angle_unit U1, angle_unit U2>
		struct converter
		{
			template<angle_unit U1, angle_unit U2>
			static T convert(const T& value);

			template<>
			static constexpr T convert<angle_unit::rad, angle_unit::deg>(const T& value)
			{
				return value * static_cast<T>(180.0) / constants<T>::Pi;
			}
			template<>
			static constexpr T convert<angle_unit::rad, angle_unit::rev>(const T& value)
			{
				return value / constants<T>::tau;
			}
			template<>
			static constexpr T convert<angle_unit::deg, angle_unit::rad>(const T& value)
			{
				return value * constants<T>::pi / static_cast<T>(180.0);
			}
			template<>
			static constexpr T convert<angle_unit::deg, angle_unit::rev>(const T& value)
			{
				return value / static_cast<T>(360.0);
			}
			template<>
			static constexpr T convert<angle_unit::rev, angle_unit::rad>(const T& value)
			{
				return value * constants<T>::tau;
			}
			template<>
			static constexpr T convert<angle_unit::rev, angle_unit::deg>(const T& value)
			{
				return value * static_cast<T>(360.0);
			}
		};
		template <typename T, angle_unit U>
		struct converter<T, U, U>
		{
			template<angle_unit U1, angle_unit U2>
			static constexpr T convert(const T& value)
			{
				return value;
			}
		};


		T m_value;


	public:
		constexpr angle()
			: m_value{}
		{}
		constexpr angle(const T& value)
			: m_value{ value }
		{}
		constexpr angle(const angle& other)
			: m_value(other.m_value)
		{}
		template <angle_unit U2>
		constexpr angle(const angle<U2, T>& other)
			: m_value(converter<T, U2, U>::convert<U2, U>(T(other)))
		{}
		angle(angle<U, T>&& other) = default;


		explicit constexpr operator T() const noexcept
		{
			return m_value;
		}
		angle operator-() const
		{
			return angle(-this->m_value);
		}
		angle operator+(const angle& other) const
		{
			return angle(this->m_value + other.m_value);
		}
		angle operator-(const angle& other) const
		{
			return angle(this->m_value - other.m_value);
		}
		angle operator*(const T& scalar) const
		{
			return angle(this->m_value * scalar);
		}
		angle operator/(const T& scalar) const
		{
			return angle(this->m_value / scalar);
		}
		T operator%(const angle& other) const
		{
			return std::remainder<T, T>(this->m_value, other.m_value);
		}
		angle& operator+=(const angle& other)
		{
			this->m_value += other.m_value;
			return *this;
		}
		angle& operator-=(const angle& other)
		{
			this->m_value -= other.m_value;
			return *this;
		}
		angle& operator*=(const T& scalar)
		{
			this->m_value *= scalar;
			return *this;
		}
		angle& operator/=(const T& scalar)
		{
			this->m_value /= scalar;
			return *this;
		}
		angle& operator=(const angle& other)
		{
			this->m_value = other.m_value;
			return *this;
		}
		angle& operator=(const T& value)
		{
			this->m_value = value;
			return *this;
		}
		bool operator==(const angle& other) const
		{
			return this->m_value == other.m_value;
		}
		bool operator!=(const angle& other) const
		{
			return this->m_value != other.m_value;
		}
		bool operator<(const angle& other) const
		{
			return (this->m_value < other.m_value);
		}
		bool operator>(const angle& other) const
		{
			return (this->m_value > other.m_value);
		}
		bool operator<=(const angle& other) const
		{
			return (this->m_value <= other.m_value);
		}
		bool operator>=(const angle& other) const
		{
			return (this->m_value >= other.m_value);
		}


		const T value() const
		{
			return m_value;
		}
		T& value()
		{
			return m_value;
		}
	};

	typedef angle<angle_unit::rad, float> angle_radf;
	typedef angle<angle_unit::deg, float> angle_degf;
	typedef angle<angle_unit::rev, float> angle_revf;
	typedef angle<angle_unit::rad, double> angle_rad;
	typedef angle<angle_unit::deg, double> angle_deg;
	typedef angle<angle_unit::rev, double> angle_rev;

	constexpr angle<angle_unit::rad, float> operator"" _radf(long double value)
	{
		return angle<angle_unit::rad, float>(static_cast<float>(value));
	}
	constexpr angle<angle_unit::deg, float> operator"" _degf(long double value)
	{
		return angle<angle_unit::deg, float>(static_cast<float>(value));
	}
	constexpr angle<angle_unit::rev, float> operator"" _revf(long double value)
	{
		return angle<angle_unit::rev, float>(static_cast<float>(value));
	}

	constexpr angle<angle_unit::rad, double> operator"" _rad(long double value)
	{
		return angle<angle_unit::rad, double>(static_cast<double>(value));
	}
	constexpr angle<angle_unit::deg, double> operator"" _deg(long double value)
	{
		return angle<angle_unit::deg, double>(static_cast<double>(value));
	}
	constexpr angle<angle_unit::rev, double> operator"" _rev(long double value)
	{
		return angle<angle_unit::rev, double>(static_cast<double>(value));
	}
}

#endif // !ANGLE_H