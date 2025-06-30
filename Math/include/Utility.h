#pragma once

namespace NAG
{
	namespace Concept
	{
		template<typename type>
		concept FloatingType = std::floating_point<type>;

		template<typename... Arg>
		concept DefaultConstructorType = (... && (std::is_default_constructible_v<Arg>));



		template<typename derived, typename base>
		concept DerivedClass = std::derived_from<derived, base>;

		template <auto min, auto... Arg>
		concept MinValue = ((... && (Arg >= min)));

		template <auto min, auto max, auto... Arg>
		concept ClampValue = (... && (Arg >= min && Arg <= max));

		template <auto max, auto... Arg>
		concept MaxValue = ((... && (Arg <= max)));

		template<typename type,typename ...Arg>
		concept IsConvertible = (... &&(std::is_convertible_v<type, Arg>));


		template<typename type>
		concept OpPlus = requires(type lhs, type rhs)
		{
			lhs + rhs;
			lhs += rhs;
		};
		template<typename type, typename ...Arg>
		concept OpPlusVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs + rhs));
			(... && (lhs += rhs));
		};
		template<typename type>
		concept OpMinus = requires(type lhs,type rhs)
		{
			lhs - rhs;
			lhs -= rhs;
		};
		template<typename type, typename ...Arg>
		concept OpMinusVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs - rhs));
			(... && (lhs -= rhs));
		};
		template<typename type>
		concept OpCross = requires(type lhs, type rhs)
		{
			lhs * rhs;
			lhs *= rhs;
		};
		template<typename type, typename ...Arg>
		concept OpCrossVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs * rhs));
			(... && (lhs *= rhs));
		};
		template<typename type>
		concept OpDivide = requires(type lhs, type rhs)
		{
			lhs / rhs;
			lhs /= rhs;
		};
		template<typename type, typename ...Arg>
		concept OpDivideVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs / rhs));
			(... && (lhs /= rhs));
		};
		template<typename type>
		concept AllOpAlgo = std::is_arithmetic_v<type>;
		template<typename... Arg>
		concept AllOpAlgoVar = std::is_arithmetic_v<Arg...>;
		
		template<typename type>
		concept OpIsSup = requires(type lhs, type rhs)
		{
			lhs > rhs;
			lhs >= rhs;
		};
		template<typename type, typename ...Arg>
		concept OpIsSupVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs > rhs));
			(... && (lhs >= rhs));
		};
		template<typename type>
		concept OpIsInf = requires(type lhs,type rhs)
		{
			lhs < rhs;
			lhs <= rhs;
		};
		template<typename type, typename ...Arg>
		concept OpIsInfVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs < rhs));
			(... && (lhs <= rhs));
		};
		template<typename type>
		concept OpEquality = requires(type lhs, type rhs)
		{
			lhs == rhs;
			lhs != rhs;
		};
		template<typename type, typename ...Arg>
		concept OpEqualityVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs == rhs));
			(... && (lhs != rhs));
		};
		template<typename type>
		concept AllOpComparative = requires(type lhs,type rhs)
		{
			lhs > rhs;
			lhs < rhs;
			lhs >= rhs;
			lhs <= rhs;
			lhs != rhs;
			lhs == rhs;
		};

		template<typename type, typename ...Arg>
		concept AllOpComparativeVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs > rhs));
			(... && (lhs < rhs));
			(... && (lhs >= rhs));
			(... && (lhs <= rhs));
			(... && (lhs != rhs));
			(... && (lhs == rhs));
		};

		template<typename type>
		concept OpAssign = requires(type lhs,type rhs)
		{
			lhs = rhs;
		};

		template<typename type, typename ...Arg>
		concept OpAssignVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs = rhs));
		};

		template<typename type>
		concept AllOP = requires(type lhs, type rhs)
		{
			lhs + rhs;
			lhs - rhs;
			lhs* rhs;
			lhs / rhs;
			lhs += rhs;
			lhs -= rhs;
			lhs *= rhs;
			lhs /= rhs;
			lhs > rhs;
			lhs < rhs;
			lhs >= rhs;
			lhs <= rhs;
			lhs != rhs;
			lhs == rhs;
			lhs = rhs;
		};
		template<typename type, typename ...Arg>
		concept AllOpVar = requires(type lhs, Arg... rhs)
		{
			(... && (lhs + rhs));
			(... && (lhs - rhs));
			(... && (lhs * rhs));
			(... && (lhs / rhs));
			(... && (lhs += rhs));
			(... && (lhs -= rhs));
			(... && (lhs *= rhs));
			(... && (lhs /= rhs));
			(... && (lhs > rhs));
			(... && (lhs < rhs));
			(... && (lhs >= rhs));
			(... && (lhs <= rhs));
			(... && (lhs != rhs));
			(... && (lhs == rhs));
			(... && (lhs = rhs));
		};

		template<typename type>
		concept OpArrow = requires(type obj) {
			obj.operator->();
		};
		template<typename type>
		concept OpDereference = requires(type obj) {
			*obj;
		};
		template<typename type>
		concept AllOpAccesibility = requires(type obj) {
			obj.operator->();
			*obj;
		};

		template<typename type>
		concept OpIncrement = requires(type obj) {
			++obj;
			obj++;
		};
		template<typename type>
		concept OpDecrement = requires(type obj) {
			--obj;
			obj--;
		};
		template<typename type>
		concept OpIncrementAndDecrement = requires(type obj) {
			--obj;
			obj--;
			++obj;
			obj++;
		};

	}
	namespace Category
	{
		template<typename type>
		concept Acces_Memory_Category = requires(type t)
		{
			t.Begin();
			t.End() ;
		};

		template<typename type>
		concept Container_Category = requires(type t,size_t idx)
		{
			t.Size();
			t[idx];
		};

		template<typename type>
		concept Iterator_Category = requires()
		{
			typename type::Iterator_type;
		};

	}
	namespace Algorithm
	{
		static constexpr float Epsilon = 1.19209e-06f;

		template<typename typepointer,typename type>requires Concept::OpIncrement<typepointer>&& Concept::OpEquality<typepointer>&& Concept::OpDereference<typepointer>
		void Fill(const typepointer& begin , const typepointer& end,const type& data)
		{
			for (auto it = begin; it != end ; ++it)
			{
				*it = data;
			}
		}

		template<typename typepointer, typename container>requires Concept::OpIncrement<typepointer>&& Concept::OpEquality<typepointer>&& Concept::OpDereference<typepointer>&& Concept::OpDereference<container>
		void Copy(const typepointer& begin, const typepointer& end, const container& dest)
		{
			auto curent = dest;
			for (auto it = begin; it != end; ++it , ++curent)
			{
				*curent = *it;
			}
		}

		template<typename typepointer, typename type>requires Concept::OpIncrement<typepointer> && Concept::OpEquality<type> && Concept::OpEquality<typepointer> && Concept::OpDereference<typepointer>
		typepointer Find(const typepointer& begin,const typepointer& end, const type& data)
		{
			for (auto it = begin ; it != end; ++it)
			{
				if (*it == data)
					return it;
			}
			return end;
		}

		template<typename type>requires Concept::OpIsInf<type>
		type Min(const type& lhs, const type& rhs)
		{
			if (lhs < rhs)
				return lhs;
			return rhs;
		}
		template<typename type> requires Concept::OpIsSup<type>
		type Max(const type& lhs, const type& rhs)
		{
			if (lhs > rhs)
				return lhs;
			return rhs;
		}
		template<typename type> requires Concept::OpAssign<type>
		void Swap(type& lhs, type& rhs)
		{
			auto tmp = lhs;
			lhs = rhs;
			rhs = tmp;
		}
		template<NAG::Concept::FloatingType type> requires Concept::OpIsSup<type>&& Concept::OpIsInf<type>&& Concept::OpAssign<type> && Concept::OpMinus<type>
		bool IsEqual(const type& lhs,const type& rhs,const type& epsilon = Epsilon)
		{
			auto result = NAG::Algorithm::Max(lhs - rhs, rhs - lhs);
			if (result <= epsilon)
				return true;
			return false;
		}
		template<typename type>requires Concept::OpIsSup<type>&& Concept::OpIsInf<type>
		type Clamp(const type& min, const type& max , const type& data)
		{
			if (max < min)
				throw std::runtime_error("max must be bigger than min");
			if (data < min)
				return min;
			if (data > max)
				return max;
			return data;
		}
		template<typename type>requires Concept::OpIsSup<type> && Concept::OpIsInf<type>
		bool IsClamp(const type& min, const type& max, const type& data) 
		{
			if (max < min)
				throw std::runtime_error("max must be bigger than min");

			if (data < min)
				return false;
			if (data > max)
				return false;
			return true;
		}
	}
}