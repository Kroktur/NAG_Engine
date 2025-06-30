#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "Utility.h"
namespace NAG
{
	namespace Math
	{
		static constexpr float PI = 3.141592f;

		template<NAG::Concept::FloatingType type>
		class AngleInterval
		{
		public:
			AngleInterval(const type& min, const type& max);
			AngleInterval(const AngleInterval& other);
			virtual ~AngleInterval() = default;
			type GetMin() const;
			type GetMax() const;
			type Normalize(const type& radiant) const;
			type Normalize(type& radiant);
			template<NAG::Concept::FloatingType type2>
			static bool IsInInterval(const type2& min, const type2& max, const AngleInterval<type2>& interval);
		private:
			type m_min;
			type m_max;
		};
		

		template<NAG::Concept::FloatingType type>
		class UnsignedInterval :public AngleInterval<type>
		{
		public:
			UnsignedInterval();
		};

		template<NAG::Concept::FloatingType type>
		class SignedInterval :public AngleInterval<type>
		{
		public:
			SignedInterval();
		};


		template<NAG::Concept::FloatingType type = float, NAG::Concept::DerivedClass<AngleInterval<type>> Interval = UnsignedInterval<type>> requires Concept::AllOpAlgo<type>
		class Angle
		{
		public:
			friend Angle<type, Interval> Degree<type, Interval>(const type&);
			friend Angle< type, Interval> Radiant<type, Interval>(const type&);
			using value_type = type;
			using const_reference_type = const type&;
			using angle_type = Interval;
			Angle();
			~Angle() = default;
			Angle(const Angle& other);

			type AsRadians();

			type AsRadians() const;

			type AsDegrees();

			type AsDegrees() const;

			Angle& operator=(const Angle& angle);

			Angle operator+(const Angle& angle) const;

			Angle operator-(const Angle& angle) const;

			Angle& operator +=(const Angle& other);

			Angle& operator -=(const Angle& other);

			Angle operator*(const_reference_type factor) const;

			Angle operator/(const_reference_type factor) const;

			Angle& operator *=(const_reference_type factor);

			Angle& operator /=(const_reference_type factor);

			bool operator==(const Angle& other) const;

			bool operator!=(const Angle& other) const;
			template<NAG::Concept::DerivedClass<AngleInterval<type>> NewInterval>
			Angle<type, NewInterval> ChangeIntervalCopy();

			AngleInterval<type> GetInterval()const;

		private:
			Angle(const type& radiant);
			type m_radiant;
			AngleInterval<type> m_strategy;
		};

		template<NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval = UnsignedInterval<float>> requires Concept::AllOpAlgo<type>
		Angle< type, Interval> Degree(const type&);

		template< NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval = UnsignedInterval<float>> requires Concept::AllOpAlgo<type>
		Angle < type, Interval > Radiant(const type&);

		template < NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval >requires Concept::AllOpAlgo<type>
		Angle< type, Interval> Degree(const type& degree)
		{
			auto rad = degree * (PI / 180.f);
			return Angle<type, Interval>(rad);
		}

		template < NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle< type, Interval> Radiant(const type& radiant)
		{
			return Angle<type, Interval>(radiant);
		}


		template <NAG::Concept::FloatingType type>
		AngleInterval<type>::AngleInterval(const type& min, const type& max):m_min(min), m_max(max)
		{}

		template <NAG::Concept::FloatingType type>
		AngleInterval<type>::AngleInterval(const AngleInterval& other):m_min(other.m_min),m_max(other.m_max)
		{
			
		}

		template <NAG::Concept::FloatingType type>
		type AngleInterval<type>::GetMin() const
		{
			return m_min;
		}

		template <NAG::Concept::FloatingType type>
		type AngleInterval<type>::GetMax() const
		{
			return m_max;
		}

		template <NAG::Concept::FloatingType type>
		type AngleInterval<type>::Normalize(const type& radiant) const
		{
			type range = m_max - m_min;
			type normalized = radiant - m_min;
			normalized = fmod(normalized, range);
			if (normalized < 0) {
				normalized += range;
			}
			return normalized + m_min;
		}

		template <NAG::Concept::FloatingType type>
		type AngleInterval<type>::Normalize(type& radiant)
		{
			type range = m_max - m_min;
			type normalized = radiant - m_min;
			normalized = fmod(normalized, range);
			if (normalized < 0) {
				normalized += range;
			}
			radiant = normalized + m_min;
			return radiant;
		}

		template <NAG::Concept::FloatingType type>
		template <NAG::Concept::FloatingType type2>
		bool AngleInterval<type>::IsInInterval(const type2& min, const type2& max, const AngleInterval<type2>& interval)
		{
			return (interval.GetMin() == min && interval.GetMax() == max);
		}

		template <NAG::Concept::FloatingType type>
		UnsignedInterval<type>::UnsignedInterval():AngleInterval<type>(0, 2 * PI)
		{}

		template <NAG::Concept::FloatingType type>
		SignedInterval<type>::SignedInterval():AngleInterval<type>(-PI, PI)
		{}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>::Angle(): m_radiant(0), m_strategy(Interval{})
		{
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>::Angle(const Angle& other):m_radiant(other.m_radiant), m_strategy(Interval{})
		{
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		type Angle<type, Interval>::AsRadians()
		{

			return m_strategy.Normalize(m_radiant);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		type Angle<type, Interval>::AsRadians() const
		{
			return m_strategy.Normalize(m_radiant);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		type Angle<type, Interval>::AsDegrees()
		{

			return (m_strategy.Normalize(m_radiant) * static_cast<type>(180) / static_cast<type>(PI));
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		type Angle<type, Interval>::AsDegrees() const
		{

			return (m_strategy.Normalize(m_radiant) * static_cast<type>(180) / static_cast<type>(PI));
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>& Angle<type, Interval>::operator=(const Angle& angle)
		{
			m_radiant = angle.m_radiant;
			return *this;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval> Angle<type, Interval>::operator+(const Angle& angle) const
		{
			return Angle(m_radiant + angle.m_radiant);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval> Angle<type, Interval>::operator-(const Angle& angle) const
		{
			return Angle(m_radiant - angle.m_radiant);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>& Angle<type, Interval>::operator+=(const Angle& other)
		{
			m_radiant += other.m_radiant;
			return *this;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>& Angle<type, Interval>::operator-=(const Angle& other)
		{
			m_radiant -= other.m_radiant;
			return *this;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval> Angle<type, Interval>::operator*(const type& factor) const
		{
			return Angle(m_radiant * factor);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval> Angle<type, Interval>::operator/(const type& factor) const
		{
			if (factor == 0)
				throw std::runtime_error("Imposible to divide by 0");
			return Angle(m_radiant / factor);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>& Angle<type, Interval>::operator*=(const type& factor)
		{
			m_radiant *= factor;
			return *this;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>& Angle<type, Interval>::operator/=(const type& factor)
		{
			if (factor == 0)
				throw std::runtime_error("Imposible to divide by 0");
			m_radiant /= factor;
			return *this;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		bool Angle<type, Interval>::operator==(const Angle& other) const
		{
			return m_radiant == other.m_radiant;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		bool Angle<type, Interval>::operator!=(const Angle& other) const
		{
			return m_radiant != other.m_radiant;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		template <NAG::Concept::DerivedClass<AngleInterval<type>> NewInterval>
		Angle<type, NewInterval> Angle<type, Interval>::ChangeIntervalCopy()
		{
			return Radiant<type, NewInterval>(m_radiant);
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		AngleInterval<type> Angle<type, Interval>::GetInterval() const
		{
			return m_strategy;
		}

		template <NAG::Concept::FloatingType type, NAG::Concept::DerivedClass<AngleInterval<type>> Interval>requires Concept::AllOpAlgo<type>
		Angle<type, Interval>::Angle(const type& radiant):m_radiant(radiant), m_strategy(Interval{})
		{
		}
	}
}
template< NAG::Concept::FloatingType type = float,NAG::Concept::DerivedClass<NAG::Math::AngleInterval<type>> Interval = NAG::Math::UnsignedInterval<type>>
std::ostream& operator<<(std::ostream& os, const NAG::Math::Angle <type, Interval>& angle)
{
	os << "Angle: " << angle.AsRadians() << " Rad" << std::endl;
	return os;
}