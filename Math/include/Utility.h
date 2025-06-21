#pragma once

namespace NAG
{
	namespace Category
	{
		template<typename type>
		concept Acces_Memory_Category = requires(type t)
		{
			{ t.Begin() };
			{ t.End() };
		};

		template<typename type>
		concept Container_Category = requires(type t,size_t idx)
		{
			{t.Size() };
			{ t[idx] };
		};

		template<typename type>
		concept Iterator_Category = requires()
		{
			typename type::Iterator_type;
		};

	}
	namespace Algorithm
	{
		template<typename typepointer,typename type>
		void Fill(const typepointer& begin , const typepointer& end,const type& data)
		{
			for (auto it = begin; it != end ; ++it)
			{
				*it = data;
			}
		}

		template<typename typepointer, typename container>
		void Copy(const typepointer& begin, const typepointer& end, const container& dest)
		{
			auto curent = dest;
			for (auto it = begin; it != end; ++it , ++curent)
			{
				*curent = *it;
			}
		}

		template<typename typepointer, typename type>
		typepointer Find(const typepointer& begin,const typepointer& end, const type& data)
		{
			for (auto it = begin ; it != end; ++it)
			{
				if (*it == data)
					return it;
			}
			return end;
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
		template<typename type>
		bool IsEqual(const type& lhs,const type& rhs,const type& epsilon = 1.19209e-07f)
		{
			auto result = NAG::Algorithm::Max(lhs - rhs, rhs - lhs);
			if (result <= epsilon)
				return true;
			return false;
		}
	}
}