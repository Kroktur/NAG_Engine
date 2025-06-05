#pragma once
#include <stdexcept>
#include "RevIterator.h"
#include "Iterator.h"
#include "Utility.h"

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

			Vector<type>& operator=(const NAG::Math::Vector<value_type>&);
			bool operator==(const Vector&) const;
			bool operator!=(const Vector&) const;

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
			void Assign(const size_t&, const value_type&);
			void Assign(const std::initializer_list<value_type>&);
			template<NAG::Category::Iterator_Category IT>
			void Assign(const IT&, const IT&);
			void Insert(const iterator_type&, const value_type&);
			void Insert(const iterator_type&,const size_t&, const value_type&);
			void Insert(const iterator_type&,const std::initializer_list<value_type>&);
			template<NAG::Category::Iterator_Category IT>
			void Insert(const iterator_type&, const IT&, const IT&);

			void Erase(const iterator_type&);
			void Erase(const iterator_type&, const iterator_type&);
			void Erase(const iterator_type&,const size_t& size);


			template<NAG::Category::Container_Category container>
			void AppendRange(const container&);
			void swap(Vector&);

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
			NAG::Algorithm::Copy(other.Begin(), other.End(), m_data);
		}

		template <typename type>
		Vector<type>::Vector(const std::initializer_list<type>& list) :m_size(0),m_capacity(0),m_data(nullptr)
		{
			resize(list.size());
			NAG::Algorithm::Copy(list.begin(), list.end(), m_data);
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
			{
				size_t nextsize = std::min(size * 2,MaxLimit());
				reserve(nextsize);
			}
			m_size = size;
		}

		template <typename type>
		void Vector<type>::reserve(const size_t& capacity)
		{
			if (capacity == m_capacity)
				return;
			if (capacity < m_size)
				throw std::out_of_range("size must be bigger");

			if (capacity == 0)
			{
				delete[] m_data;
				m_data = nullptr;
				m_capacity = 0;
				return;
			}
			type* new_data = new type[capacity];
			NAG::Algorithm::Copy(m_data, m_data + m_size, new_data);
			NAG::Algorithm::Fill(new_data + m_size, new_data + capacity, type{});
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
		Vector<type>& Vector<type>::operator=(const NAG::Math::Vector<type>& other)
		{
			resize(other.Size());
			NAG::Algorithm::Copy(other.Begin(), other.End(), m_data);
			return *this;
		}

		template <typename type>
		bool Vector<type>::operator==(const Vector& other) const
		{
			if (m_size != other.Size())
				return false;
			for (std::make_signed_t<size_t> i = 0; i < m_size ; ++ i)
			{
				if (m_data[i] != other[i])
					return false;
			}
			return true;
		}

		template <typename type>
		bool Vector<type>::operator!=(const Vector& other) const
		{
			if (m_size != other.Size())
				return true;
			for (std::make_signed_t<size_t> i = 0; i < m_size; ++i)
			{
				if (m_data[i] != other[i])
					return true;
			}
			return false;
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
			return ConstReverseIterator<type>(m_data + m_size - 1);
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
		void Vector<type>::Assign(const size_t& count, const value_type& data)
		{
			Clear();
			resize(count);
			NAG::Algorithm::Fill(m_data, m_data + m_size,data);
		}

		template <typename type>
		void Vector<type>::Assign(const std::initializer_list<value_type>& list)
		{
			Clear();
			resize(list.size());
			NAG::Algorithm::Copy(list.begin(), list.end(), m_data);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Assign(const IT& begin, const IT& end)
		{
			Clear();
			auto size = end - begin;
			resize(size);
			for (auto i = 0 ; i< size ; ++i)
			{
				m_data[i] = *(begin + i);
			}
		}

		template <typename type>
		void Vector<type>::Insert(const iterator_type& it, const value_type& data)
		{
			if (it < Begin() || it > End())
				throw std::out_of_range("Iterator is invalid");
			resize(m_size + 1);
			for (auto curent_it = End() - 1; curent_it != it ; --curent_it)
			{
				*curent_it = *(curent_it - 1);
			}
			*it = data;
		}

		template <typename type>
		void Vector<type>::Insert(const iterator_type& it, const size_t& count, const value_type& data)
		{
			if (it < Begin() || it > End())
				throw std::out_of_range("Iterator is invalid");
			resize(m_size + count);
			for (auto curent_it = End() - 1; curent_it != it + count; --curent_it)
			{
				*curent_it = *(curent_it - count);
			}
			for (auto curent_it = it; curent_it < it + count; ++ curent_it)
			{
				*curent_it = data;
			}
		}

		template <typename type>
		void Vector<type>::Insert(const iterator_type& it, const std::initializer_list<value_type>& list)
		{
			if (it < Begin() || it > End())
				throw std::out_of_range("Iterator is invalid");
			resize(m_size + list.size());
			for (auto curent_it = End() - 1; curent_it != it + list.size(); --curent_it)
			{
				*curent_it = *(curent_it - list.size());
			}
			NAG::Algorithm::Copy(list.begin(), list.end(), it);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Insert(const iterator_type& it , const IT& begin, const IT& end)
		{
			auto count = end - begin;
			if (it < Begin() || it > End())
				throw std::out_of_range("Iterator is invalid");
			resize(m_size + count);
			for (auto curent_it = End() - 1; curent_it != it + count; --curent_it)
			{
				*curent_it = *(curent_it - count);
			}
			NAG::Algorithm::Copy(begin, end, it);
		}

		template <typename type>
		void Vector<type>::Erase(const iterator_type& it)
		{
			
			if (it < Begin() || it > End())
				throw std::out_of_range("Iterator is invalid");
			for (auto current_it = it; current_it != End() - 1; ++current_it)
			{
				*current_it = *(current_it + 1);
			}
			resize(m_size - 1);
		}


		template <typename type>
		void Vector<type>::Erase(const iterator_type& begin, const iterator_type& end)
		{
			if (begin < Begin() || end > End() || begin > end)
				throw std::out_of_range("Iterator is invalid");
			size_t totalsize = end - begin;
			for (auto current_it = begin; current_it != End() - totalsize ; ++current_it)
			{
				*current_it = *(current_it + totalsize);
			}
			resize(m_size - totalsize);
		}

		template <typename type>
		void Vector<type>::Erase(const iterator_type& it, const size_t& size)
		{
			auto end = it + size;
			if (it < Begin() || end > End())
				throw std::out_of_range("Iterator is invalid");
			for (auto current_it = it; current_it != End() - size; ++current_it)
			{
				*current_it = *(current_it + size);
			}
			resize(m_size - size);
		}

		template <typename type>
		template <NAG::Category::Container_Category container >
		void Vector<type>::AppendRange(const container& container)
		{
			Insert(End(), container.Begin(), container.End());
		}

		template <typename type>
		void Vector<type>::swap(Vector& other)
		{
			auto tmpdata = m_data;
			m_data = other.m_data;
			other.m_data = tmpdata;

			auto tmpcapacity = m_capacity;
			m_capacity = other.m_capacity;
			other.m_capacity = tmpcapacity;

			auto tmpsize = m_size;
			m_size = other.m_size;
			other.m_size = tmpsize;
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
