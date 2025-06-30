#pragma once
#include "VectorND.h"
namespace NAG
{
	namespace Math
	{
		template<Concept::AllOpAlgo type>requires Concept::DefaultConstructorType<type>
		class Vec2 : public VectorND<type, 2>
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using const_pointer_type = const type*;
			using reference_type = type&;
			using const_reference_type = const type&;
			Vec2();
			Vec2(const type&, const type&);
			Vec2(const Vec2&);
			~Vec2()= default;
			type& x;
			type& y;
			 Vec2<type> NormalVector();
		};

		template <Concept::AllOpAlgo type>requires Concept::DefaultConstructorType<type>
		Vec2<type>::Vec2() : VectorND<type, 2>(),x(this->m_data[0]),y(this->m_data[1])
		{
		}

		template <Concept::AllOpAlgo type>requires Concept::DefaultConstructorType<type>
		Vec2<type>::Vec2(const type& x_, const type& y_) : VectorND<type, 2>(x_, y_), x(this->m_data[0]), y(this->m_data[1])
		{
		}

		template <Concept::AllOpAlgo type>requires Concept::DefaultConstructorType<type>
		Vec2<type>::Vec2(const Vec2& other) : VectorND<type, 2>(other.x,other.y), x(this->m_data[0]), y(this->m_data[1])
		{
		}

		template <Concept::AllOpAlgo type>requires Concept::DefaultConstructorType<type>
		Vec2<type> Vec2<type>::NormalVector()
		{
			return Vec2<type>(-y, x);
		}
	}
}
template<NAG::Concept::AllOpAlgo type>
std::ostream& operator<<(std::ostream& os, const NAG::Math::Vec2 < type>& vec2)
{
	os << "Vec2: ";
	if (vec2.Size() == 0)
		return os << "[ ]" << std::endl;
	os << "[" << vec2.x << "," << vec2.y << "]" << std::endl;
	return os;
}