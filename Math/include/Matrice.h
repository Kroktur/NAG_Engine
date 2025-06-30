#pragma once
#include "Array.h"

namespace NAG
{
	namespace Math
	{

		template<Concept::AllOpAlgo type, size_t height, size_t width = height> requires Concept::MinValue<1,height,width> && Concept::DefaultConstructorType<type>
		class Matrix
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using const_pointer_type = const type*;
			using reference_type = type&;
			using const_reference_type = const type&;
			Matrix();
			Matrix(const Matrix&);
			Matrix(const std::initializer_list <type>&);
			template<Concept::AllOpAlgo... Args> requires Concept::IsConvertible<type,Args...> && Concept::DefaultConstructorType<Args...>
			Matrix(const Args&...);
			~Matrix() = default;
			void Clear();
			Matrix& operator=(const Matrix&);
			bool operator==(const Matrix&) const;
			bool operator!=(const Matrix&) const;
			size_t Size() const;
			size_t Height() const;
			size_t Width() const;
			size_t GetCellIndex(const size_t&, const size_t&) const;
			reference_type GetCell(const size_t&, const size_t&);
			const_reference_type GetCell(const size_t&, const size_t&) const;
			reference_type operator[](const size_t&);
			reference_type At(const size_t&);
			const_reference_type operator[](const size_t&) const;
			const_reference_type At(const size_t&)const;
			Matrix operator +(const Matrix&) const;
			Matrix operator -(const Matrix&) const;
			Matrix& operator +=(const Matrix&);
			Matrix& operator -=(const Matrix&);
			Matrix operator *(const type&) const;
			Matrix operator /(const type&) const;
			Matrix& operator *=(const type&);
			Matrix& operator /=(const type&);
			bool IsZero() const;
			template<size_t otherwidth>requires Concept::MinValue<1, otherwidth>
			Matrix<type, height, otherwidth> MatrixProduct(const Matrix<type, width, otherwidth>&);
		private:
			Array < type, width* height> m_data;
		};

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>::Matrix() : m_data()
		{

		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>::Matrix(const Matrix& other) :m_data(other.m_data)
		{
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>::Matrix(const std::initializer_list<type>& list) :m_data(list)
		{

		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		template<Concept::AllOpAlgo... Args> requires Concept::IsConvertible<type, Args...> && Concept::DefaultConstructorType<Args...>
		Matrix<type, height, width>::Matrix(const Args&... arg):m_data(arg...)
		{

		}

		template <Concept::AllOpAlgo type, size_t height, size_t width> requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		void Matrix<type, height, width>::Clear()
		{
			m_data.Clear();
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>& Matrix<type, height, width>::operator=(const Matrix& other)
		{
			if (this == &other)
				return *this;
			m_data = other.m_data;
			return *this;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		bool Matrix<type, height, width>::operator==(const Matrix& other) const
		{
			return m_data == other.m_data;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		bool Matrix<type, height, width>::operator!=(const Matrix& other) const
		{
			return m_data != other.m_data;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		size_t Matrix<type, height, width>::Size() const
		{
			return m_data.Size();
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		size_t Matrix<type, height, width>::Height() const
		{
			return height;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		size_t Matrix<type, height, width>::Width() const
		{
			return width;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		size_t Matrix<type, height, width>::GetCellIndex(const size_t& row, const size_t& col) const
		{
			auto index = row * width + col;
			if (index >= Size())
				throw std::out_of_range("out of range");
			return index;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		typename Matrix<type, height, width>::reference_type Matrix<type, height, width>::GetCell(const size_t& row,
			const size_t& col)
		{
			return m_data[GetCellIndex(row, col)];
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		typename Matrix<type, height, width>::const_reference_type Matrix<type, height, width>::GetCell(const size_t& row,
			const size_t& col) const
		{
			return m_data[GetCellIndex(row, col)];
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		typename Matrix<type, height, width>::reference_type Matrix<type, height, width>::operator[](const size_t& index)
		{
			return m_data[index];
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		typename Matrix<type, height, width>::reference_type Matrix<type, height, width>::At(const size_t& index)
		{
			return m_data.At(index);
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		typename Matrix<type, height, width>::const_reference_type Matrix<type, height, width>::operator[](const size_t& index) const
		{
			return m_data[index];
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		typename Matrix<type, height, width>::const_reference_type Matrix<type, height, width>::At(const size_t& index) const
		{
			return m_data.At(index);
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width> Matrix<type, height, width>::operator+(const Matrix& other) const
		{
			Matrix result;
			for (size_t i = 0; i < Size(); ++i)
			{
				result[i] = m_data[i] + other[i];
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width> Matrix<type, height, width>::operator-(const Matrix& other) const
		{
			Matrix result;
			for (size_t i = 0; i < Size(); ++i)
			{
				result[i] = m_data[i] - other[i];
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>& Matrix<type, height, width>::operator+=(const Matrix& other)
		{
			for (size_t i = 0; i < Size(); ++i)
			{
				m_data[i] += other[i];
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>& Matrix<type, height, width>::operator-=(const Matrix& other)
		{
			for (size_t i = 0; i < Size(); ++i)
			{
				m_data[i] -= other[i];
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width> Matrix<type, height, width>::operator*(const type& scalar) const
		{
			Matrix result;
			for (size_t i = 0; i < Size(); ++i)
			{
				result[i] = m_data[i] * scalar;
			}
			return result;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width> Matrix<type, height, width>::operator/(const type& scalar) const
		{
			if (scalar == 0)
				throw std::out_of_range(" imposible divide by 0");

			Matrix result;
			for (size_t i = 0; i < Size(); ++i)
			{
				result[i] = m_data[i] / scalar;
			}
			return  result;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>& Matrix<type, height, width>::operator*=(const type& scalar)
		{
			for (size_t i = 0; i < Size(); ++i)
			{
				 m_data[i] *= scalar;
			}
			return *this;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		Matrix<type, height, width>& Matrix<type, height, width>::operator/=(const type& scalar)
		{
			if (scalar == 0)
				throw std::out_of_range(" imposible divide by 0");

			for (size_t i = 0; i < Size(); ++i)
			{
				 m_data[i] /= scalar;
			}
			return  *this;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		bool Matrix<type, height, width>::IsZero() const
		{
			for (size_t i = 0; i < Size(); ++i)
			{
				if (m_data[i] != 0)
					return false;
			}
			return true;
		}

		template <Concept::AllOpAlgo type, size_t height, size_t width>requires Concept::MinValue<1, height, width>&& Concept::DefaultConstructorType<type>
		template <size_t otherwidth> requires Concept::MinValue<1,otherwidth>
		Matrix<type, height, otherwidth> Matrix<type, height, width>::MatrixProduct(
			const Matrix<type, width, otherwidth>& other)
		{
			Matrix<type, height, otherwidth> result;
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < otherwidth; ++col)
				{
					result.GetCell(row, col) = type{};
					for (size_t idx = 0; idx < width; ++idx)
					{
						result.GetCell(row, col) += GetCell(row, idx) * other.GetCell(idx, col);
					}
				}
			}
			return result;
		}

	}
}
template<NAG::Concept::AllOpAlgo type,size_t height, size_t width = height>
std::ostream& operator<<(std::ostream& os, const NAG::Math::Matrix<type,height,width>& contain)
{
	os << "Max: " << std::endl;
	if (contain.Size() == 0)
	{
		os <<"[ ]" << std::endl;
		return os;
	}
	for (auto i = 0 ; i < height ; ++i)
	{
		os << "[";
		for (auto j = 0 ; j < width - 1; ++j)
		{
			os << contain.GetCell(i, j) << " , ";
		}
		os << contain.GetCell(i, width - 1) << "]" << std::endl;
	}
	return os;
}