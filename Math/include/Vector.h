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
			using const_reverse_iterator_type = NAG::Math::ConstReverseIterator<type>;

			Vector();
			Vector(const Vector&);
			Vector(const std::initializer_list<value_type>&);
			template<typename... Args>
			Vector(const Args&...);
			~Vector();
			void Resize(const size_t&);
			void Reserve(const size_t&);
			void Clear();
			Vector& operator=(const  Vector&);
			bool operator==(const Vector&) const;
			bool operator!=(const Vector&) const;
			size_t Size() const;
			size_t Capacity() const;
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
			const_iterator_type Begin() const;
			const_iterator_type End() const;
			const_iterator_type CBegin() const;
			const_iterator_type CEnd() const;
			reverse_iterator_type RBegin();
			reverse_iterator_type REnd();
			const_reverse_iterator_type RBegin() const;
			const_reverse_iterator_type REnd()const;
			const_reverse_iterator_type CRBegin() const;
			const_reverse_iterator_type CREnd() const;
			void PushBack(const value_type&);
			void PopBack();
			void Assign(const size_t&, const value_type&);
			void Assign(const std::initializer_list<value_type>&);
			template<NAG::Category::Iterator_Category IT>
			void Assign(const IT&, const IT&);
			template<NAG::Category::Iterator_Category IT>
			void Insert(const IT&, const value_type&);
			template<NAG::Category::Iterator_Category IT>
			void Insert(const IT&,const size_t&, const value_type&);
			template<NAG::Category::Iterator_Category IT>
			void Insert(const IT&,const std::initializer_list<value_type>&);
			template<NAG::Category::Iterator_Category IT, NAG::Category::Iterator_Category IT2>
			void Insert(const IT&, const IT2&, const IT2&);
			template<NAG::Category::Iterator_Category IT>
			void Erase(const IT&);
			template<NAG::Category::Iterator_Category IT>
			void Erase(const IT&, const IT&);
			template<NAG::Category::Iterator_Category IT>
			void Erase(const IT&,const size_t& size);
			template<NAG::Category::Acces_Memory_Category container>
			void AppendRange(const container&);
			template<NAG::Category::Iterator_Category IT,NAG::Category::Acces_Memory_Category container>
			void InsertRange(const IT&,const container&);
			template<NAG::Category::Acces_Memory_Category container>
			void AssignRange(const container&);
			void Swap(Vector&);

		private:
			template<typename T, typename... Rest>
			void ConstructElements(const size_t& index,  const T& first, const Rest&... rest);

			template<typename T>
			void ConstructElements(const size_t& index, const T& last);

			type* m_data;
			size_t m_size;
			size_t m_capacity;
		};

	

		template <typename type>
		Vector<type>::Vector():m_size(0),m_capacity(0),m_data(nullptr)
		{
		}

		template <typename type>
		Vector<type>::Vector( const Vector& other):m_size(0),m_capacity(0),m_data(nullptr)
		{
			Reserve(other.Capacity());
			Resize(other.Size());
			NAG::Algorithm::Copy(other.Begin(), other.End(), m_data);
		}

		template <typename type>
		Vector<type>::Vector(const std::initializer_list<type>& list) :m_size(0),m_capacity(0),m_data(nullptr)
		{
			Resize(list.size());
			std::copy(list.begin(), list.end(), m_data);
		}

		template <typename type>
		template <typename ... Args>
		Vector<type>::Vector(const Args&... args):m_size(0),m_capacity(0),m_data(nullptr)
		{
			Resize(sizeof...(Args));
			ConstructElements(0,args...);
		}

		template <typename type>
		Vector<type>::~Vector()
		{
			Clear();
			if (m_data)
			{
				delete[]m_data;
				m_data = nullptr;
			}
		}

		template <typename type>
		void Vector<type>::Resize(const size_t& size)
		{
			if (size > m_capacity)
			{
				size_t nextsize = NAG::Algorithm::Min(size * 2,MaxLimit());
				Reserve(nextsize);
			}
			m_size = size;
		}

		template <typename type>
		void Vector<type>::Reserve(const size_t& capacity)
		{
			if (capacity == m_capacity)
				return;
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
		typename Vector<type>::reference_type Vector<type>::At(const size_t& index)
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
		typename Vector<type>::const_reference_type Vector<type>::At(const size_t& index) const
		{
			if (index > m_size - 1)
				throw std::out_of_range(" index is too big");
			return m_data[index];
		}

		template <typename type>
		typename Vector<type>::reference_type Vector<type>::Front()
		{
			if (IsEmpty())
				throw std::out_of_range("Vector is empty");
			return m_data[0];
		}

		template <typename type>
		typename Vector<type>::reference_type Vector<type>::Back()
		{
			if (IsEmpty())
				throw std::out_of_range("Vector is empty");
			return m_data[m_size - 1];
		}

		template <typename type>
		typename Vector<type>::const_reference_type Vector<type>::Front() const
		{
			if (IsEmpty())
				throw std::out_of_range("Vector is empty");
			return m_data[0];
		}

		template <typename type>
		typename Vector<type>::const_reference_type Vector<type>::Back() const
		{
			if (IsEmpty())
				throw std::out_of_range("Vector is empty");
			return m_data[m_size - 1];
		}

		template <typename type>
		typename Vector<type>::pointer_type Vector<type>::Data()
		{
			if (IsEmpty())
				return nullptr;
			return m_data;
		}

		template <typename type>
		typename Vector<type>::const_pointer_type Vector<type>::Data() const
		{
			if (IsEmpty())
				return nullptr;
			return m_data;
		}

		template <typename type>
		void Vector<type>::Clear()
		{
			Resize(0);
			Reserve(0);
		}

		template <typename type>
		Vector<type>& Vector<type>::operator=(const Vector& other)
		{
			if (this == &other)
				return *this;

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
		typename Vector<type>::const_iterator_type Vector<type>::Begin() const
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data);
		}

		template <typename type>
		typename Vector<type>::const_iterator_type Vector<type>::End() const
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data + m_size);
		}

		template <typename type>
		typename Vector<type>::const_iterator_type Vector<type>::CBegin() const 
		{
			if (IsEmpty())
				return ConstIterator<type>{};
			return ConstIterator<type>(m_data);
		}

		template <typename type>
		typename Vector<type>::const_iterator_type Vector<type>::CEnd() const 
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
		typename Vector<type>::const_reverse_iterator_type Vector<type>::RBegin() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data + m_size - 1);
		}

		template <typename type>
		typename Vector<type>::const_reverse_iterator_type Vector<type>::REnd() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data - 1);
		}

		template <typename type>
		typename Vector<type>::const_reverse_iterator_type Vector<type>::CRBegin() const
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data + m_size - 1);
		}

		template <typename type>
		typename Vector<type>::const_reverse_iterator_type Vector<type>::CREnd() const 
		{
			if (IsEmpty())
				return ConstReverseIterator<type>{};
			return ConstReverseIterator<type>(m_data - 1);
		}

		template <typename type>
		void Vector<type>::PushBack(const value_type& value)
		{
			Resize(m_size + 1);
			m_data[m_size - 1] = value;
		}

		template <typename type>
		void Vector<type>::PopBack()
		{
			if (IsEmpty())
				return;
			m_data[m_size - 1] = type{};
			Resize(m_size - 1);
		}

		template <typename type>
		void Vector<type>::Assign(const size_t& count, const value_type& data)
		{
			Clear();
			Resize(count);
			NAG::Algorithm::Fill(m_data, m_data + m_size,data);
		}

		template <typename type>
		void Vector<type>::Assign(const std::initializer_list<value_type>& list)
		{
			Clear();
			Resize(list.size());
			NAG::Algorithm::Copy(list.begin(), list.end(), m_data);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Assign(const IT& begin, const IT& end)
		{
			Clear();
			auto size = NAG::Algorithm::Max(end - begin, begin - end);
			Resize(size);
			for (auto i = 0 ; i< size ; ++i)
			{
				m_data[i] = *(begin + i);
			}
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Insert(const IT& it, const value_type& data)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr > End().operator->())
				throw std::out_of_range("Iterator is invalid");

			size_t offset = ptr - m_data;
			Resize(m_size + 1);


			auto start = End() - 1;
			auto stop = Begin() + offset;
			auto newptr = Begin() + offset;

			for (auto curent_it = start; curent_it != stop; --curent_it)
			{
				*curent_it = *(curent_it - 1);
			}
			*newptr = data;
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Insert(const IT& it, const size_t& count, const value_type& data)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr > End().operator->())
				throw std::out_of_range("Iterator is invalid");
			size_t offset = ptr - m_data;
			Resize(m_size + count);

			auto start = End() - 1;
			auto stop = Begin() + offset + count - 1;
			auto newptr = Begin() + offset;

			for (auto curent_it = start; curent_it != stop; --curent_it)
			{
				*curent_it = *(curent_it - count);
			}
			for (auto curent_it = newptr; curent_it < newptr + count; ++curent_it)
			{
				*curent_it = data;
			}
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Insert(const IT& it, const std::initializer_list<value_type>& list)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr > End().operator->())
				throw std::out_of_range("Iterator is invalid");
			size_t offset = ptr - m_data;
			size_t count = list.size();
			Resize(m_size + count);

			auto start = End() - 1;
			auto stop = Begin() + offset + count - 1;
			auto newptr = Begin() + offset;

			for (auto curent_it = start; curent_it != stop; --curent_it)
			{
				*curent_it = *(curent_it - count);
			}
			NAG::Algorithm::Copy(list.begin(), list.end(), newptr);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT, NAG::Category::Iterator_Category IT2>
		void Vector<type>::Insert(const IT& it, const IT2& begin, const IT2& end)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr > End().operator->())
				throw std::out_of_range("Iterator is invalid");
			size_t offset = ptr - m_data;
			auto count = NAG::Algorithm::Max(end - begin, begin - end);
			Resize(m_size + count);

			auto start = End() - 1;
			auto stop = Begin() + offset + count - 1;
			auto newptr = Begin() + offset;
			for (auto curent_it = start; curent_it != stop; --curent_it)
			{
				*curent_it = *(curent_it - count);
			}
			NAG::Algorithm::Copy(begin, end, newptr);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Erase(const IT& it)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr >= End().operator->())
				throw std::out_of_range("Iterator is invalid");
			size_t offset = ptr - m_data;
			auto newptr = Begin() + offset;
			auto stop = End() - 1;
			for (auto current_it = newptr; current_it != stop; ++current_it)
			{
				*current_it = *(current_it + 1);
			}
			Resize(m_size - 1);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT>
		void Vector<type>::Erase(const IT& begin, const IT& end)
		{
			auto ptr = begin.operator->();
			auto ptr2 = end.operator->();
			if (ptr < Begin().operator->() || ptr >= End().operator->() || ptr2 < Begin().operator->() || ptr2 >= End().operator->())
				throw std::out_of_range("Iterator is invalid");

			auto count = NAG::Algorithm::Max(end - begin, begin - end);
			auto startptr = NAG::Algorithm::Min(ptr, ptr2);
			auto ofset = startptr - m_data;
			auto newptr = Begin() + ofset;
			auto stop = Begin() + ofset + count - 1;
			for (auto current_it = newptr; current_it != stop; ++current_it)
			{
				*current_it = *(current_it + count);
			}
			Resize(m_size - count);
		}

		template <typename type>
		template<NAG::Category::Iterator_Category IT>
		void Vector<type>::Erase(const IT& it, const size_t& size)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr >= End().operator->() || ptr + size >= m_data + m_size)
				throw std::out_of_range("Iterator is invalid");

			auto ofset = ptr - m_data;
			auto newptr = Begin() + ofset;
			auto stop = Begin() + ofset + size - 1;
			for (auto current_it = newptr; current_it != stop; ++current_it)
			{
				*current_it = *(current_it + size);
			}
			Resize(m_size - size);
		}

		template <typename type>
		template <NAG::Category::Acces_Memory_Category container >
		void Vector<type>::AppendRange(const container& contain)
		{
			auto lastsize = m_size;
			auto ofset = contain.End() - contain.Begin();
			Resize(m_size + ofset);
			NAG::Algorithm::Copy(contain.Begin(), contain.End(), m_data + lastsize);
		}

		template <typename type>
		template <NAG::Category::Iterator_Category IT, NAG::Category::Acces_Memory_Category container>
		void Vector<type>::InsertRange(const IT& it, const container& contain)
		{
			auto ptr = it.operator->();
			if (ptr < Begin().operator->() || ptr > End().operator->())
				throw std::out_of_range("Iterator is invalid");
			size_t offset = ptr - m_data;
			size_t count = contain.End() - contain.Begin();
			Resize(m_size + count);

			auto start = End() - 1;
			auto stop = Begin() + offset + count - 1;
			auto newptr = Begin() + offset;

			for (auto curent_it = start; curent_it != stop; --curent_it)
			{
				*curent_it = *(curent_it - count);
			}
			NAG::Algorithm::Copy(contain.Begin(), contain.End(), newptr);
		}

		template <typename type>
		template <NAG::Category::Acces_Memory_Category container>
		void Vector<type>::AssignRange(const container& contain)
		{
			Clear();
			Resize((contain.End()- contain.Begin()));
			NAG::Algorithm::Copy(contain.Begin(), contain.End(), m_data);
		}

		template <typename type>
		void Vector<type>::Swap(Vector& other)
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
		void Vector<type>::ConstructElements(const size_t& index, const T& first, const Rest&... rest)
		{
			m_data[index] = first;
			ConstructElements(index + 1,rest...);
		}

		template <typename type>
		template <typename T>
		void Vector<type>::ConstructElements(const size_t& index, const T& last)
		{
			m_data[index] = last;
		}
	}
}
template<typename type>
std::ostream& operator<<(std::ostream& os, const NAG::Math::Vector< type>& vector)
{
	os << "Vec: ";
	if (vector.Size() == 0)
		return os << "[ ]" << std::endl;
	os << "[";
	for (auto i = 0; i < vector.Size() - 1; ++i)
	{
		os << vector.At(i) << ",";
	}
	os << vector.At(vector.Size() - 1) << "]" << std::endl;
	return os;
}