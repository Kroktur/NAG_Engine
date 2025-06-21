#pragma once
namespace NAG
{
	namespace Math
	{
		template<typename type>
		class ReverseIterator
		{
		public:
			using value_type = type;
			using pointer_type = type*;
			using reference_type = type&;
			using difference_type = std::ptrdiff_t;
			using Iterator_type = int;
			ReverseIterator(pointer_type);
			ReverseIterator(const ReverseIterator&);
			ReverseIterator();
			reference_type operator*();
			reference_type operator*() const;
			pointer_type operator->();
			pointer_type operator->() const;
			ReverseIterator& operator++();
			ReverseIterator& operator--();
			ReverseIterator operator++(int);
			ReverseIterator operator--(int);
			bool operator==(const ReverseIterator&) const;
			bool operator!=(const ReverseIterator&) const;
			bool operator>(const ReverseIterator&) const;
			bool operator<(const ReverseIterator&) const;
			bool operator>=(const ReverseIterator&) const;
			bool operator<=(const ReverseIterator&) const;
			ReverseIterator& operator=(const ReverseIterator&);
			ReverseIterator operator+(const difference_type&);
			ReverseIterator operator+(const difference_type&) const;
			ReverseIterator operator-(const difference_type&);
			ReverseIterator operator-(const difference_type&) const;
			ReverseIterator& operator+=(const difference_type&);
			ReverseIterator& operator-=(const difference_type&);
			difference_type operator-(const ReverseIterator&);
			difference_type operator-(const ReverseIterator&) const;
		private:
			pointer_type m_data;
		};

		template <typename type>
		ReverseIterator<type>::ReverseIterator(pointer_type data) :m_data(data)
		{
		}

		template <typename type>
		ReverseIterator<type>::ReverseIterator(const ReverseIterator& it) : m_data(it.m_data)
		{
		}

		template <typename type>
		ReverseIterator<type>::ReverseIterator():m_data(nullptr)
		{
		}

		template <typename type>
		typename ReverseIterator<type>::reference_type ReverseIterator<type>::operator*()
		{
			return *m_data;
		}

		template <typename type>
		typename ReverseIterator<type>::reference_type ReverseIterator<type>::operator*() const
		{
			return *m_data;
		}

		template <typename type>
		typename ReverseIterator<type>::pointer_type ReverseIterator<type>::operator->()
		{
			return m_data;
		}

		template <typename type>
		typename ReverseIterator<type>::pointer_type ReverseIterator<type>::operator->() const
		{
			return m_data;
		}

		template <typename type>
		ReverseIterator<type>& ReverseIterator<type>::operator++()
		{
			--m_data;
			return *this;
		}

		template <typename type>
		ReverseIterator<type>& ReverseIterator<type>::operator--()
		{
			++m_data;
			return *this;
		}

		template <typename type>
		ReverseIterator<type> ReverseIterator<type>::operator++(int)
		{
			ReverseIterator tmp = *this;
			++(*this);
			return tmp;
		}

		template <typename type>
		ReverseIterator<type> ReverseIterator<type>::operator--(int)
		{
			ReverseIterator tmp = *this;
			--(*this);
			return tmp;
		}

		template <typename type>
		bool ReverseIterator<type>::operator==(const ReverseIterator& it) const
		{
			return m_data == it.m_data;

		}

		template <typename type>
		bool ReverseIterator<type>::operator!=(const ReverseIterator& it) const
		{
			return m_data != it.m_data;

		}

		template <typename type>
		bool ReverseIterator<type>::operator>(const ReverseIterator& it) const
		{
			return m_data < it.m_data;

		}

		template <typename type>
		bool ReverseIterator<type>::operator<(const ReverseIterator& it) const
		{
			return m_data > it.m_data;
		}

		template <typename type>
		bool ReverseIterator<type>::operator>=(const ReverseIterator& it) const
		{
			return m_data <= it.m_data;
		}

		template <typename type>
		bool ReverseIterator<type>::operator<=(const ReverseIterator& it) const
		{
			return m_data >= it.m_data;
		}

		template <typename type>
		ReverseIterator<type>& ReverseIterator<type>::operator=(const ReverseIterator& it)
		{
			m_data = it.m_data;
			return *this;
		}

		template <typename type>
		ReverseIterator<type> ReverseIterator<type>::operator+(const difference_type& index)
		{
			return ReverseIterator(m_data - index);
		}

		template <typename type>
		ReverseIterator<type> ReverseIterator<type>::operator+(const difference_type& index) const
		{
			return ReverseIterator(m_data - index);
		}

		template <typename type>
		ReverseIterator<type> ReverseIterator<type>::operator-(const difference_type& index)
		{
			return ReverseIterator(m_data + index);
		}

		template <typename type>
		ReverseIterator<type> ReverseIterator<type>::operator-(const difference_type& index) const
		{
			return ReverseIterator(m_data + index);
		}

		template <typename type>
		ReverseIterator<type>& ReverseIterator<type>::operator+=(const difference_type& index)
		{
			m_data -= index;
			return *this;
		}

		template <typename type>
		ReverseIterator<type>& ReverseIterator<type>::operator-=(const difference_type& index)
		{
			m_data += index;
			return *this;
		}

		template <typename type>
		typename ReverseIterator<type>::difference_type ReverseIterator<type>::operator-(const ReverseIterator& it)
		{
			return std::ptrdiff_t(m_data - it.m_data);
		}

		template <typename type>
		typename ReverseIterator<type>::difference_type ReverseIterator<type>::operator-(const ReverseIterator& it) const
		{
			return std::ptrdiff_t( m_data - it.m_data);
		}
template<typename type>
class ConstReverseIterator
{
public:
	using value_type = const type;
	using pointer_type = const type*;
	using reference_type = const type&;
	using difference_type = std::ptrdiff_t;
	using Iterator_type = int;
	ConstReverseIterator(pointer_type);
	ConstReverseIterator(const ConstReverseIterator&);
	ConstReverseIterator();
	reference_type operator*();
	reference_type operator*() const;
	pointer_type operator->();
	pointer_type operator->() const;
	ConstReverseIterator& operator++();
	ConstReverseIterator& operator--();
	ConstReverseIterator operator++(int);
	ConstReverseIterator operator--(int);
	bool operator==(const ConstReverseIterator&) const;
	bool operator!=(const ConstReverseIterator&) const;
	bool operator>(const ConstReverseIterator&) const;
	bool operator<(const ConstReverseIterator&) const;
	bool operator>=(const ConstReverseIterator&) const;
	bool operator<=(const ConstReverseIterator&) const;
	ConstReverseIterator& operator=(const ConstReverseIterator&);
	ConstReverseIterator operator+(const difference_type&);
	ConstReverseIterator operator+(const difference_type&) const;
	ConstReverseIterator operator-(const difference_type&);
	ConstReverseIterator operator-(const difference_type&) const;
	ConstReverseIterator& operator+=(const difference_type&);
	ConstReverseIterator& operator-=(const difference_type&);
	difference_type operator-(const ConstReverseIterator&);
	difference_type operator-(const ConstReverseIterator&) const;
private:
	pointer_type m_data;
};

template <typename type>
ConstReverseIterator<type>::ConstReverseIterator(pointer_type data) :m_data(data)
{
}

template <typename type>
ConstReverseIterator<type>::ConstReverseIterator(const ConstReverseIterator& it) : m_data(it.m_data)
{
}

template <typename type>
ConstReverseIterator<type>::ConstReverseIterator() : m_data(nullptr)
{
}

template <typename type>
typename ConstReverseIterator<type>::reference_type ConstReverseIterator<type>::operator*()
{
	return *m_data;
}

template <typename type>
typename ConstReverseIterator<type>::reference_type ConstReverseIterator<type>::operator*() const
{
	return *m_data;
}

template <typename type>
typename ConstReverseIterator<type>::pointer_type ConstReverseIterator<type>::operator->()
{
	return m_data;
}

template <typename type>
typename ConstReverseIterator<type>::pointer_type ConstReverseIterator<type>::operator->() const
{
	return m_data;
}

template <typename type>
ConstReverseIterator<type>& ConstReverseIterator<type>::operator++()
{
	--m_data;
	return *this;
}

template <typename type>
ConstReverseIterator<type>& ConstReverseIterator<type>::operator--()
{
	++m_data;
	return *this;
}

template <typename type>
ConstReverseIterator<type> ConstReverseIterator<type>::operator++(int)
{
	ConstReverseIterator tmp = *this;
	++(*this);
	return tmp;
}

template <typename type>
ConstReverseIterator<type> ConstReverseIterator<type>::operator--(int)
{
	ConstReverseIterator tmp = *this;
	--(*this);
	return tmp;
}

template <typename type>
bool ConstReverseIterator<type>::operator==(const ConstReverseIterator& it) const
{
	return m_data == it.m_data;

}

template <typename type>
bool ConstReverseIterator<type>::operator!=(const ConstReverseIterator& it) const
{
	return m_data != it.m_data;

}

template <typename type>
bool ConstReverseIterator<type>::operator>(const ConstReverseIterator& it) const
{
	return m_data < it.m_data;

}

template <typename type>
bool ConstReverseIterator<type>::operator<(const ConstReverseIterator& it) const
{
	return m_data > it.m_data;
}

template <typename type>
bool ConstReverseIterator<type>::operator>=(const ConstReverseIterator& it) const
{
	return m_data <= it.m_data;
}

template <typename type>
bool ConstReverseIterator<type>::operator<=(const ConstReverseIterator& it) const
{
	return m_data >= it.m_data;
}

template <typename type>
ConstReverseIterator<type>& ConstReverseIterator<type>::operator=(const ConstReverseIterator& it)
{
	m_data = it.m_data;
	return *this;
}

template <typename type>
ConstReverseIterator<type> ConstReverseIterator<type>::operator+(const difference_type& index)
{
	return ConstReverseIterator(m_data - index);
}

template <typename type>
ConstReverseIterator<type> ConstReverseIterator<type>::operator+(const difference_type& index) const
{
	return ConstReverseIterator(m_data - index);
}

template <typename type>
ConstReverseIterator<type> ConstReverseIterator<type>::operator-(const difference_type& index)
{
	return ConstReverseIterator(m_data + index);
}

template <typename type>
ConstReverseIterator<type> ConstReverseIterator<type>::operator-(const difference_type& index) const
{
	return ConstReverseIterator(m_data + index);
}

template <typename type>
ConstReverseIterator<type>& ConstReverseIterator<type>::operator+=(const difference_type& index)
{
	m_data -= index;
	return *this;
}

template <typename type>
ConstReverseIterator<type>& ConstReverseIterator<type>::operator-=(const difference_type& index)
{
	m_data += index;
	return *this;
}

template <typename type>
typename ConstReverseIterator<type>::difference_type ConstReverseIterator<type>::operator-(const ConstReverseIterator& it)
{
	return std::ptrdiff_t(m_data - it.m_data);
}

template <typename type>
typename ConstReverseIterator<type>::difference_type ConstReverseIterator<type>::operator-(const ConstReverseIterator& it) const
{
	return std::ptrdiff_t(m_data - it.m_data);
}

	}
}
