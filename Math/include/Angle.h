#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath> 
namespace NAG
{
	namespace Math
	{
		static constexpr float PI = 3.141592f;
		template<typename type>
		class IAngleInterval
		{
		public:
			IAngleInterval(const float&, const float&);
			virtual ~IAngleInterval() = default;
			virtual type Normalize(const type&) const = 0;
		private:
			float m_min;
			float m_max;
		};

		template<typename type>
		class UnsignedInterval : public IAngleInterval<type>
		{
		public:
			UnsignedInterval();
			type Normalize(const type&) const override;
		};
		template<typename type>
		class SignedInterval : public IAngleInterval<type>
		{
		public:
			SignedInterval();
			type Normalize(const type&) const override;
		};

		template<typename ,typename type>
		concept AngleInterval = requires{};


		template<typename type = float, AngleInterval Interval = UnsignedInterval<type>>
		class Angle
		{
		public:
			friend Angle<type, Interval> Degree<type,Interval>(const type&);
			friend Angle<type, Interval> Radiant<type, Interval>(const type&);
			using value_type = type;
			using angle_type = Interval;
			Angle();
			~Angle();
			Angle(const Angle& other);
			type AsRadians();
			type AsRadians() const;
			type AsDegrees(); 
			type AsDegrees() const;
			Angle& operator=(const Angle&);
			Angle operator+(const Angle&) const;
			Angle operator-(const Angle&) const;
			Angle& operator +=(const Angle&);
			Angle& operator -=(const Angle&);
			Angle operator*(const type&) const;
			Angle operator/(const type& ) const;
			Angle& operator *=(const type& );
			Angle& operator /=(const type& );
			bool operator==(const Angle& ) const;
			bool operator!=(const Angle& ) const;
			template<AngleInterval newstrategy>
			Angle<type,newstrategy> ChangeInterval();
		private:
			Angle(const type&);
			type m_radiant;
			IAngleInterval<type>* m_strategy;
		};

		template<typename type = float , AngleInterval Interval = UnsignedInterval<type>>
		Angle<type, Interval> Degree(const type&);

		template<typename type =float, AngleInterval Interval = UnsignedInterval<type>>
		Angle<type, Interval> Radiant(const type&);

		template <typename type, AngleInterval Interval >
		Angle<type, Interval> Degree(const type& degree)
		{
			return Angle<type, Interval>(degree * (PI / 180.f));
		}

		template <typename type , AngleInterval Interval>
		Angle<type, Interval> Radiant(const type& radiant)
		{
			return Angle<type, Interval>(radiant);
		}


		template <typename type>
		IAngleInterval<type>::IAngleInterval(const float& min, const float& max ):m_min(min), m_max(max)
		{
		}

		template <typename type>
		UnsignedInterval<type>::UnsignedInterval():IAngleInterval<type>(0, 2 * PI)
		{
		}

		template <typename type>
		type UnsignedInterval<type>::Normalize(const type& radiant) const
		{
			type result = std::fmod(radiant, 2 * PI);
			if (result < 0.0f) result += (2 * PI);
			return result;
		}

		template <typename type>
		SignedInterval<type>::SignedInterval() : IAngleInterval<type>(-PI,PI)
		{
		}

		template <typename type>
		type SignedInterval<type>::Normalize(const type& radiant) const
		{
			type result = std::fmod(radiant + PI, 2 * PI);
			if (result < 0.0f) result += 2 * PI;
			return result - PI;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>::Angle() : m_radiant(0),m_strategy(new Interval{})
		{
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>::~Angle()
		{
			delete m_strategy;
			m_strategy = nullptr;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>::Angle(const Angle& other):m_radiant(other.m_radiant),m_strategy(new Interval{})
		{
		}

		template <typename type, AngleInterval Interval>
		type Angle<type, Interval>::AsRadians()
		{
			
			return m_strategy->Normalize(m_radiant);
		}

		template <typename type, AngleInterval Interval>
		type Angle<type, Interval>::AsRadians() const
		{
			return m_strategy->Normalize(m_radiant);;
		}

		template <typename type, AngleInterval Interval>
		type Angle<type, Interval>::AsDegrees()
		{
			
			return (m_strategy->Normalize(m_radiant)* 180 / PI);
		}

		template <typename type, AngleInterval Interval>
		type Angle<type, Interval>::AsDegrees() const
		{
			return (m_strategy->Normalize(m_radiant)* 180 / PI);
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>& Angle<type, Interval>::operator=(const Angle& angle)
		{
			m_radiant = angle.m_radiant;
			return *this;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval> Angle<type, Interval>::operator+(const Angle& angle) const
		{
			return Angle(m_radiant + angle.m_radiant);
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval> Angle<type, Interval>::operator-(const Angle& angle) const
		{
			return Angle( m_radiant - angle.m_radiant);
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>& Angle<type, Interval>::operator+=(const Angle& other)
		{
			m_radiant += other.m_radiant;
			return *this;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>& Angle<type, Interval>::operator-=(const Angle& other)
		{
			m_radiant -= other.m_radiant;
			return *this;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval> Angle<type, Interval>::operator*(const type& factor) const
		{
			return Angle(m_radiant * factor);
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval> Angle<type, Interval>::operator/(const type& factor) const
		{
			if (factor == 0)
				throw std::runtime_error("Imposible to divide by 0");
			return Angle(m_radiant / factor);
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>& Angle<type, Interval>::operator*=(const type& factor)
		{
			m_radiant *= factor;
			return *this;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>& Angle<type, Interval>::operator/=(const type& factor)
		{
			if (factor == 0)
				throw std::runtime_error("Imposible to divide by 0");
			m_radiant /= factor;
			return *this;
		}

		template <typename type, AngleInterval Strategy>
		bool Angle<type, Strategy>::operator==(const Angle& other) const
		{
			return m_radiant == other.m_radiant;
		}

		template <typename type, AngleInterval Strategy>
		bool Angle<type, Strategy>::operator!=(const Angle& other) const
		{
			return m_radiant != other.m_radiant;
		}

		template <typename type, AngleInterval Interval>
		template <AngleInterval newstrategy>
		Angle<type, newstrategy> Angle<type, Interval>::ChangeInterval()
		{
			return Radiant<type, newstrategy>(m_radiant);
		}

		template <typename type, AngleInterval Interval>
		void Angle<type, Interval>::VerifyLimit()
		{
			auto min = m_strategy->Min();
			auto max = m_strategy->Max();
			float range = max - min;
			 m_radiant = std::fmod(m_radiant - min, range);

			if (m_radiant < 0)
				m_radiant += range;

			m_radiant += min;
		}

		template <typename type, AngleInterval Interval>
		type Angle<type, Interval>::ConstVerifyLimit() const
		{
			auto min = m_strategy->Min();
			auto max = m_strategy->Max();
			float range = max - min;
			type result = std::fmod(m_radiant - min, range);

			if (result < 0)
				result += range;

			result += min;
			return result;
		}

		template <typename type, AngleInterval Interval>
		Angle<type, Interval>::Angle(const type& radiant) :m_radiant(radiant),m_strategy(new Interval{})
		{
		}

	}
}
template<typename type>
std::ostream& operator<<(std::ostream& os,  const NAG::Math::Angle < type>& angle)
{
	os << "Angle: " << angle.AsRadians() << " Rad" << std::endl;
	return os;
}