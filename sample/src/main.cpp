#include <iostream>

#include "Vector.h"

int main(int argc, char** argv)
{
    NAG::Math::Vector<int> test(1,2,3,4 );
    NAG::Math::Vector<int> test2(1, 1, 1, 1,1);
    test.Assign(test2.Begin(), test2.End());
    int* test3 = new int[5];
    test2.resize(test.Size());
    NAG::Algorithm::Copy(test.Begin(), test.End(), test2.Begin());
    std::cout <<  test2[4];
    return 0;
}
