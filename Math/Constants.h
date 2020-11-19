#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Math
{
	template <typename T = float> class constants
	{
	public:
		static constexpr float e			= 2.718281828f;

		static constexpr float pi			= 3.141592653f;
		static constexpr float half_pi		= 1.570796326f;
		static constexpr float third_pi		= 1.047197551f;
		static constexpr float quarter_pi	= 0.785398163f;
		static constexpr float eighth_pi	= 0.392699081f;
		static constexpr float two_pi		= 6.283185307f;
		static constexpr float three_pi		= 9.424777960f;
		static constexpr float four_pi		= 12.56637061f;
		static constexpr float r_pi			= 0.318309886f;
		static constexpr float r_half_pi	= 0.636619772f;
		static constexpr float r_two_pi		= 0.159154943f;

		static constexpr float tau			= 6.283185307f;
		static constexpr float half_tau		= pi;
		static constexpr float quarter_tau	= half_pi;
		static constexpr float eighth_tau	= quarter_pi;
		static constexpr float sixteenth_tau= eighth_pi;

		static constexpr float sqrt2		= 1.414213562f;
		static constexpr float sqrt3		= 1.732050807f;
	};
	template<> class constants<double>
	{
	public:
		static constexpr double e			= 2.7182818284590452353;

		static constexpr double pi			= 3.1415926535897932384;
		static constexpr double half_pi		= 1.5707963267948966192;
		static constexpr double third_pi	= 1.0471975511965977461;
		static constexpr double quarter_pi	= 0.7853981633974483096;
		static constexpr double eighth_pi	= 0.3926990816987241548;

		static constexpr double tau			= 6.2831853071795864769;
		static constexpr double half_tau	= pi;
		static constexpr double quarter_tau = half_pi;
		static constexpr double eighth_tau	= quarter_pi;
		static constexpr double sizteenth_tau = eighth_pi;

		static constexpr double sqrt2		= 1.4142135623730950488;
		static constexpr double sqrt3		= 1.7320508075688772935;
	};
}

#endif // !CONSTANTS_H