#pragma once
#include "Array.h"
#include <cmath>
namespace NAG
{
	namespace Math
	{
		template<Concept::AllOpAlgo type, size_t size> requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		class VectorND
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using const_pointer_type = const type*;
			using reference_type = type&;
			using const_reference_type = const type&;

			VectorND();
			VectorND(const VectorND&);
			VectorND(const std::initializer_list <type> &);
			template<Concept::AllOpAlgo... Args> requires Concept::IsConvertible<type, Args...> && Concept::DefaultConstructorType<Args...>
			VectorND(const Args&...);
			~VectorND()=default;
			void Clear();
			VectorND& operator=(const VectorND&);
			bool operator==(const VectorND&) const;
			bool operator!=(const VectorND&) const;
			size_t Size() const;
			reference_type operator[](const size_t&);
			reference_type At(const size_t&);
			const_reference_type operator[](const size_t&) const;
			const_reference_type At(const size_t&)const;
			VectorND<type, size> operator +(const VectorND<type, size>&) const;
			VectorND<type, size> operator -(const VectorND<type, size>&) const;
			VectorND<type, size>& operator +=(const VectorND<type, size>&);
			VectorND<type, size>& operator -=(const VectorND<type, size>&);
			VectorND<type, size> operator *(const type&) const;
			VectorND<type, size> operator /(const type&) const;
			VectorND<type, size>& operator *=(const type&);
			VectorND<type, size>& operator /=(const type&);
			type Norm() const;
			VectorND Normalize() const;
			bool IsZero() const;	
			type Dot(const VectorND<type, size>&) const;

		protected:
			Array<type, size> m_data;
		};

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>::VectorND() : m_data()
		{
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>::VectorND(const VectorND& other) :m_data(other.m_data)
		{

		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>::VectorND(const std::initializer_list<type>& list) : m_data(list)
		{
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		template <Concept::AllOpAlgo ... Args> requires Concept::IsConvertible<type, Args...> && Concept::DefaultConstructorType<Args...>
		VectorND<type, size>::VectorND(const Args&... arg): m_data(arg...)
		{

		}

		template <Concept::AllOpAlgo type, size_t size> requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		void VectorND<type, size>::Clear()
		{
			m_data.Clear();
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>& VectorND<type, size>::operator=(const VectorND& other)
		{
			if (this == &other)
				return *this;
			m_data = other.m_data;
			return *this;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		bool VectorND<type, size>::operator==(const VectorND& other) const
		{
			return m_data == other.m_data;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		bool VectorND<type, size>::operator!=(const VectorND& other) const
		{
			return m_data != other.m_data;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size> VectorND<type, size>::operator+(const VectorND<type, size>& other) const
		{
			VectorND result;
			for (size_t i = 0 ; i < size ; ++i)
			{
				result[i] =m_data[i] + other[i];
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size> VectorND<type, size>::operator-(const VectorND<type, size>& other) const
		{
			VectorND result;
			for (size_t i = 0; i < size; ++i)
			{
				result[i] = m_data[i] - other[i];
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>& VectorND<type, size>::operator+=(const VectorND<type, size>& other)
		{
			for (size_t i = 0; i < size; ++i)
			{
				m_data[i] += other[i];
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>& VectorND<type, size>::operator-=(const VectorND<type, size>& other)
		{
			for (size_t i = 0; i < size; ++i)
			{
				m_data[i] -= other[i];
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size> VectorND<type, size>::operator*(const type& factor) const
		{
			VectorND result ;
			for (size_t i = 0; i < size; ++i)
			{
				result[i] = m_data[i] * factor;
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size> VectorND<type, size>::operator/(const type& factor) const
		{
			if (factor == 0)
				throw std::out_of_range(" imposible divide by 0");

			VectorND result;
			for (size_t i = 0; i < size; ++i)
			{
				result[i] = m_data[i] / factor;
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>& VectorND<type, size>::operator*=(const type& factor)
		{
		
			for (size_t i = 0; i < size; ++i)
			{
				m_data[i] *= factor;
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size>& VectorND<type, size>::operator/=(const type& factor)
		{
			if (factor == 0)
				throw std::runtime_error(" imposible divide by 0");
			for (size_t i = 0; i < size; ++i)
			{
				m_data[i] /= factor;
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		type VectorND<type, size>::Norm() const
		{
			type result =type{};
			for (size_t i = 0; i < size; ++i)
			{
				result += m_data[i] * m_data[i];
			}
			return std::sqrt(result);
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		VectorND<type, size> VectorND<type, size>::Normalize() const
		{
			type length = Norm();
			if (length == 0)
				throw std::runtime_error("can't normilize null vector");
			return *this / length;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		bool VectorND<type, size>::IsZero() const
		{
			for (size_t i  = 0 ; i < size  ; ++ i)
			{
				if (m_data[i] != 0)
					return false;
			}
			return true;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		type VectorND<type, size>::Dot(const VectorND<type, size>& other) const
		{
			type result = type{};
			for (size_t i = 0; i < size; ++i)
			{
				result += m_data[i] * other[i];
			}
			return result;
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		size_t VectorND<type, size>::Size() const
		{
			return m_data.Size();
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		typename VectorND<type, size>::reference_type VectorND<type, size>::operator[](const size_t& index)
		{
			return m_data[index];
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		typename VectorND<type, size>::reference_type VectorND<type, size>::At(const size_t& index)
		{
			return m_data.At(index);
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		typename VectorND<type, size>::const_reference_type VectorND<type, size>::operator[](const size_t& index) const
		{
			return m_data[index];
		}

		template <Concept::AllOpAlgo type, size_t size>requires Concept::MinValue<1, size>&& Concept::DefaultConstructorType<type>
		typename VectorND<type, size>::const_reference_type VectorND<type, size>::At(const size_t& index) const
		{
			return m_data.At(index);
		}
	}
}
template<NAG::Concept::AllOpAlgo type, size_t size>
std::ostream& operator<<(std::ostream& os, const NAG::Math::VectorND < type, size >& vectorND)
{
	os << "VecND: ";
	if (size == 0)
		return os << "[ ]" << std::endl;
	os << "[";
	for (auto i = 0; i < size - 1; ++i)
	{
		os << vectorND.At(i) << ",";
	}
	os << vectorND.At(size - 1) << "]" << std::endl;
	return os;
}