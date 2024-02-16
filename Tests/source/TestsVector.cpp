#include <gtest/gtest.h>
#include <vector/vector.hpp>

TEST(Construct_test_default_int, GetTest)
{
	MyVector<int> v;
	ASSERT_EQ(0, v.size());
	ASSERT_EQ(0, v.capacity());
}

class A
{
public:

	A() = delete;
};

TEST(Construct_test_count_int, GetTest)
{
	MyVector<std::string> v{ "abc", "adc", "adefr", "xuy" };
	MyVector<std::string> v1{ "a" };
	v.swap(v1);

	v1 = v;
	for (auto x : v1)
	{
		std::cout << x << ' ';
	}
	for (auto it = v.cbegin(), ite = v.cend(); it != ite; ++it) {}
}

//TEST(Construct_test_init_list_int, GetTest)
//{
//	vector<int> v = { 1, 2, 3 , 4, 5, 6};
//	ASSERT_EQ(6, v.size());
//	ASSERT_EQ(12, v.capacity());
//	auto beg = v.begin();
//	auto end = v.end();
//	ASSERT_EQ(1, *beg);
//	ASSERT_EQ(6, *(end - 1));
//}
//
//TEST(Construct_test_default_string, GetTest)
//{
//	vector<std::string> v;
//	ASSERT_EQ(0, v.size());
//	ASSERT_EQ(0, v.capacity());
//}
//
//TEST(Construct_test_init_list_string, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" , "adfrffe"};
//	ASSERT_EQ(4, v.size());
//	ASSERT_EQ(8, v.capacity());
//	auto beg = v.begin();
//	auto end = v.end();
//	ASSERT_EQ("a", *beg);
//	ASSERT_EQ("adfrffe", *(end - 1));
//}
//
//TEST(Construct_test_copy_int, GetTest)
//{
//	vector<int> v = { 1, 2, 3 , 4, 5, 6};
//	vector<int> v1(v);
//	ASSERT_EQ(6, v1.size());
//	ASSERT_EQ(12, v1.capacity());
//	auto beg = v1.begin();
//	auto end = v1.end();
//	ASSERT_EQ(1, *beg);
//	ASSERT_EQ(6, *(end - 1));
//}
//
//TEST(Construct_test_move_int, GetTest)
//{
//	vector<int> v = { 1, 2, 3, 4, 5, 6};
//	vector<int> v1(std::move(v));
//	ASSERT_EQ(6, v1.size());
//	ASSERT_EQ(12, v1.capacity());
//	auto beg = v1.begin();
//	auto end = v1.end();
//	ASSERT_EQ(1, *beg);
//	ASSERT_EQ(6, *(end - 1));
//}
//
//TEST(Construct_test_copy_string, GetTest)
//{
//	vector<std::string>  v = { "a", "b", "c" };
//	vector<std::string> v1(v);
//	ASSERT_EQ(3, v1.size());
//	ASSERT_EQ(6, v1.capacity());
//	auto beg = v1.begin();
//	auto end = v1.end();
//	ASSERT_EQ("a", *beg);
//	ASSERT_EQ("c", *(end - 1));
//}
//
//TEST(Construct_test_move_string, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	vector<std::string> v1(std::move(v));
//	ASSERT_EQ(3, v1.size());
//	ASSERT_EQ(6, v1.capacity());
//	auto beg = v1.begin();
//	auto end = v1.end();
//	ASSERT_EQ("a", *beg);
//	ASSERT_EQ("c", *(end - 1));
//}
//
//TEST(Operator_one, GetTest)
//{
//	vector<int> v = { 1, 2, 3 };
//	vector<int> v1;
//	v1 = v;
//	ASSERT_EQ(3, v1.size());
//	ASSERT_EQ(6, v1.capacity());
//	auto beg = v1.begin();
//	auto end = v1.end();
//	ASSERT_EQ(1, *beg);
//	ASSERT_EQ(3, *(end - 1));
//}
//
//TEST(Operator_two, GetTest)
//{
//	vector<int> v = { 1, 2, 3 };
//	vector<int> v1;
//	v1 = std::move(v);
//	ASSERT_EQ(3, v1.size());
//	ASSERT_EQ(6, v1.capacity());
//	auto beg = v1.begin();
//	auto end = v1.end();
//	ASSERT_EQ(1, *beg);
//	ASSERT_EQ(3, *(end - 1));
//}
//
//TEST(Operator_three, GetTest)
//{
//	vector<int> v = { 1, 2, 3 };
//	for (int i = 0; i < v.size(); i++)
//	{
//		ASSERT_EQ(i + 1, v[i]);
//	}
//	const vector<int> v1 = { 1, 2, 3 };
//	for (int i = 0; i < v1.size(); i++)
//	{
//		ASSERT_EQ(i + 1, v1[i]);
//	}
//}
//
//TEST(At, GetTest)
//{
//	vector<int> v = { 1, 2, 3 };
//	for (int i = 0; i < v.size(); i++)
//	{
//		ASSERT_EQ(i + 1, v.at(i));
//	}
//	const vector<int> v1 = { 1, 2, 3 };
//	for (int i = 0; i < v1.size(); i++)
//	{
//		ASSERT_EQ(i + 1, v1.at(i));
//	}
//	vector<int> v2;
//	ASSERT_THROW(v2.at(-1), std::out_of_range);
//	const vector<int> v3;
//	ASSERT_THROW(v3.at(2), std::out_of_range);
//}
//
//TEST(Swap, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	vector<std::string> v1 = { "d", "f", "g" };
//	ASSERT_EQ(3, v.size());
//	ASSERT_EQ(6, v.capacity());
//	ASSERT_EQ(3, v1.size());
//	ASSERT_EQ(6, v1.capacity());
//	auto beg = v.begin();
//	auto end = v.end();
//	auto beg1 = v1.begin();
//	auto end1 = v1.end();
//	ASSERT_EQ("a", *beg);
//	ASSERT_EQ("c", *(end - 1));
//	ASSERT_EQ("d", *beg1);
//	ASSERT_EQ("g", *(end1 - 1));
//	v1.swap(v);
//	auto b = v.begin();
//	auto en = v.end();
//	auto be1 = v1.begin();
//	auto en1 = v1.end();
//	ASSERT_EQ("d", *b);
//	ASSERT_EQ("g", *(en - 1));
//	ASSERT_EQ("a", *be1);
//	ASSERT_EQ("c", *(en1 - 1));
//}
//
//TEST(Emplace_back_int, GetTest)
//{
//	vector<int> v;
//	for (size_t i = 0; i < 10; i++)
//	{
//		v.emplace_back(i);
//	}
//	for (size_t i = 0; i < 10; i++)
//	{
//		ASSERT_EQ(i, v[i]);
//	}
//}
//
//TEST(Emplace_back_string, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	v.insert("g", 1);
//	ASSERT_EQ(4, v.size());
//	ASSERT_EQ("g", v[1]);
//	ASSERT_EQ("b", v[2]);
//	v.emplace_back("f");
//	ASSERT_EQ(5, v.size());
//	ASSERT_EQ("f", v[4]);
//}
//
//TEST(Insert_int_iterator, GetTest)
//{
//	vector<int> v;
//	for (size_t i = 0; i < 10; i++)
//	{
//		v.emplace_back(i);
//	}
//	v.insert(15, 5);
//	ASSERT_EQ(15, v[5]);
//}
//
//TEST(Insert_string, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	v.insert("g", 1);
//	ASSERT_EQ(4, v.size());
//	ASSERT_EQ("g", v[1]);
//	ASSERT_EQ("b", v[2]);
//	v.insert("f", 2);
//	ASSERT_EQ(5, v.size());
//	ASSERT_EQ("f", v[2]);
//	ASSERT_EQ("b", v[3]);
//}
//
//TEST(Push_back, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	v.push_back("g");
//	ASSERT_EQ(4, v.size());
//	ASSERT_EQ("g", *(v.end() - 1));
//	v.push_back("g");
//	v.push_back("g");
//	v.push_back("g");
//	ASSERT_EQ(12, v.capacity());
//}
//
//TEST(Pop_back_int, GetTest)
//{
//	vector<int> v;
//	for (size_t i = 0; i < 10; i++)
//	{
//		v.emplace_back(i);
//	}
//	v.pop_back();
//	ASSERT_EQ(9, *v.end());
//}
//
//TEST(Pop_back_string, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	v.push_back("g");
//	ASSERT_EQ(4, v.size());
//	ASSERT_EQ("g", *(v.end() - 1));
//	v.pop_back();
//	ASSERT_EQ(3, v.size());
//	ASSERT_EQ("c", *(v.end() - 1));
//}
//
//
//TEST(Reserve, GetTest)
//{
//	vector<std::string> v = { "a", "b", "c" };
//	v.reserve(10);
//	ASSERT_EQ(10, v.capacity());
//	ASSERT_EQ(3, v.size());
//}
