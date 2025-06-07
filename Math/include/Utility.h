#pragma once
namespace NAG
{
	namespace Category
	{
		template<typename type>
		concept Container_Category = requires(type t)
		{
			{ t.Begin() };
			{ t.End() };
		};

		template<typename type>
		concept Iterator_Category = requires()
		{
			typename type::Iterator_type;
		};

	}
	namespace Algorithm
	{
		template<Category::Iterator_Category IT,typename type>
		void Fill(const IT& begin , const IT& end,const type& data)
		{
			for (auto it = begin; it != end ; ++it)
			{
				*it = data;
			}
		}

		template<Category::Iterator_Category IT, typename container>
		void Copy(const IT& begin, const IT& end, const container& dest)
		{
			auto curent = dest;
			for (auto it = begin; it != end; ++it , ++curent)
			{
				*curent = *it;
			}
		}

		template<typename type>
		type Min(const type& lhs, const type& rhs)
		{
			if (lhs < rhs)
				return lhs;
			return rhs;
		}
		template<typename type>
		type Max(const type& lhs, const type& rhs)
		{
			if (lhs > rhs)
				return lhs;
			return rhs;
		}
		template<typename type>
		void Swap(type& lhs, type& rhs)
		{
			auto tmp = lhs;
			lhs = rhs;
			rhs = tmp;
		} 
	}
}
