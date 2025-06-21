#pragma once
#include "VectorND.h"
namespace NAG
{
	namespace Math
	{
		template<typename type>
		class Vec3 : public VectorND<type, 3>
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using const_pointer_type = const type*;
			using reference_type = type&;
			using const_reference_type = const type&;
			Vec3();
			Vec3(const type&, const type&, const type&);
			Vec3(const Vec3&);
			~Vec3() = default;
			type& x;
			type& y;
			type& z;
			Vec3 Cross(const Vec3&) const;
		};

		template <typename type>
		Vec3<type>::Vec3() : VectorND<type, 3>(), x(this->m_data[0]),y(this->m_data[1]),z(this->m_data[2])
		{
		}

		template <typename type>
		Vec3<type>::Vec3(const type& x_, const type& y_, const type& z_) : VectorND<type, 3>(x_, y_, z_), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2])
		{
		}

		template <typename type>
		Vec3<type>::Vec3(const Vec3& other) : VectorND<type, 3>(other.x,other.y,other.z), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2])
		{
		}

		template <typename type>
		Vec3<type> Vec3<type>::Cross(const Vec3& other) const
		{
			return Vec3{
		 y* other.z - z * other.y,
		 z * other.x -x * other.z,
		x * other.y -y * other.x };
		}
	}
}
template<typename type>
std::ostream& operator<<(std::ostream& os, const NAG::Math::Vec3 < type>& vec3)
{
	os << "Vec3: ";
	if (vec3.Size() == 0)
		return os << "[ ]" << std::endl;
	os << "[" << vec3.x << "," << vec3.y <<","<<vec3.z<< "]" << std::endl;
	return os;
}