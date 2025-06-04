#pragma once
namespace KT
{
	namespace Math
	{
		template<typename type>
		class Iterator
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using reference_type = type&;
			using difference_type =std::ptrdiff_t;
			Iterator(pointer_type);
			Iterator(const Iterator&);
			Iterator();
			reference_type operator*();
			reference_type operator*() const;
			pointer_type operator->();
			pointer_type operator->() const;
			Iterator& operator++();
			Iterator& operator--();
			Iterator operator++(int);
			Iterator operator--(int);
			bool operator==(const Iterator&) const;
			bool operator!=(const Iterator&) const;
			bool operator>(const Iterator&) const;
			bool operator<(const Iterator&) const;
			bool operator>=(const Iterator&) const;
			bool operator<=(const Iterator&) const;
			Iterator& operator=(const Iterator&);
			Iterator operator+(const difference_type&);
			Iterator operator+(const difference_type&) const;
			Iterator operator-(const difference_type&) ;
			Iterator operator-(const difference_type&) const;
			Iterator& operator+=(const difference_type&);
			Iterator& operator-=(const difference_type&);
			difference_type operator-(const Iterator&);
			difference_type operator-(const Iterator&) const;
		private:
			pointer_type m_data;
		};

		template <typename type>
		Iterator<type>::Iterator(pointer_type data):m_data(data)
		{}

		template <typename type>
		Iterator<type>::Iterator(const Iterator& it):m_data(it.m_data)
		{
		}

		template <typename type>
		Iterator<type>::Iterator():m_data(nullptr)
		{
		}

		template <typename type>
		typename Iterator<type>::reference_type Iterator<type>::operator*()
		{
			return *m_data;
		}

		template <typename type>
		typename Iterator<type>::reference_type Iterator<type>::operator*() const
		{
			return *m_data;
		}

		template <typename type>
		typename Iterator<type>::pointer_type Iterator<type>::operator->()
		{
			return m_data;
		}

		template <typename type>
		typename Iterator<type>::pointer_type Iterator<type>::operator->() const
		{
			return m_data;
		}

		template <typename type>
		Iterator<type>& Iterator<type>::operator++()
		{
			++m_data;
			return *this;
		}

		template <typename type>
		Iterator<type>& Iterator<type>::operator--()
		{
			--m_data;
			return *this;
		}

		template <typename type>
		Iterator<type> Iterator<type>::operator++(int)
		{
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		template <typename type>
		Iterator<type> Iterator<type>::operator--(int)
		{
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}

		template <typename type>
		bool Iterator<type>::operator==(const Iterator& it) const
		{
			return m_data == it.m_data;
		
		}

		template <typename type>
		bool Iterator<type>::operator!=(const Iterator& it) const
		{
			return m_data != it.m_data;
			
		}

		template <typename type>
		bool Iterator<type>::operator>(const Iterator& it) const
		{
			return m_data > it.m_data;
		
		}

		template <typename type>
		bool Iterator<type>::operator<(const Iterator& it) const
		{
			return m_data < it.m_data;
		}

		template <typename type>
		bool Iterator<type>::operator>=(const Iterator& it) const
		{
			return m_data >= it.m_data;
		}

		template <typename type>
		bool Iterator<type>::operator<=(const Iterator& it) const
		{
			return m_data <= it.m_data;
		}

		template <typename type>
		Iterator<type>& Iterator<type>::operator=(const Iterator& it)
		{
			m_data = it.m_data;
			return *this;
		}

		template <typename type>
		Iterator<type> Iterator<type>::operator+(const difference_type& index)
		{
			return Iterator(m_data + index);
		}

		template <typename type>
		Iterator<type> Iterator<type>::operator+(const difference_type& index) const
		{
			return Iterator(m_data + index);
		}

		template <typename type>
		Iterator<type> Iterator<type>::operator-(const difference_type& index)
		{
			return Iterator(m_data - index);
		}

		template <typename type>
		Iterator<type> Iterator<type>::operator-(const difference_type& index) const
		{
			return Iterator(m_data - index);
		}

		template <typename type>
		Iterator<type>& Iterator<type>::operator+=(const difference_type& index)
		{
			m_data += index;
			return *this;
		}

		template <typename type>
		Iterator<type>& Iterator<type>::operator-=(const difference_type& index)
		{
			m_data -= index;
			return *this;
		}

		template <typename type>
		typename Iterator<type>::difference_type Iterator<type>::operator-(const Iterator& it)
		{
			return std::ptrdiff_t(m_data - it.m_data);
		}

		template <typename type>
		typename Iterator<type>::difference_type Iterator<type>::operator-(const Iterator& it) const
		{
			return std::ptrdiff_t(m_data - it.m_data);
		}
	template<typename type>
class ConstIterator
{
public:
	using value_type = const type;
	using pointer_type = const type*;
	using reference_type = const type&;
	using difference_type = std::ptrdiff_t;
	ConstIterator(pointer_type);
	ConstIterator(const ConstIterator&);
	ConstIterator();
	reference_type operator*();
	reference_type operator*() const;
	pointer_type operator->();
	pointer_type operator->() const;
	ConstIterator& operator++();
	ConstIterator& operator--();
	ConstIterator operator++(int);
	ConstIterator operator--(int);
	bool operator==(const ConstIterator&) const;
	bool operator!=(const ConstIterator&) const;
	bool operator>(const ConstIterator&) const;
	bool operator<(const ConstIterator&) const;
	bool operator>=(const ConstIterator&) const;
	bool operator<=(const ConstIterator&) const;
	ConstIterator& operator=(const ConstIterator&);
	ConstIterator operator+(const difference_type&);
	ConstIterator operator+(const difference_type&) const;
	ConstIterator operator-(const difference_type&);
	ConstIterator operator-(const difference_type&) const;
	ConstIterator& operator+=(const difference_type&);
	ConstIterator& operator-=(const difference_type&);
	difference_type operator-(const ConstIterator&);
	difference_type operator-(const ConstIterator&) const;
private:
	pointer_type m_data;
};

template <typename type>
ConstIterator<type>::ConstIterator(pointer_type data) :m_data(data)
{
}

template <typename type>
ConstIterator<type>::ConstIterator(const ConstIterator& it) : m_data(it.m_data)
{
}

template <typename type>
ConstIterator<type>::ConstIterator() : m_data(nullptr)
{
}

template <typename type>
typename ConstIterator<type>::reference_type ConstIterator<type>::operator*()
{
	return *m_data;
}

template <typename type>
typename ConstIterator<type>::reference_type ConstIterator<type>::operator*() const
{
	return *m_data;
}

template <typename type>
typename ConstIterator<type>::pointer_type ConstIterator<type>::operator->()
{
	return m_data;
}

template <typename type>
typename ConstIterator<type>::pointer_type ConstIterator<type>::operator->() const
{
	return m_data;
}

template <typename type>
ConstIterator<type>& ConstIterator<type>::operator++()
{
	++m_data;
	return *this;
}

template <typename type>
ConstIterator<type>& ConstIterator<type>::operator--()
{
	--m_data;
	return *this;
}

template <typename type>
ConstIterator<type> ConstIterator<type>::operator++(int)
{
	ConstIterator tmp = *this;
	++(*this);
	return tmp;
}

template <typename type>
ConstIterator<type> ConstIterator<type>::operator--(int)
{
	ConstIterator tmp = *this;
	--(*this);
	return tmp;
}

template <typename type>
bool ConstIterator<type>::operator==(const ConstIterator& it) const
{
	return m_data == it.m_data;

}

template <typename type>
bool ConstIterator<type>::operator!=(const ConstIterator& it) const
{
	return m_data != it.m_data;

}

template <typename type>
bool ConstIterator<type>::operator>(const ConstIterator& it) const
{
	return m_data > it.m_data;

}

template <typename type>
bool ConstIterator<type>::operator<(const ConstIterator& it) const
{
	return m_data < it.m_data;
}

template <typename type>
bool ConstIterator<type>::operator>=(const ConstIterator& it) const
{
	return m_data >= it.m_data;
}

template <typename type>
bool ConstIterator<type>::operator<=(const ConstIterator& it) const
{
	return m_data <= it.m_data;
}

template <typename type>
ConstIterator<type>& ConstIterator<type>::operator=(const ConstIterator& it)
{
	m_data = it.m_data;
	return *this;
}

template <typename type>
ConstIterator<type> ConstIterator<type>::operator+(const difference_type& index)
{
	return ConstIterator(m_data + index);
}

template <typename type>
ConstIterator<type> ConstIterator<type>::operator+(const difference_type& index) const
{
	return ConstIterator(m_data + index);
}

template <typename type>
ConstIterator<type> ConstIterator<type>::operator-(const difference_type& index)
{
	return ConstIterator(m_data - index);
}

template <typename type>
ConstIterator<type> ConstIterator<type>::operator-(const difference_type& index) const
{
	return Iterator(m_data - index);
}

template <typename type>
ConstIterator<type>& ConstIterator<type>::operator+=(const difference_type& index)
{
	m_data += index;
	return *this;
}

template <typename type>
ConstIterator<type>& ConstIterator<type>::operator-=(const difference_type& index)
{
	m_data -= index;
	return *this;
}

template <typename type>
typename ConstIterator<type>::difference_type ConstIterator<type>::operator-(const ConstIterator& it)
{
	return std::ptrdiff_t(m_data - it.m_data);
}

template <typename type>
typename ConstIterator<type>::difference_type ConstIterator<type>::operator-(const ConstIterator& it) const
{
	return std::ptrdiff_t(m_data - it.m_data);
}
	}
}
