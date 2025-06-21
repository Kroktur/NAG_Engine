#include "Units.h"
#include "../include/Vector.h"
#include <vector>
#include "../include/Angle.h"
#include "../include/Array.h"
#include "../include/Iterator.h"
#include "../include/Matrice.h"
#include "../include/Vec2.h"
#include "../include/Vec3.h"
using namespace NAG::Unit;
int main()
{
	TestUnits VectorTest("Vector");
	VectorTest.AddTest<int, 1>([]() -> ReturnTest<int,1>
		{
			ReturnTest<int,1> result;
			result.name = "Constructor default Test";
			NAG::Math::Vector<int> vector;
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 0;
			return result;
		});
	VectorTest.AddTest<int,2>([]() -> ReturnTest<int,2>
		{
			ReturnTest<int,2> result;
			result.name = "Constructor Copy Test";
			NAG::Math::Vector<int> vector;
			vector.PushBack(3);
			vector.PushBack(4);
			auto vector2 = vector;
			result.data[0].value = vector2.Size();
			result.data[0].expected_value = vector.Size();
			result.data[1].value = vector2[0];
			result.data[1].expected_value = vector[0];
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "Constructor List Test";
			NAG::Math::Vector<int> vector{ 1,2,3,5 };
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 4;
			result.data[1].value = vector[0];
			result.data[1].expected_value = 1;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "Constructor variadique Test";
			NAG::Math::Vector<int> vector(1,2,3,5 );
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 4;
			result.data[1].value = vector[0];
			result.data[1].expected_value = 1;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "Resize ";
			NAG::Math::Vector<int> vector(1, 2, 3, 5);
			vector.Resize(3);
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 3;
			result.data[1].value = vector[1];
			result.data[1].expected_value = 2;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "Reserve ";
			NAG::Math::Vector<int> vector(1, 2, 3, 5);
			vector.Reserve(100);
			result.data[0].value = vector.Capacity();
			result.data[0].expected_value = 100;
			result.data[1].value = vector[50];
			result.data[1].expected_value = int{};
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "Clear ";
			NAG::Math::Vector<int> vector(1, 2, 3, 5);
			vector.Clear();
			result.data[0].value = vector.Capacity();
			result.data[0].expected_value = 0;
			result.data[1].value = vector.Size();
			result.data[1].expected_value = 0;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "operator = ";
			NAG::Math::Vector<int> vector(1, 2, 3, 5);
			auto vector2 = vector;
			result.data[0].value = vector2.Capacity();
			result.data[0].expected_value =vector.Capacity();
			result.data[1].value = vector2.Size();
			result.data[1].expected_value = vector.Size();
			return result;
		});
	VectorTest.AddTest<bool, 2>([]() -> ReturnTest<bool, 2>
		{
			ReturnTest<bool, 2> result;
			result.name = "operator == & operator != ";
			NAG::Math::Vector<int> vector(1, 2, 3, 5);
			auto vector2 = vector;
			result.data[0].value = vector == vector2;
			result.data[0].expected_value = true;
			result.data[1].value = vector != vector2;
			result.data[1].expected_value = false;
			return result;
		});
	VectorTest.AddTest<int, 3>([]() -> ReturnTest<int, 3>
		{
			ReturnTest<int, 3> result;
			result.name = "Size & Capacity & MaxLimit";
			NAG::Math::Vector<int> vector(1, 2, 3, 5);
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 4;
			result.data[1].value = vector.Capacity();
			result.data[1].expected_value = 8;
			result.data[2].value = vector.MaxLimit();
			result.data[2].expected_value = std::numeric_limits<size_t>::max() / sizeof(int);
			return result;
		});
	VectorTest.AddTest<bool,1>([]() -> ReturnTest<bool>
		{
			ReturnTest<bool> result;
			result.name = "Emtpty";
			NAG::Math::Vector<int> vector{};
			result.data[0].value = vector.IsEmpty();
			result.data[0].expected_value = true;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int,2>
		{
			ReturnTest<int,2> result;
			result.name = "operator [] && at";
			NAG::Math::Vector<int> vector{1,2,3,4};
			result.data[0].value = vector[2];
			result.data[0].expected_value = 3;
			result.data[1].value = vector.At(1);
			result.data[1].expected_value = 2;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "Front [] && Back";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			result.data[0].value = vector.Front();
			result.data[0].expected_value = 1;
			result.data[1].value = vector.Back() ;
			result.data[1].expected_value = 4;
			return result;
		});
	VectorTest.AddTest<int*, 1>([]() -> ReturnTest<int*, 1>
		{
			ReturnTest<int*, 1> result;
			result.name = "Data";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			result.data[0].value = vector.Data();
			result.data[0].expected_value = vector.Begin().operator->();
			return result;
		});
	VectorTest.AddTest<int*, 2>([]() -> ReturnTest<int*, 2>
		{
			ReturnTest<int*, 2> result;
			result.name = "Begin && End";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			result.data[0].value = vector.Begin().operator->();
			result.data[0].expected_value = vector.Data();
			result.data[1].value = vector.End().operator->();
			result.data[1].expected_value = vector.Data() + vector.Size();
			return result;
		});
	VectorTest.AddTest<int*, 2>([]() -> ReturnTest<int*, 2>
		{
			ReturnTest<int*, 2> result;
			result.name = "RBegin && REnd";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			result.data[0].value = vector.RBegin().operator->();
			result.data[0].expected_value = vector.Data() + vector.Size() - 1;
			result.data[1].value = vector.REnd().operator->();
			result.data[1].expected_value = vector.Data() -1 ;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int, 2> result;
			result.name = "PushBack && PopBack";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			vector.PushBack(10);
			result.data[0].value = vector.Back();
			result.data[0].expected_value = 10;
			vector.PopBack();
			result.data[1].value = vector.Back();
			result.data[1].expected_value = 4;
			return result;
		});
	VectorTest.AddTest<int, 6>([]() -> ReturnTest<int, 6>
		{
			ReturnTest<int,6> result;
			result.name = "Assign ";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			vector.Assign(10, 5350);
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 10;
			result.data[1].value = vector.Back();
			result.data[1].expected_value = 5350;
			vector.Assign({242,12});
			result.data[2].value = vector.Size();
			result.data[2].expected_value = 2;
			result.data[3].value = vector.Back();
			result.data[3].expected_value = 12;
			NAG::Math::Vector<int> vector2(1, 2, 3, 4, 5);
			vector.Assign(vector2.Begin(), vector2.End());
			result.data[4].value = vector.Size();
			result.data[4].expected_value = 5;
			result.data[5].value = vector.Back();
			result.data[5].expected_value = 5;
			return result;
		});
	VectorTest.AddTest<int, 8>([]() -> ReturnTest<int, 8>
		{
			ReturnTest<int, 8> result;
			result.name = "Insert ";
			NAG::Math::Vector<int> vector{ 1,2,3,4 };
			vector.Insert(vector.End() - 1, 5350);
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 5;
			result.data[1].value = vector.Front();
			result.data[1].expected_value = 1;
			vector.Insert(vector.End(),3,5);
			result.data[2].value = vector.Size();
			result.data[2].expected_value = 8;
			result.data[3].value = vector.Back();
			result.data[3].expected_value = 5;
			NAG::Math::Vector<int> vector2(1, 2, 3, 4, 5);
			vector.Insert(vector.End(),vector2.Begin(), vector2.Begin() + 5);
			result.data[4].value = vector.Size();
			result.data[4].expected_value = 13;
			result.data[5].value = vector.Back();
			result.data[5].expected_value = 5;
			vector.Insert(vector.End(), {1,2,3});
			result.data[6].value = vector.Size();
			result.data[6].expected_value = 16;
			result.data[7].value = vector.Back();
			result.data[7].expected_value = 3;
			return result;
		});
	VectorTest.AddTest<int, 6>([]() -> ReturnTest<int, 6>
		{
			ReturnTest<int, 6> result;
			result.name = "Erase";
			NAG::Math::Vector<int> vector{ 1,2,3,4,5,6,7,8,9,10 };
			vector.Erase(vector.RBegin());
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 9;
			result.data[1].value = vector.Front();
			result.data[1].expected_value = 1;
			vector.Erase(vector.RBegin() + 4,4);
			result.data[2].value = vector.Size();
			result.data[2].expected_value = 5;
			result.data[3].value = vector.Front();
			result.data[3].expected_value = 1;
			vector.Erase(vector.Begin(), vector.Begin() + 3);
			result.data[4].value = vector.Size();
			result.data[4].expected_value =2;
			result.data[5].value = vector.Front();
			result.data[5].expected_value = 4;
			return result;
		});
	VectorTest.AddTest<int, 6>([]() -> ReturnTest<int, 6>
		{
			ReturnTest<int, 6> result;
			result.name = "Range test";
			NAG::Math::Vector<int> vector{ 1,2,3,4,5};
			NAG::Math::Vector<int> vector2{6,7,8,9,10};
			vector.AppendRange(vector2);
			result.data[0].value = vector.Size();
			result.data[0].expected_value = 10;
			result.data[1].value = vector.Back();
			result.data[1].expected_value = 10;
			vector.InsertRange(vector.Begin(),vector2);
			result.data[2].value = vector.Size();
			result.data[2].expected_value = 15;
			result.data[3].value = vector.Front();
			result.data[3].expected_value = 6;
			vector.AssignRange( vector2);
			result.data[4].value = vector.Size();
			result.data[4].expected_value = 5;
			result.data[5].value = vector.Front();
			result.data[5].expected_value = 6;
			return result;
		});
	VectorTest.AddTest<int, 2>([]() -> ReturnTest<int, 2>
		{
			ReturnTest<int,2> result;
			result.name = "Range test";
			NAG::Math::Vector<int> vector{ 1,2,3,4,5 };
			NAG::Math::Vector<int> vector2{ 6,7,8,9,10 };
			vector.Swap(vector2);
			result.data[0].value = vector.Front();
			result.data[0].expected_value =6;
			result.data[1].value = vector2.Front();
			result.data[1].expected_value = 1;
			return result;
		});
	VectorTest.RunTest();
	TestUnits AngleTest("Angle");
	AngleTest.AddTest<float, 2>([]() -> ReturnTest<float, 2>
		{
			ReturnTest<float, 2> result;
			result.name = "Test Strategy";
			auto angle = NAG::Math::Radiant<float,NAG::Math::SignedInterval<float>>(3/4 * NAG::Math::PI);
			result.data[0].value = angle.AsRadians();
			result.data[0].expected_value = -1/2 *NAG::Math::PI;
			auto angle2 = NAG::Math::Radiant(2*NAG::Math::PI);
			result.data[1].value = angle2.AsRadians();
			result.data[1].expected_value =0;
			return result;
		});
	AngleTest.AddTest<float, 2>([]() -> ReturnTest<float, 2>
		{
			ReturnTest<float, 2> result;
			result.name = "Test Rad";
			auto angle = NAG::Math::Radiant<float, NAG::Math::SignedInterval>(3.f / 4 * NAG::Math::PI);
			result.data[0].value = angle.AsDegrees();
			result.data[0].expected_value = -1.f / 2 * NAG::Math::PI;
			auto angle2 = NAG::Math::Degree(360.f);
			result.data[1].value = angle2.AsDegrees();
			result.data[1].expected_value = 0;
			return result;
		});
	AngleTest.AddTest<float, 2>([]() -> ReturnTest<float, 2>
		{
			ReturnTest<float, 2> result;
			result.name = "Test Degree";
			auto angle = NAG::Math::Degree<float, NAG::Math::SignedInterval<float>>(270);
			result.data[0].value = angle.AsDegrees();
			result.data[0].expected_value = -90;
			auto angle2 = NAG::Math::Radiant(2*NAG::Math::PI);
			result.data[1].value = angle2.AsDegrees();
			result.data[1].expected_value = 0;
			return result;
		});
	AngleTest.AddTest<float, 1>([]() -> ReturnTest<float, 1>
		{
			ReturnTest<float, 1> result;
			result.name = "Test Assignation";
			auto angle = NAG::Math::Degree(270.f);
			auto angle2 = NAG::Math::Angle<>();
			angle2 = angle;
			result.data[0].value = angle2.AsDegrees();
			result.data[0].expected_value = 270;
			return result;
		});
	AngleTest.AddTest<float, 8>([]() -> ReturnTest<float, 8>
		{
			ReturnTest<float, 8> result;
			result.name = "Test operator";
			auto angle = NAG::Math::Degree(90.f);
			auto angle2 = NAG::Math::Degree(90.f);
			auto angle3 = angle + angle2;
			result.data[0].value = angle3.AsDegrees();
			result.data[0].expected_value = 180;
			auto angle4 = angle3 - angle2;
			result.data[1].value = angle4.AsDegrees();
			result.data[1].expected_value = 90;
			angle += angle2;
			result.data[2].value = angle.AsDegrees();
			result.data[2].expected_value = 180;
			angle -= angle2;
			result.data[3].value = angle.AsDegrees();
			result.data[3].expected_value = 90;
			auto angle5 = angle * 2;
			result.data[4].value = angle5.AsDegrees();
			result.data[4].expected_value = 180;
			auto angle6 = angle / 2;
			result.data[5].value = angle6.AsDegrees();
			result.data[5].expected_value =45;
			angle *= 2;
			result.data[6].value = angle.AsDegrees();
			result.data[6].expected_value =180;
			angle /= 2;
			result.data[7].value = angle.AsDegrees();
			result.data[7].expected_value = 90;

			return result;
		});
	AngleTest.AddTest<bool, 2>([]() -> ReturnTest<bool, 2>
		{
			ReturnTest<bool, 2> result;
			result.name = "Test operator == / !=";
			auto angle = NAG::Math::Degree(270.f);
			auto angle2 = NAG::Math::Angle<>();
			result.data[0].value = angle == angle2;
			result.data[0].expected_value = false;
			result.data[1].value = angle != angle2;
			result.data[1].expected_value = true;
			return result;
		});
	AngleTest.AddTest<float, 2>([]() -> ReturnTest<float, 2>
		{
			ReturnTest<float, 2> result;
			result.name = "Test Interval Change";
			auto angle = NAG::Math::Degree(270.f);
			result.data[0].value = angle.AsDegrees();
			result.data[0].expected_value = 270;
			auto angle2 = angle.ChangeInterval<NAG::Math::SignedInterval>();
			result.data[1].value = angle2.AsDegrees();
			result.data[1].expected_value = -90;
			return result;
		});
	 AngleTest.RunTest();
	 TestUnits ArrayTest("Array");
	 ArrayTest.AddTest<float, 4>([]() -> ReturnTest<float, 4>
		 {
			 ReturnTest<float, 4> result;
			 result.name = "Constructor";
			 NAG::Math::Array<float, 4> array;
			 result.data[0].value = array[0];
			 result.data[0].expected_value = float{};
			 NAG::Math::Array<float, 4> array2{1,2,3,4};
			 result.data[1].value = array2[1];
			 result.data[1].expected_value = 2;
			 NAG::Math::Array<float, 4> array3(array2);
			 result.data[2].value = array3[0];
			 result.data[2].expected_value = array2[0];
			 NAG::Math::Array<float, 4> array4(1, 2, 3, 5);
			 result.data[3].value = array4[0];
			 result.data[3].expected_value = 1;
			 return result;
		 });
	 ArrayTest.AddTest<float, 1>([]() -> ReturnTest<float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "Clear";
			 NAG::Math::Array<float, 4> array(1,2,3,4);
			 array.Clear();
			 result.data[0].value = array[0];
			 result.data[0].expected_value = float{};
			 return result;
		 });
	 ArrayTest.AddTest<float, 1>([]() -> ReturnTest<float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "operator =";
			 NAG::Math::Array<float, 4> array(1, 2, 3, 4);
			 NAG::Math::Array<float, 4> array2 = array;
			 result.data[0].value = array2[0];
			 result.data[0].expected_value = array[0];
			 return result;
		 });
	 ArrayTest.AddTest<bool, 2>([]() -> ReturnTest<bool, 2>
		 {
			 ReturnTest<bool, 2> result;
			 result.name = "operator == && !=";
			 NAG::Math::Array<float, 4> array(1,2,3,4);
			 NAG::Math::Array<float, 4> array2(1,2,3,4);
			 result.data[0].value = array == array2;
			 result.data[0].expected_value = true;
			 result.data[1].value = array != array2;
			 result.data[1].expected_value = false;
			 return result;
		 });
	 ArrayTest.AddTest<float, 3>([]() -> ReturnTest<float, 3>
		 {
			 ReturnTest<float, 3> result;
			 result.name = "limit";
			 NAG::Math::Array<float, 4> array(1, 2, 3, 4);
			 result.data[0].value = array.Size();
			 result.data[0].expected_value = 4;
			 result.data[1].value =  array.MaxLimit();
			 result.data[1].expected_value = 4;
			 result.data[2].value = static_cast<float>(array.IsEmpty());
			 result.data[2].expected_value = 0;
			 return result;
		 });
	 ArrayTest.AddTest<float, 5>([]() -> ReturnTest<float, 5>
		 {
			 ReturnTest<float, 5> result;
			 result.name = "accessibility";
			 NAG::Math::Array<float, 4> array(1, 2, 3, 4);
			 result.data[0].value = array[0];
			 result.data[0].expected_value = 1;
			 result.data[1].value = array.At(0);
			 result.data[1].expected_value = 1;
			 result.data[2].value = array.Front();
			 result.data[2].expected_value = 1;
			 result.data[3].value = array.Back();
			 result.data[3].expected_value = 4;
			 result.data[4].value = *array.Data();
			 result.data[4].expected_value =1;
			 return result;
		 });
	 ArrayTest.AddTest<float*, 4>([]() -> ReturnTest<float*, 4>
		 {
			 ReturnTest<float*, 4> result;
			 result.name = "Iterator";
			 NAG::Math::Array<float, 4> array(1, 2, 3, 4);
			 result.data[0].value = array.Begin().operator->();
			 result.data[0].expected_value = array.Data();
			 result.data[1].value = array.End().operator->();
			 result.data[1].expected_value = array.Data() + array.Size();
			 result.data[2].value = array.RBegin().operator->();
			 result.data[2].expected_value = array.Data() + array.Size() - 1;
			 result.data[3].value = (array.REnd() - 1).operator->();
			 result.data[3].expected_value = array.Data();
			 return result;
		 });
	 ArrayTest.AddTest< const float*, 4>([]() -> ReturnTest< const float*, 4>
		 {
			 ReturnTest< const float*, 4> result;
			 result.name = " const Iterator";
			 NAG::Math::Array<float, 4> array(1, 2, 3, 4);
			 result.data[0].value = array.CBegin().operator->();
			 result.data[0].expected_value = array.Data();
			 result.data[1].value = array.CEnd().operator->();
			 result.data[1].expected_value = array.Data() + array.Size();
			 result.data[2].value = array.CRBegin().operator->();
			 result.data[2].expected_value = array.Data() + array.Size() - 1;
			 result.data[3].value = (array.CREnd() - 1).operator->();
			 result.data[3].expected_value = array.Data();
			 return result;
		 });
	ArrayTest.AddTest< float, 3>([]() -> ReturnTest< float, 3>
			 {
				 ReturnTest< float,3> result;
				 result.name = "Assign";
				 NAG::Math::Array<float, 4> array(1, 2, 3, 4);
				 array.Assign(2, 5);
				 result.data[0].value = array[3];
				 result.data[0].expected_value = float{};
				 array.Assign({ 4,3,2,1 });
				 result.data[1].value = array[0];
				 result.data[1].expected_value = 4;
				 NAG::Math::Array<float, 4>array2(5, 5, 5, 5);
				 array.Assign(array2.RBegin(), array2.REnd());
				 result.data[2].value = array[0];
				 result.data[2].expected_value = 5;
				 return result;
			 });
	ArrayTest.AddTest< float, 2>([]() -> ReturnTest< float, 2>
		{
			ReturnTest< float,2> result;
			result.name = "Swap";
			NAG::Math::Array<float, 4> array(1, 2, 3, 4);
			NAG::Math::Array<float, 4> array2(4, 3, 2, 1);
			array.Swap(array2);
			result.data[0].value = array[0];
			result.data[0].expected_value = 4;
			result.data[1].value = array2[0];
			result.data[1].expected_value = 1;
			return result;
		});
	 ArrayTest.RunTest();
	 TestUnits IteratorTest("Iterator");
	 IteratorTest.AddTest< int*, 2>([]() -> ReturnTest< int*, 2>
		 {
			 ReturnTest< int*, 2> result;
			 result.name = "Constructor";
			 int* ptr = new int(3);
			 NAG::Math::Iterator<int> iterator(ptr);
			 result.data[0].value = iterator.operator->();
			 result.data[0].expected_value = ptr;
			 NAG::Math::Iterator<int> iterator2(iterator);
			 result.data[1].value = iterator2.operator->();
			 result.data[1].expected_value = ptr;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 IteratorTest.AddTest< bool, 1>([]() -> ReturnTest< bool, 1>
		 {
			 ReturnTest< bool, 1> result;
			 result.name = " default Constructor";
			 NAG::Math::Iterator<int> iterator;
			 NAG::Math::Iterator<int> iterator2(nullptr);
			 result.data[0].value = iterator2 == iterator;
			 result.data[0].expected_value = true;

			 return result;
		 });
	 IteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "operator incrementation";
			 int* ptr = new int(3);
			 NAG::Math::Iterator<int> iterator(ptr);
			 result.data[0].value = *iterator == 3;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator.operator->() == ptr;
			 result.data[1].expected_value = true;
			 ++iterator;
			 result.data[2].value = iterator.operator->() == ptr + 1;
			 result.data[2].expected_value = true;
			 --iterator;
			 result.data[3].value = iterator.operator->() == ptr;
			 result.data[3].expected_value = true;
			 result.data[4].value = (iterator++).operator->() == ptr;
			 result.data[4].expected_value = true;
			 result.data[5].value = (iterator--).operator->() == ptr + 1;
			 result.data[5].expected_value = true;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 IteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "comparison operator ";
			 int* ptr = new int(3);
			 NAG::Math::Iterator<int> iterator(ptr);
			 NAG::Math::Iterator<int> iterator2(ptr);
			 result.data[0].value = iterator == iterator2;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator != iterator2;
			 result.data[1].expected_value = false;
			 result.data[2].value = iterator >= iterator2;
			 result.data[2].expected_value = true;
			 result.data[3].value = iterator <= iterator2;
			 result.data[3].expected_value = true;
			 ++iterator;
			 result.data[4].value = iterator > iterator2;
			 result.data[4].expected_value = true;
			 result.data[5].value = iterator< iterator2;
			 result.data[5].expected_value = false;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 IteratorTest.AddTest< int, 6>([]() -> ReturnTest< int, 6>
		 {
			 ReturnTest<int, 6> result;
			 result.name = "other operator ";
			 int* ptr = new int(3);
			 int* ptr2 = new int(5);
			 NAG::Math::Iterator<int> iterator(ptr);
			 NAG::Math::Iterator<int> iterator2(ptr2);
			 iterator = iterator2;
			 result.data[0].value = *iterator;
			 result.data[0].expected_value = *ptr2;
			 result.data[1].value = *(iterator + 1);
			 result.data[1].expected_value = *(ptr2 + 1);
			 result.data[2].value = *(iterator - 1);
			 result.data[2].expected_value = *(ptr2 - 1);
			 result.data[3].value =*(iterator+=1);
			 result.data[3].expected_value = *(ptr2 + 1);
			 result.data[4].value = *(iterator -= 1);
			 result.data[4].expected_value = *ptr2;
			 result.data[5].value =  static_cast<int>(iterator2 - iterator);
			 result.data[5].expected_value = 0;
			 delete ptr;
			 ptr = nullptr;
			 delete ptr2;
			 ptr2 = nullptr;
	 	return result;
		 });
	 IteratorTest.RunTest();
	 TestUnits ReverseIteratorTest("ReverseIterator");
	 ReverseIteratorTest.AddTest< int*, 2>([]() -> ReturnTest< int*, 2>
		 {
			 ReturnTest< int*, 2> result;
			 result.name = "Constructor";
			 int* ptr = new int(3);
			 NAG::Math::ReverseIterator<int> iterator(ptr);
			 result.data[0].value = iterator.operator->();
			 result.data[0].expected_value = ptr;
			 NAG::Math::ReverseIterator<int> iterator2(iterator);
			 result.data[1].value = iterator2.operator->();
			 result.data[1].expected_value = ptr;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 ReverseIteratorTest.AddTest< bool, 1>([]() -> ReturnTest< bool, 1>
		 {
			 ReturnTest< bool, 1> result;
			 result.name = " default Constructor";
			 NAG::Math::ReverseIterator<int> iterator;
			 NAG::Math::ReverseIterator<int> iterator2(nullptr);
			 result.data[0].value = iterator2 == iterator;
			 result.data[0].expected_value = true;

			 return result;
		 });
	 ReverseIteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "operator incrementation";
			 int* ptr = new int(3);
			 NAG::Math::ReverseIterator<int> iterator(ptr);
			 result.data[0].value = *iterator == 3;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator.operator->() == ptr;
			 result.data[1].expected_value = true;
			 ++iterator;
			 result.data[2].value = iterator.operator->() == ptr - 1;
			 result.data[2].expected_value = true;
			 --iterator;
			 result.data[3].value = iterator.operator->() == ptr;
			 result.data[3].expected_value = true;
			 result.data[4].value = (iterator++).operator->() == ptr;
			 result.data[4].expected_value = true;
			 result.data[5].value = (iterator--).operator->() == ptr - 1;
			 result.data[5].expected_value = true;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 ReverseIteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "comparison operator ";
			 int* ptr = new int(3);
			 NAG::Math::ReverseIterator<int> iterator(ptr);
			 NAG::Math::ReverseIterator<int> iterator2(ptr);
			 result.data[0].value = iterator == iterator2;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator != iterator2;
			 result.data[1].expected_value = false;
			 result.data[2].value = iterator >= iterator2;
			 result.data[2].expected_value = true;
			 result.data[3].value = iterator <= iterator2;
			 result.data[3].expected_value = true;
			 ++iterator;
			 result.data[4].value = iterator > iterator2;
			 result.data[4].expected_value = true;
			 result.data[5].value = iterator < iterator2;
			 result.data[5].expected_value = false;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 ReverseIteratorTest.AddTest< int, 6>([]() -> ReturnTest< int, 6>
		 {
			 ReturnTest<int, 6> result;
			 result.name = "other operator ";
			 int* ptr = new int(3);
			 int* ptr2 = new int(5);
			 NAG::Math::ReverseIterator<int> iterator(ptr);
			 NAG::Math::ReverseIterator<int> iterator2(ptr2);
			 iterator = iterator2;
			 result.data[0].value = *iterator;
			 result.data[0].expected_value = *ptr2;
			 result.data[1].value = *(iterator + 1);
			 result.data[1].expected_value = *(ptr2 - 1);
			 result.data[2].value = *(iterator - 1);
			 result.data[2].expected_value = *(ptr2 + 1);
			 result.data[3].value = *(iterator += 1);
			 result.data[3].expected_value = *(ptr2 - 1);
			 result.data[4].value = *(iterator -= 1);
			 result.data[4].expected_value = *ptr2;
			 result.data[5].value = static_cast<int>(iterator2 - iterator);
			 result.data[5].expected_value = 0;
			 delete ptr;
			 ptr = nullptr;
			 delete ptr2;
			 ptr2 = nullptr;
			 return result;
		 });
	 ReverseIteratorTest.RunTest();
	 TestUnits constIteratorTest("constIterator");
	 constIteratorTest.AddTest<const int*, 2>([]() -> ReturnTest<const int*, 2>
		 {
			 ReturnTest<const int*, 2> result;
			 result.name = "Constructor";
			 int* ptr = new int(3);
			 NAG::Math::ConstIterator<int> iterator(ptr);
			 result.data[0].value = iterator.operator->();
			 result.data[0].expected_value = ptr;
			 NAG::Math::ConstIterator<int> iterator2(iterator);
			 result.data[1].value = iterator2.operator->();
			 result.data[1].expected_value = ptr;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 constIteratorTest.AddTest< bool, 1>([]() -> ReturnTest< bool, 1>
		 {
			 ReturnTest< bool, 1> result;
			 result.name = " default Constructor";
			 NAG::Math::ConstIterator<int> iterator;
			 NAG::Math::ConstIterator<int> iterator2(nullptr);
			 result.data[0].value = iterator2 == iterator;
			 result.data[0].expected_value = true;

			 return result;
		 });
	 constIteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "operator incrementation";
			 int* ptr = new int(3);
			 NAG::Math::ConstIterator<int> iterator(ptr);
			 result.data[0].value = *iterator == 3;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator.operator->() == ptr;
			 result.data[1].expected_value = true;
			 ++iterator;
			 result.data[2].value = iterator.operator->() == ptr + 1;
			 result.data[2].expected_value = true;
			 --iterator;
			 result.data[3].value = iterator.operator->() == ptr;
			 result.data[3].expected_value = true;
			 result.data[4].value = (iterator++).operator->() == ptr;
			 result.data[4].expected_value = true;
			 result.data[5].value = (iterator--).operator->() == ptr + 1;
			 result.data[5].expected_value = true;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 constIteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "comparison operator ";
			 int* ptr = new int(3);
			 NAG::Math::ConstIterator<int> iterator(ptr);
			 NAG::Math::ConstIterator<int> iterator2(ptr);
			 result.data[0].value = iterator == iterator2;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator != iterator2;
			 result.data[1].expected_value = false;
			 result.data[2].value = iterator >= iterator2;
			 result.data[2].expected_value = true;
			 result.data[3].value = iterator <= iterator2;
			 result.data[3].expected_value = true;
			 ++iterator;
			 result.data[4].value = iterator > iterator2;
			 result.data[4].expected_value = true;
			 result.data[5].value = iterator < iterator2;
			 result.data[5].expected_value = false;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 constIteratorTest.AddTest< int, 6>([]() -> ReturnTest< int, 6>
		 {
			 ReturnTest<int, 6> result;
			 result.name = "other operator ";
			 int* ptr = new int(3);
			 int* ptr2 = new int(5);
			 NAG::Math::ConstIterator<int> iterator(ptr);
			 NAG::Math::ConstIterator<int> iterator2(ptr2);
			 iterator = iterator2;
			 result.data[0].value = *iterator;
			 result.data[0].expected_value = *ptr2;
			 result.data[1].value = *(iterator + 1);
			 result.data[1].expected_value = *(ptr2 + 1);
			 result.data[2].value = *(iterator - 1);
			 result.data[2].expected_value = *(ptr2 - 1);
			 result.data[3].value = *(iterator += 1);
			 result.data[3].expected_value = *(ptr2 + 1);
			 result.data[4].value = *(iterator -= 1);
			 result.data[4].expected_value = *ptr2;
			 result.data[5].value = static_cast<int>(iterator2 - iterator);
			 result.data[5].expected_value = 0;
			 delete ptr;
			 ptr = nullptr;
			 delete ptr2;
			 ptr2 = nullptr;
			 return result;
		 });
	 constIteratorTest.RunTest();
	 TestUnits ConstReverseIteratorTest("ConstReverseIterator");
	 ConstReverseIteratorTest.AddTest<const int*, 2>([]() -> ReturnTest<const int*, 2>
		 {
			 ReturnTest<const int*, 2> result;
			 result.name = "Constructor";
			 int* ptr = new int(3);
			 NAG::Math::ConstReverseIterator<int> iterator(ptr);
			 result.data[0].value = iterator.operator->();
			 result.data[0].expected_value = ptr;
			 NAG::Math::ConstReverseIterator<int> iterator2(iterator);
			 result.data[1].value = iterator2.operator->();
			 result.data[1].expected_value = ptr;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 ConstReverseIteratorTest.AddTest< bool, 1>([]() -> ReturnTest< bool, 1>
		 {
			 ReturnTest< bool, 1> result;
			 result.name = " default Constructor";
			 NAG::Math::ConstReverseIterator<int> iterator;
			 NAG::Math::ConstReverseIterator<int> iterator2(nullptr);
			 result.data[0].value = iterator2 == iterator;
			 result.data[0].expected_value = true;

			 return result;
		 });
	 ConstReverseIteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "operator incrementation";
			 int* ptr = new int(3);
			 NAG::Math::ConstReverseIterator<int> iterator(ptr);
			 result.data[0].value = *iterator == 3;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator.operator->() == ptr;
			 result.data[1].expected_value = true;
			 ++iterator;
			 result.data[2].value = iterator.operator->() == ptr - 1;
			 result.data[2].expected_value = true;
			 --iterator;
			 result.data[3].value = iterator.operator->() == ptr;
			 result.data[3].expected_value = true;
			 result.data[4].value = (iterator++).operator->() == ptr;
			 result.data[4].expected_value = true;
			 result.data[5].value = (iterator--).operator->() == ptr - 1;
			 result.data[5].expected_value = true;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 ConstReverseIteratorTest.AddTest< bool, 6>([]() -> ReturnTest< bool, 6>
		 {
			 ReturnTest<bool, 6> result;
			 result.name = "comparison operator ";
			 int* ptr = new int(3);
			 NAG::Math::ConstReverseIterator<int> iterator(ptr);
			 NAG::Math::ConstReverseIterator<int> iterator2(ptr);
			 result.data[0].value = iterator == iterator2;
			 result.data[0].expected_value = true;
			 result.data[1].value = iterator != iterator2;
			 result.data[1].expected_value = false;
			 result.data[2].value = iterator >= iterator2;
			 result.data[2].expected_value = true;
			 result.data[3].value = iterator <= iterator2;
			 result.data[3].expected_value = true;
			 ++iterator;
			 result.data[4].value = iterator > iterator2;
			 result.data[4].expected_value = true;
			 result.data[5].value = iterator < iterator2;
			 result.data[5].expected_value = false;
			 delete ptr;
			 ptr = nullptr;
			 return result;
		 });
	 ConstReverseIteratorTest.AddTest< int, 6>([]() -> ReturnTest< int, 6>
		 {
			 ReturnTest<int, 6> result;
			 result.name = "other operator ";
			 int* ptr = new int(3);
			 int* ptr2 = new int(5);
			 NAG::Math::ConstReverseIterator<int> iterator(ptr);
			 NAG::Math::ConstReverseIterator<int> iterator2(ptr2);
			 iterator = iterator2;
			 result.data[0].value = *iterator;
			 result.data[0].expected_value = *ptr2;
			 result.data[1].value = *(iterator + 1);
			 result.data[1].expected_value = *(ptr2 - 1);
			 result.data[2].value = *(iterator - 1);
			 result.data[2].expected_value = *(ptr2 + 1);
			 result.data[3].value = *(iterator += 1);
			 result.data[3].expected_value = *(ptr2 - 1);
			 result.data[4].value = *(iterator -= 1);
			 result.data[4].expected_value = *ptr2;
			 result.data[5].value = static_cast<int>(iterator2 - iterator);
			 result.data[5].expected_value = 0;
			 delete ptr;
			 ptr = nullptr;
			 delete ptr2;
			 ptr2 = nullptr;
			 return result;
		 });
	 ConstReverseIteratorTest.RunTest();
	 TestUnits VectorNDTest("VectorND");
	 VectorNDTest.AddTest< int, 4>([]() -> ReturnTest< int, 4>
		 {
			 ReturnTest<int,4> result;
			 result.name = "constructor ";
			 NAG::Math::VectorND<int, 3> vnd;
			 result.data[0].value = vnd[0];
			 result.data[0].expected_value = int{} ;
			 vnd[0] = 1;
			 NAG::Math::VectorND<int, 3> vnd2(vnd); 
			 result.data[1].value = vnd2[0];
			 result.data[1].expected_value = 1;
			 NAG::Math::VectorND<int, 3> vnd3{5,5,5};
			 result.data[2].value = vnd3[0];
			 result.data[2].expected_value = 5;
			 NAG::Math::VectorND<int, 3> vnd4( 5,5,5 );
			 result.data[3].value = vnd4[0];
			 result.data[3].expected_value = 5;
			 return result;
		 });
	 VectorNDTest.AddTest< bool,3>([]() -> ReturnTest< bool, 3>
		 {
			 ReturnTest<bool, 3> result;
			 result.name = "operator ";
			 NAG::Math::VectorND<int, 3> vnd(1,2,3);
			 NAG::Math::VectorND<int, 3> vnd2(1, 2, 3);
			 result.data[0].value = vnd == vnd2;
			 result.data[0].expected_value = true;
			 result.data[1].value = vnd != vnd2;
			 result.data[1].expected_value = false;
			 auto vnd3 = vnd;
			 result.data[2].value = vnd == vnd3;
			 result.data[2].expected_value = true;
			 return result;
		 });
	 VectorNDTest.AddTest< float, 2>([]() -> ReturnTest< float, 2>
		 {
			 ReturnTest<float, 2> result;
			 result.name = "accesibility";
			 NAG::Math::VectorND<int, 3> vnd(1, 2, 3);
			 result.data[0].value = vnd[0];
			 result.data[0].expected_value = 1;
			 result.data[1].value = vnd.At(2);
			 result.data[1].expected_value = 3;
			 return result;
		 });
	 VectorNDTest.AddTest< float, 1>([]() -> ReturnTest< float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "Size";
			 NAG::Math::VectorND<int, 3> vnd(1, 2, 3);
			 result.data[0].value = vnd.Size();
			 result.data[0].expected_value = 3;
			 return result;
		 });
	 VectorNDTest.AddTest< float, 8>([]() -> ReturnTest< float, 8>
		 {
			 ReturnTest<float,8> result;
			 result.name = "operator incrementation";
			 NAG::Math::VectorND<float, 3> vnd(1, 2, 3);
			 NAG::Math::VectorND<float, 3> vnd2(2, 2, 2);
			 result.data[0].value =(vnd2 + vnd)[0];
			 result.data[0].expected_value = 3;
			 result.data[1].value = (vnd2 - vnd)[0];
			 result.data[1].expected_value = 1;
			 vnd += vnd2;
			 result.data[2].value = vnd[0];
			 result.data[2].expected_value = 3;
			 vnd -= vnd2;
			 result.data[3].value = vnd[0];
			 result.data[3].expected_value = 1;
			 result.data[4].value = (vnd * 2)[0];
			 result.data[4].expected_value = 2;
			 result.data[5].value = (vnd / 2)[1];
			 result.data[5].expected_value = 1;
			 vnd *= 2;
			 result.data[6].value = vnd[0];
			 result.data[6].expected_value = 2;
			 vnd /= 2;
			 result.data[7].value = vnd[0];
			 result.data[7].expected_value = 1;
			 return result;
		 });
	 VectorNDTest.AddTest< float, 1>([]() -> ReturnTest< float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "Norm";
			 NAG::Math::VectorND<float, 3> vnd(1, 2,2);
			 result.data[0].value = vnd.Norm();
			 result.data[0].expected_value = 3;
			 return result;
		 });
	 VectorNDTest.AddTest< float, 1>([]() -> ReturnTest< float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "Normalize";
			 NAG::Math::VectorND<int, 3> vnd(1, 2, 3);
			 auto vecnd2 = vnd.Normalize();
			 result.data[0].value = vecnd2.Norm();
			 result.data[0].expected_value = 1;
			 return result;
		 });
	 VectorNDTest.AddTest< bool, 2>([]() -> ReturnTest< bool, 2>
		 {
			 ReturnTest<bool, 2> result;
			 result.name = "Zero";
			 NAG::Math::VectorND<int, 3> vnd(0,0,0);
			 result.data[0].value = vnd.IsZero();
			 result.data[0].expected_value = true;
			 NAG::Math::VectorND<int, 3> vnd2(1,4, 2);
			 result.data[1].value = vnd2.IsZero();
			 result.data[1].expected_value = false;
			 return result;
		 });
	 VectorNDTest.AddTest< float, 1>([]() -> ReturnTest< float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "Dot";
			 NAG::Math::VectorND<int, 3> vnd(1, 2, 3);
			 auto dotresult  = vnd.Dot(NAG::Math::VectorND<int, 3>{4, -5, 6});
			 result.data[0].value = dotresult;
			 result.data[0].expected_value = 12;
			 return result;
		 });
	 VectorNDTest.RunTest();
	 TestUnits Vec2Test("Vec2");
	 Vec2Test.AddTest< float, 3>([]() -> ReturnTest< float, 3>
		 {
			 ReturnTest<float, 3> result;
			 result.name = "Constructor";
			 NAG::Math::Vec2<int> vec2;
			 result.data[0].value = vec2[0];
			 result.data[0].expected_value = int{};
			 NAG::Math::Vec2<int> vec22(10,5 );
			 result.data[1].value = vec22[0];
			 result.data[1].expected_value = 10;
			 NAG::Math::Vec2<int> vec23(vec22);
			 result.data[2].value = vec23[0];
			 result.data[2].expected_value = vec22[0];
			 return result;
		 });
	 Vec2Test.AddTest< float, 2>([]() -> ReturnTest< float,2>
		 {
			 ReturnTest<float, 2> result;
			 result.name = "assignation";
			 NAG::Math::Vec2<int> vec2(10, 4);
			 result.data[0].value = vec2[0];
			 result.data[0].expected_value =vec2.x;
			 vec2[0] = 59;
			 result.data[1].value = vec2.x;
			 result.data[1].expected_value =59;
			 return result;
		 });
	 Vec2Test.RunTest();
	 TestUnits Vec3Test("Vec3");
	 Vec3Test.AddTest< float, 3>([]() -> ReturnTest< float, 3>
		 {
			 ReturnTest<float, 3> result;
			 result.name = "Constructor";
			 NAG::Math::Vec3<int> vec3;
			 result.data[0].value = vec3[0];
			 result.data[0].expected_value = int{};
			 NAG::Math::Vec3<int> vec32(10, 5,5);
			 result.data[1].value = vec32[0];
			 result.data[1].expected_value = 10;
			 NAG::Math::Vec3<int> vec33(vec32);
			 result.data[2].value = vec33[0];
			 result.data[2].expected_value = vec32[0];
			 return result;
		 });
	 Vec3Test.AddTest< float, 2>([]() -> ReturnTest< float, 2>
		 {
			 ReturnTest<float, 2> result;
			 result.name = "assignation";
			 NAG::Math::Vec3<int> vec3(10, 4,5);
			 result.data[0].value = vec3[0];
			 result.data[0].expected_value = vec3.x;
			 vec3[0] = 59;
			 result.data[1].value = vec3.x;
			 result.data[1].expected_value = 59;
			 return result;
		 });
	 Vec3Test.AddTest< float, 1>([]() -> ReturnTest< float, 1>
		 {
			 ReturnTest<float, 1> result;
			 result.name = "Cross";
			 NAG::Math::Vec3<int> vec3(1,0,0);
			 NAG::Math::Vec3<int> vec32(0, 1, 0);
			 auto reslut = vec3.Cross(vec32);
			 result.data[0].value = reslut.z;
			 result.data[0].expected_value =1;
			 return result;
		 });
	 Vec3Test.RunTest();
	 TestUnits Matrixtest("Matrix");
	 Matrixtest.AddTest<float, 4>([]()->ReturnTest<float, 4>
	 {
			 ReturnTest<float, 4> result;
			 result.name = "constructor";
			 NAG::Math::Matrix<float, 3> matrix;
			 result.data[0].value = matrix[8];
			 result.data[0].expected_value = 0;
			 NAG::Math::Matrix<float, 3> matrix2{1,2,3,4,5,6,7,8,9};
			 result.data[1].value = matrix2[8];
			 result.data[1].expected_value = 9;
			 NAG::Math::Matrix<float, 3> matrix3(matrix2);
			 result.data[2].value = matrix3[8];
			 result.data[2].expected_value = 9;
			 NAG::Math::Matrix<float, 3> matrix4( 1,2,3,4,5,6,7,8,9 );
			 result.data[3].value = matrix4[8];
			 result.data[3].expected_value = 9;

			 return result;
	 });
	 Matrixtest.AddTest<bool, 2>([]()->ReturnTest<bool,2>
		 {
			 ReturnTest<bool,2> result;
			 result.name = "operator == && !=";
			 NAG::Math::Matrix<float, 3> matrix{ 1,2,3,4,5,6,7,8,9 };
			 NAG::Math::Matrix<float, 3> matrix2{ 1,2,3,4,5,6,7,8,9 };
			 result.data[0].value = matrix2 == matrix;
			 result.data[0].expected_value = true;
			 result.data[1].value = matrix2 != matrix;
			 result.data[1].expected_value = false;
			 return result;
		 });
	 Matrixtest.AddTest<bool, 1>([]()->ReturnTest<bool, 1>
		 {
			 ReturnTest<bool,1> result;
			 result.name = "operator =";
			 NAG::Math::Matrix<float, 3> matrix{ 1,2,3,4,5,6,7,8,9 };
			 NAG::Math::Matrix<float, 3> matrix2 = matrix;
			 result.data[0].value = matrix2 == matrix;
			 result.data[0].expected_value = true;
			 return result;
		 });
	 Matrixtest.AddTest<float, 3>([]()->ReturnTest<float,3>
		 {
			 ReturnTest<float, 3> result;
			 result.name = "operator =";
			 NAG::Math::Matrix<float, 3> matrix{ 1,2,3,4,5,6,7,8,9 };
			 result.data[0].value = matrix.Size();
			 result.data[0].expected_value = 9;
			 result.data[1].value = matrix.Height();
			 result.data[1].expected_value = 3;
			 result.data[2].value = matrix.Width();
			 result.data[2].expected_value = 3;
			 return result;
		 });
	 Matrixtest.AddTest<float, 4>([]()->ReturnTest<float,4>
		 {
			 ReturnTest<float, 4> result;
			 result.name = "accesibility";
			 NAG::Math::Matrix<float, 3> matrix{ 1,2,3,4,5,6,7,8,9 };

			 result.data[0].value = matrix.GetCellIndex(2,2);
			 result.data[0].expected_value = 8;
			 result.data[1].value = matrix.GetCell(2,2);
			 result.data[1].expected_value = 9;
			 result.data[2].value = matrix[8];
			 result.data[2].expected_value = 9;
			 result.data[3].value = matrix.At(8);
			 result.data[3].expected_value = 9;
			 return result;
		 });
	 Matrixtest.AddTest<float, 8>([]()->ReturnTest<float, 8>
		 {
			 ReturnTest<float, 8> result;
			 result.name = "operator";
			 NAG::Math::Matrix<float, 3> matrix{ 1,2,3,4,5,6,7,8,9 };
			 NAG::Math::Matrix<float, 3> matrix2{ 1,2,3,4,5,6,7,8,9 };
			 result.data[0].value = (matrix + matrix2)[8];
			 result.data[0].expected_value = 9 + 9;
			 result.data[1].value = (matrix - matrix2)[8];
			 result.data[1].expected_value = 0;
			 matrix += matrix2;
			 result.data[2].value = matrix[8];
			 result.data[2].expected_value =9 + 9;
			 matrix -= matrix2;
			 result.data[3].value = matrix[8];
			 result.data[3].expected_value = 9;
			 result.data[4].value = (matrix * 2)[8];
			 result.data[4].expected_value = 9 * 2;
			 result.data[5].value = (matrix / 2)[8];
			 result.data[5].expected_value = 9.f / 2;
			 matrix *= 2;
			 result.data[6].value = matrix[8];
			 result.data[6].expected_value = 9 * 2;
			 matrix /= 2;
			 result.data[7].value = matrix[8];
			 result.data[7].expected_value = 9;
			 return result;
		 });
	 Matrixtest.AddTest<bool, 1>([]()->ReturnTest<bool, 1>
		 {
			 ReturnTest<bool, 1> result;
			 result.name = "IsZero";
			 NAG::Math::Matrix<float, 3> matrix;
			 result.data[0].value = matrix.IsZero();
			 result.data[0].expected_value = true;
			 return result;
		 });
	 Matrixtest.AddTest<bool, 1>([]()->ReturnTest<bool, 1>
		 {
			 ReturnTest<bool, 1> result;
			 result.name = "MatrixProduct";
			 NAG::Math::Matrix<float,2,3> matrix(1,2,3,4,5,6);
			 NAG::Math::Matrix<float, 3, 2> matrix2(7,8,9,10,11,12);
			 auto cross = matrix.MatrixProduct(matrix2);
			 NAG::Math::Matrix<float, 2> matrix3(58, 64, 139, 154);
			 result.data[0].value = cross == matrix3;
			 result.data[0].expected_value = true;
			 return result;
		 });
	 Matrixtest.RunTest();
	 TestUnits Utility("Utility");
	 Utility.AddTest<float,7>([]()->ReturnTest<float, 7>
		 {
			 ReturnTest<float,7> result;
			 result.name = "Utility";
			 NAG::Math::Array<float, 4> array;
			 NAG::Algorithm::Fill(array.Begin(), array.End(), 5);
			 result.data[0].value = array[3];
			 result.data[0].expected_value = 5.f;
			 float* tab = new float[4];
			 NAG::Algorithm::Copy(array.Begin(), array.End(), tab);
			 result.data[1].value = tab[3];
			 result.data[1].expected_value = 5;
			 delete[] tab;
			 tab = nullptr;
			 NAG::Math::Vector<float> vector(1, 2, 3, 4);
			 auto it = NAG::Algorithm::Find(vector.Begin(), vector.End(), 4);
	 	     result.data[2].value = it == (vector.End()-1);
			 result.data[2].expected_value = 1;
			 float min = 4;
			 float max = 6;
			 result.data[3].value = NAG::Algorithm::Min(min,max);
			 result.data[3].expected_value = min;
			 result.data[4].value = NAG::Algorithm::Max(min, max);
			 result.data[4].expected_value = max;
			 NAG::Algorithm::Swap(max, min);
			 result.data[5].value = min;
			 result.data[5].expected_value = 6;
			 result.data[6].value = NAG::Algorithm::IsEqual(min,max,2.f) == true;
			 result.data[6].expected_value = 1;
			 return result;
		 });
	 auto angle = NAG::Math::Degree<float>(90);
	 std::cout << angle;
	 Utility.RunTest();
	return 0;
}
