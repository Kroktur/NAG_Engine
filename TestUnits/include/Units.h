#pragma once
#include <iostream>
#include "array"
#include "functional"
#include "string"


namespace NAG
{
	namespace Unit
	{
		static constexpr const char* RESET = "\033[0m";
		static constexpr const char* RED = "\033[31m";
		static constexpr const char* GREEN = "\033[32m";
		static constexpr const char* BLUE = "\033[38;5;39m";
		static constexpr const char* ORANGE = "\033[38;5;208m";

		template<typename type>
		concept UnitTestType = requires(std::ostream & os, const type & data, const type & other)
		{
			{ os << data };
			{ data == other };
		};

		template<UnitTestType type,size_t size = 1>
		class ReturnTest
		{
		public:
			template<typename>
			struct ValueContainer;

			ReturnTest();
			std::string name;
			std::array<ValueContainer<type>, size> data;
		private:
			template<typename  typecontainer>
			struct ValueContainer
			{
				ValueContainer();
				typecontainer value ;
				typecontainer expected_value ;
			};
		};
		class TestUnits
		{
		public:
			TestUnits(const std::string&);
			template<UnitTestType type, size_t size>
			void AddTest(std::function<ReturnTest<type,size>()> fn);
			void RunTest();

		private:
			void PrintOk();
			template<UnitTestType type>
			void PrintKO(const type& value, const type& expectedvalue);
			std::vector<std::function<bool()>> m_tests;
			std::string m_name;

		};

		template <UnitTestType type, size_t size>
		ReturnTest<type, size>::ReturnTest():data(ValueContainer<type>{}),name("")
		{}

		template <UnitTestType type, size_t size>
		template <typename typecontainer>
		ReturnTest<type, size>::ValueContainer<typecontainer>::ValueContainer():value(typecontainer{}), expected_value(typecontainer{})
		{}

		template <UnitTestType type,size_t size>
		void TestUnits::AddTest(std::function<ReturnTest<type,size>()> fn)
		{
			m_tests.push_back([this, fn]()->bool
				{
					auto executeresult = fn();

					if (executeresult.name == "")
						throw std::runtime_error("no name");

					std::cout << "Start Test : " << BLUE << executeresult.name << RESET << std::endl;
					bool result = true;
					for (auto i = 0; i < size; ++i)
					{
						if (executeresult.data[i].value == executeresult.data[i].expected_value)
						{
							PrintOk();
							continue;
						}
						PrintKO(executeresult.data[i].value, executeresult.data[i].expected_value);
						result = false;
					}
					if (result)
					{
						std::cout << "End Test : " << BLUE << executeresult.name << RESET << std::endl;
						return true;
					}
					std::cout << "End Test : " << ORANGE << executeresult.name << RESET << std::endl;
					return false;
				});
		}

		template <UnitTestType type>
		void TestUnits::PrintKO(const type& value, const type& expectedvalue)
		{
			std::cout << "Result : " << RED << "KO" << RESET << "\n" << "Output Value : " << RED << value << RESET << "\n" << "Expected Value : " << GREEN << expectedvalue << RESET << std::endl;
		}
	}
}