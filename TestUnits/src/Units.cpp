#include "Units.h"

NAG::Unit::TestUnits::TestUnits(const std::string& name) : m_name(name)
{

}

void NAG::Unit::TestUnits::RunTest()
{
	std::cout << BLUE << "Start " << m_name << " Test" << RESET << std::endl;
	std::pair<bool, int> allTestOk = { true,0 };
	for (auto test : m_tests)
	{
		auto result = test();
		if (!result)
		{
			allTestOk.first = false;
			allTestOk.second += 1;
		}
		
	}
	if (allTestOk.first)
		std::cout << GREEN << "All "<< m_name<<" Test Succeed" << RESET << std::endl;
	else
		std::cout << RED << allTestOk.second << " Test Failed" << RESET << std::endl;
}

void NAG::Unit::TestUnits::PrintOk()
{
	std::cout << "Result : " << GREEN  <<"OK" << RESET <<std::endl;
}
