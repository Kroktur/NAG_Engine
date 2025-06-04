#include <iostream>

#include "Vector.h"

int main(int argc, char** argv)
{
    NAG::Math::Vector<int> test(1,2,3,4 );
    NAG::Math::Vector<int> test2(1, 1, 1, 1,1);
    test.Assign(test2.Begin(), test2.End());
    std::cout <<  test[4];
    return 0;
}
