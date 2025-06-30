#pragma once

namespace NAG
{
	namespace Math
	{
		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		class Pair
		{
		public:
			using left_value_type = lhstype;
			using right_value_type = rhstype;
			Pair();
			Pair(const Pair& other);
			Pair(const left_value_type& lhs, const right_value_type& rhs);
			template<Concept::DefaultConstructorType type, Concept::DefaultConstructorType type2>requires Concept::IsConvertible<lhstype,type> && Concept::IsConvertible<rhstype, type2>
			Pair(const type& lhs = type{}, const type2& rhs = type2{});
			Pair<rhstype, lhstype> SwapType();
			void Clear();
			lhstype lhsdata;
			rhstype rhsdata;
		};

		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		Pair<lhstype, rhstype>::Pair():lhsdata(lhstype{}),rhsdata(rhstype{})
		{
		}

		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		Pair<lhstype, rhstype>::Pair(const Pair& other) : lhsdata(other.lhsdata),rhsdata(other.rhsdata)
		{
		}

		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		Pair<lhstype, rhstype>::Pair(const lhstype& lhs, const rhstype& rhs) : lhsdata(lhs), rhsdata(rhs)
		{
		}

		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		template <Concept::DefaultConstructorType type, Concept::DefaultConstructorType type2>requires Concept::IsConvertible<lhstype, type>&& Concept::IsConvertible<rhstype, type2>
		Pair<lhstype, rhstype>::Pair(const type& lhs, const type2& rhs):lhsdata(static_cast<lhstype>(lhs)),rhsdata(static_cast<rhstype>(rhs))
		{
		}

		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		Pair<rhstype, lhstype> Pair<lhstype, rhstype>::SwapType()
		{
			return Pair<rhstype, lhstype>(rhsdata, lhsdata);
		}

		template <Concept::DefaultConstructorType lhstype, Concept::DefaultConstructorType rhstype>
		void Pair<lhstype, rhstype>::Clear()
		{
			lhsdata = lhstype{};
			rhsdata = rhstype{};
		}
	}
}
