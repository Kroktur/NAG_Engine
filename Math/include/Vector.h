#pragma once
#include <stdexcept>
#include "RevIterator.h"
#include "Iterator.h"
namespace NAG
{
	namespace Math
	{
		template<typename type>
		class Vector
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using const_pointer_type = const type*;
			using reference_type = type&;
			using const_reference_type =const type&;
			using difference_type = std::ptrdiff_t;
			using iterator_type = NAG::Math::Iterator<type>;
			using reverse_iterator_type = NAG::Math::ReverseIterator<type>;
			using const_iterator_type = NAG::Math::ConstIterator<type>;
			using const_reverse_Iterator_type = NAG::Math::ConstReverseIterator<type>;
			Vector();
			Vector(const Vector&);
			Vector(const std::initializer_list<value_type>&);
			template<typename... Args>
			Vector(const Args&...);
			~Vector();

			void resize(const size_t&);
			void reserve(const size_t&);
			void Clear();
			reference_type operator=(const NAG::Math::Vector<type>&);

			size_t Size() const;
			size_t Capacity() const;
			size_t MaxLimit() const;
			bool IsEmpty()const;

			reference_type operator[](const size_t&);
			reference_type at(const size_t&);
			const_reference_type operator[](const size_t&) const;
			const_reference_type at(const size_t&)const;
			reference_type front();
			reference_type back();
			const_reference_type front() const;
			const_reference_type back() const;
			pointer_type data();
			const_pointer_type data() const;

			iterator_type Begin();
			iterator_type End();
			const_iterator_type CBegin();
			const_iterator_type CEnd();
			reverse_iterator_type RBegin();
			reverse_iterator_type REnd();
			const_reverse_Iterator_type CRBegin();
			const_reverse_Iterator_type CREnd();

			void Push_Back(const value_type&);
			void Pop_Back();


		private:
			template<typename T, typename... Rest>
			void construct_elements(const size_t& index,  const T& first, const Rest&... rest);

			template<typename T>
			void construct_elements(const size_t& index, const T& last);

			type* m_data;
			size_t m_size;
			size_t m_capacity;
		};

		template <typename type>
		Vector<type>::Vector():m_size(0),m_capacity(0),m_data(nullptr)
		{
		}

		template <typename type>
		Vector<type>::Vector(const Vector& other):m_size(0),m_capacity(0),m_data(nullptr)
		{
			reserve(other.Capacity());
			resize(other.Size());
			std::copy(other.Begin(), other.End(), m_data);
		}

		template <typename type>
		Vector<type>::Vector(const std::initializer_list<type>& list) :m_size(0),m_capacity(0),m_data(nullptr)
		{
			resize(list.size());
			std::copy(list.begin(), list.end(), m_data);
		}

		template <typename type>
		template <typename ... Args>
		Vector<type>::Vector(const Args&... args):m_size(0),m_capacity(0),m_data(nullptr)
		{
			resize(sizeof...(Args));
			construct_elements(0,args...);
		}

		template <typename type>
		Vector<type>::~Vector()
		{
			Clear();
			delete[] m_data;
		}

		template <typename type>
		void Vector<type>::resize(const size_t& size)
		{
			if (size > m_capacity)
				reserve(size * 2);
			m_size = size;
		}

		template <typename type>
		void Vector<type>::reserve(const size_t& capacity)
		{
			if (capacity == m_capacity)
				return;
			if (capacity < m_size)
				throw std::out_of_range("size must be bigger");

			type* new_data = new type[capacity];
			std::copy(m_data, m_data + m_size, new_data);
			std::fill(new_data + m_size, new_data + capacity, type{});
			delete[] m_data;
			m_data = new_data;
			m_capacity = capacity;

		}

		template <typename type>
		size_t Vector<type>::Size() const
		{
			return  m_size;
		}

		template <typename type>
		size_t Vector<type>::Capacity() const
		{
			return m_capacity;
		}

		template <typename type>
		size_t Vector<type>::MaxLimit() const
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}

		template <typename type>
		bool Vector<type>::IsEmpty() const
		{
			if (m_size == 0)
				return true;
			return false;
		}

		template <typename type>
		typename Vector<type>::reference_type Vector<type>::operator[](const size_t& index)
		{
			return m_data[index];
		}

		template <typename type>
		typename Vector<type>::reference_type Vector<type>::at(const size_t& index)
		{
			if (index > m_size - 1)
				throw std::out_of_range(" index is too big");
			return m_data[index];
		}

		template <typename type>
		typename Vector<type>::const_reference_type Vector<type>::operator[](const size_t& index) const
		{
			return m_data[index];
		}

		template <typename type>
		typename Vector<type>::const_reference_type Vector<type>::at(const size_t& index) const
		{
			if (index > m_size - 1)
				throw std::out_of_range(" index is too big");
			return m_data[index];
		}

		template <typename type>
		typename Vector<type>::reference_type Vector<type>::front()
		{
			if (IsEmpty())
				throw std::out_of_range("Array is empty");
			return m_data[0];
		}

		template <typename type>
		typename Vector<type>::reference_type Vector<type>::back()
		{
			if (IsEmpty())
				throw std::out_of_range("Array is empty");
			return m_data[m_size - 1];
		}

		template <typename type>
		typename Vector<type>::const_reference_type Vector<type>::front() const
		{
			if (IsEmpty())
				throw std::out_of_range("Array is empty");
			return m_data[0];
		}

		template <typename type>
		typename Vector<type>::const_reference_type Vector<type>::back() const
		{
			if (IsEmpty())
				throw std::out_of_range("Array is empty");
			return m_data[m_size - 1];
		}

		template <typename type>
		typename Vector<type>::pointer_type Vector<type>::data()
		{
			return m_data;
		}

		template <typename type>
		typename Vector<type>::const_pointer_type Vector<type>::data() const
		{
			return m_data;
		}

		template <typename type>
		void Vector<type>::Clear()
		{
			resize(0);
			reserve(0);
		}

		template <typename type>
		typename Vector<type>::iterator_type Vector<type>::Begin()
		{
			if (IsEmpty())
				return Iterator<type>{};
			return Iterator<type>(m_data);
		}


		template <typename type>
		typename Vector<type>::iterator_type Vector<type>::End()
		{
			if (IsEmpty())
				return Iterator<type>{};
			return Iterator<type>(m_data + m_size);
		}

		template <typename type>
		typename Vector<type>::const_iterator_type Vector<type>::CBegin()
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data);
		}

		template <typename type>
		typename Vector<type>::const_iterator_type Vector<type>::CEnd()
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data + m_size);
		}

		template <typename type>
		typename Vector<type>::reverse_iterator_type Vector<type>::RBegin()
		{
			if (IsEmpty())
				return ReverseIterator<type>{};
			return ReverseIterator<type>(m_data + m_size - 1);
		}

		template <typename type>
		typename Vector<type>::reverse_iterator_type Vector<type>::REnd()
		{
			if (IsEmpty())
				return ReverseIterator<type>{};
			return ReverseIterator<type>(m_data - 1);
		}

		template <typename type>
		typename Vector<type>::const_reverse_Iterator_type Vector<type>::CRBegin()
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			ConstReverseIterator<type>(m_data + m_size - 1);
		}

		template <typename type>
		typename Vector<type>::const_reverse_Iterator_type Vector<type>::CREnd()
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data - 1);
		}

		template <typename type>
		void Vector<type>::Push_Back(const value_type& value)
		{
			resize(m_size + 1);
			m_data[m_size - 1] = value;
		}

		template <typename type>
		void Vector<type>::Pop_Back()
		{
			if (IsEmpty())
				return;
			m_data[m_size - 1] = type{};
			resize(m_size - 1);
		}

		template <typename type>
		template <typename T, typename ... Rest>
		void Vector<type>::construct_elements(const size_t& index, const T& first, const Rest&... rest)
		{
			m_data[index] = first;
			construct_elements(index + 1,rest...);
		}

		template <typename type>
		template <typename T>
		void Vector<type>::construct_elements(const size_t& index, const T& last)
		{
			m_data[index] = last;
		}
	}
}
