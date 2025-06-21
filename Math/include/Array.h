#pragma once
#include <stdexcept>
#include "RevIterator.h"
#include "Iterator.h"
#include "Utility.h"
namespace NAG
{
	namespace Math
	{
		template<typename type, size_t size>
		class Array
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using const_pointer_type = const type*;
			using reference_type = type&;
			using const_reference_type = const type&;
			using difference_type = std::ptrdiff_t;
			using iterator_type = NAG::Math::Iterator<type>;
			using reverse_iterator_type = NAG::Math::ReverseIterator<type>;
			using const_iterator_type = NAG::Math::ConstIterator<type>;
			using const_reverse_iterator_type = NAG::Math::ConstReverseIterator<type>;

			Array();
			Array(const Array&);
			Array(const std::initializer_list<value_type>&);
			template<typename... Args>
			Array(const Args&...);
			virtual ~Array();
			void Clear();
			Array& operator=(const Array&);
			bool operator==(const Array&) const;
			bool operator!=(const Array&) const;
			size_t Size() const;
			size_t MaxLimit() const;
			bool IsEmpty()const;
			reference_type operator[](const size_t&);
			reference_type At(const size_t&);
			const_reference_type operator[](const size_t&) const;
			const_reference_type At(const size_t&)const;
			reference_type Front();
			reference_type Back();
			const_reference_type Front() const;
			const_reference_type Back() const;
			pointer_type Data();
			const_pointer_type Data() const;
			iterator_type Begin();
			iterator_type End();
			const_iterator_type Begin()const;
			const_iterator_type End()const;
			const_iterator_type CBegin() const;
			const_iterator_type CEnd() const;
			reverse_iterator_type RBegin();
			reverse_iterator_type REnd();
			const_reverse_iterator_type RBegin() const;
			const_reverse_iterator_type REnd() const;
			const_reverse_iterator_type CRBegin() const;
			const_reverse_iterator_type CREnd() const;
			void Assign(const size_t&, const value_type&);
			void Assign(const std::initializer_list<value_type>&);
			template<NAG::Category::Iterator_Category IT>
			void Assign(const IT&, const IT&);
			void Swap(Array&);
			
		private:
			template<typename T, typename... Rest>
			void ConstructElements(const size_t& index, const T& first, const Rest&... rest);
			template<typename T>
			void ConstructElements(const size_t& index, const T& last);
			void ConstructData();
			type* m_data;
		};

		template <typename type, size_t size>
		Array<type, size>::Array():m_data(nullptr)
		{
			ConstructData();
			NAG::Algorithm::Fill(m_data, m_data + size, type{});
		}

		template <typename type, size_t size>
		Array<type, size>::Array(const Array& other):m_data(nullptr)
		{
			ConstructData();
			NAG::Algorithm::Copy(other.Begin(), other.End(), m_data);
		}

		template <typename type, size_t size>
		Array<type, size>::Array(const std::initializer_list<value_type>& list):m_data(nullptr)
		{
			ConstructData();
			if (list.size() > size)
				throw std::out_of_range("size is to big");

			NAG::Algorithm::Copy(list.begin(), list.end(), m_data);
			NAG::Algorithm::Fill(m_data + list.size() , m_data + size, type{});
		}

		template <typename type, size_t size>
		template <typename ... Args>
		Array<type, size>::Array(const Args&... arg):m_data(nullptr)
		{
			ConstructData();
			ConstructElements(0, arg...);
		}

		template <typename type, size_t size>
		Array<type, size>::~Array()
		{
			delete[] m_data;
			m_data = nullptr;
		}

		template <typename type, size_t size>
		void Array<type, size>::Clear()
		{
			delete[] m_data;
			m_data = nullptr;
			ConstructData();
			NAG::Algorithm::Fill(m_data, m_data + size, type{});
		}

		template <typename type, size_t size>
		Array<type,size>& Array<type, size>::operator=(const Array& other)
		{
			if (this == &other)
				return *this;

			NAG::Algorithm::Copy(other.Begin(), other.End(), m_data);
			return *this;
		}

		template <typename type, size_t size>
		bool Array<type, size>::operator==(const Array& other) const
		{
			if (size != other.Size())
				return false;
			for (std::make_signed_t<size_t> i = 0; i < size; ++i)
			{
				if (m_data[i] != other[i])
					return false;
			}
			return true;
		}

		template <typename type, size_t size>
		bool Array<type, size>::operator!=(const Array& other) const
		{
			if (size != other.Size())
				return true;
			for (std::make_signed_t<size_t> i = 0; i < size; ++i)
			{
				if (m_data[i] != other[i])
					return true;
			}
			return false;
		}

		template <typename type, size_t size>
		size_t Array<type, size>::Size() const
		{
			return  size;
		}

		template <typename type, size_t size>
		size_t Array<type, size>::MaxLimit() const
		{
			return size;
		}

		template <typename type, size_t size>
		bool Array<type, size>::IsEmpty() const
		{
			return size == 0;
		}

		template <typename type, size_t size>
		typename Array<type, size>::reference_type Array<type, size>::operator[](const size_t& index)
		{
			return m_data[index];
		}

		template <typename type, size_t size>
		typename Array<type, size>::reference_type Array<type, size>::At(const size_t& index)
		{
			if (index >= size)
				throw std::out_of_range("out of range");
			return m_data[index];
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reference_type Array<type, size>::operator[](const size_t& index) const
		{
			return m_data[index];
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reference_type Array<type, size>::At(const size_t& index) const
		{
			if (index >= size)
				throw std::out_of_range("out of range");
			return m_data[index];
		}

		template <typename type, size_t size>
		typename Array<type, size>::reference_type Array<type, size>::Front()
		{
			if (IsEmpty())
				throw std::out_of_range("array is empty");
			return m_data[0];
		}

		template <typename type, size_t size>
		typename Array<type, size>::reference_type Array<type, size>::Back()
		{
			if (IsEmpty())
				throw std::out_of_range("array is empty");
			return m_data[size - 1];
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reference_type Array<type, size>::Front() const
		{
			if (IsEmpty())
				throw std::out_of_range("array is empty");
			return m_data[0];
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reference_type Array<type, size>::Back() const
		{
			if (IsEmpty())
				throw std::out_of_range("array is empty");
			return m_data[size - 1];
		}

		template <typename type, size_t size>
		typename Array<type, size>::pointer_type Array<type, size>::Data()
		{
			if (IsEmpty())
				return nullptr;
			return m_data;
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_pointer_type Array<type, size>::Data() const
		{
			if (IsEmpty())
				return nullptr;
			return m_data;
		}

		template <typename type, size_t size>
		typename Array<type, size>::iterator_type Array<type, size>::Begin()
		{
			if (IsEmpty())
				return Iterator<type>{};
			return Iterator<type>(m_data);
		}

		template <typename type, size_t size>
		typename Array<type, size>::iterator_type Array<type, size>::End()
		{
			if (IsEmpty())
				return Iterator<type>{};
			return Iterator<type>(m_data + size);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_iterator_type Array<type, size>::Begin() const
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data);

		}

		template <typename type, size_t size>
		typename Array<type, size>::const_iterator_type Array<type, size>::End() const
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data + size);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_iterator_type Array<type, size>::CBegin() const
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_iterator_type Array<type, size>::CEnd() const
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data + size);
		}

		template <typename type, size_t size>
		typename Array<type, size>::reverse_iterator_type Array<type, size>::RBegin()
		{
			if (IsEmpty())
				return ReverseIterator<type>{};
			return ReverseIterator<type>(m_data + size - 1);
		}

		template <typename type, size_t size>
		typename Array<type, size>::reverse_iterator_type Array<type, size>::REnd()
		{
			if (IsEmpty())
				return ReverseIterator<type>{};
			return ReverseIterator<type>(m_data  - 1);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reverse_iterator_type Array<type, size>::RBegin() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data + size - 1);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reverse_iterator_type Array<type, size>::REnd() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data - 1);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reverse_iterator_type Array<type, size>::CRBegin() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data + size - 1);
		}

		template <typename type, size_t size>
		typename Array<type, size>::const_reverse_iterator_type Array<type, size>::CREnd() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data - 1);
		}

		template <typename type, size_t size>
		void Array<type, size>::Assign(const size_t& sizeofvalue, const value_type& data)
		{
			Clear();
			if (sizeofvalue > size)
				throw std::out_of_range("out of range");
			NAG::Algorithm::Fill(m_data, m_data + sizeofvalue, data);
			NAG::Algorithm::Fill(m_data + sizeofvalue, m_data + size, type{});
		}

		template <typename type, size_t size>
		void Array<type, size>::Assign(const std::initializer_list<value_type>& list)
		{
			Clear();
			if (list.size() > size)
				throw std::out_of_range("out of range");
			NAG::Algorithm::Copy(list.begin(), list.end(),m_data);
			NAG::Algorithm::Fill(m_data + list.size(), m_data + size, type{});
		}

		template <typename type, size_t size>
		template <NAG::Category::Iterator_Category IT>
		void Array<type, size>::Assign(const IT& begin, const IT& end)
		{
			Clear();
			auto sizediff = NAG::Algorithm::Max(end - begin, begin - end);
			if (sizediff > size)
				throw std::out_of_range("out of range");
			for (auto i = 0; i < sizediff; ++i)
			{
				m_data[i] = *(begin + i);
			}
			NAG::Algorithm::Fill(m_data + sizediff, m_data + size, type{});
		}

		template <typename type, size_t size>
		void Array<type, size>::Swap(Array& other)
		{
			auto tmpdata = m_data;
			m_data = other.m_data;
			other.m_data = tmpdata;
		}


		template <typename type, size_t size>
		template <typename T, typename ... Rest>
		void Array<type, size>::ConstructElements(const size_t& index, const T& first, const Rest&... rest)
		{
			if (index >= size)
				throw std::out_of_range("out of range");
			m_data[index] = first;
			ConstructElements(index + 1 , rest...);
			
		}

		template <typename type, size_t size>
		template <typename T>
		void Array<type, size>::ConstructElements(const size_t& index, const T& last)
		{
			if (index >= size)
				throw std::out_of_range("out of range");
			m_data[index] = last;
		}

		template <typename type, size_t size>
		void Array<type, size>::ConstructData()
		{
			if (m_data)
				return;
			m_data = new type[size];
		}
	}
}
template<typename type,size_t size>
std::ostream& operator<<(std::ostream& os, const NAG::Math::Array < type,size >& array )
{
	os << "Arr: ";
	if (size == 0)
		return os << "[ ]" << std::endl;
	os << "[";
	for (auto i = 0 ; i < size - 1 ; ++i)
	{
		os << array.At(i)<<",";
	}
	os << array.At(size - 1) << "]" << std::endl;
	return os;
}