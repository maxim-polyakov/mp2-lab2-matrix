#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(10);

	ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector <int> v1(6);
	TVector <int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	int size = 3;
	TVector<int> a(size);
	TVector<int> b = a;

	EXPECT_NE(&a, &b);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);

	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(4, 2);

	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, checking_filling_memory) {
	TVector<int> v(2);

	EXPECT_EQ(0, v[0]);
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}
//----------------------------------------------------------------
TEST(TVector, throws_when_set_element_with_negative_index)
{
	int size = 3;
	TVector<int> a(size);

	ASSERT_ANY_THROW(a[-1] = 0);
}
//----------------------------------------------------------------
TEST(TVector, throws_when_set_element_with_too_large_index)
{
	int size = 3;
	TVector<int> a(size);

	ASSERT_ANY_THROW(a[MAX_VECTOR_SIZE + 1] = 0);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(10);
	EXPECT_TRUE(v == v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v(2);
	TVector<int> v1(2);

	v[0] = 1;
	v[1] = 2;

	v1 = v;

	EXPECT_EQ(v1, v);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> a(3);
	a = TVector<int>(4);

	EXPECT_EQ(4, a.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v(3);
	TVector<int> v1(2);

	v[0] = 1;
	v[1] = 2;
	v[2] = 3;

	v1 = v;

	EXPECT_EQ(v1, v);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector <int> v1(6);
	TVector <int> v2(6);
	EXPECT_TRUE(v2 == v1);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> a(2);

	EXPECT_TRUE(a == a);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector <int> v1(6);
	TVector <int> v2(13);

	EXPECT_TRUE(v1 != v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector <int> v1(3);
	TVector <int> v2(3);
	TVector <int> res(3);
	v1[0] = 1;
	v1[2] = 3;

	v2[0] = 2;
	v2[1] = 1;
	v2[2] = 4;
	res = v1 + 1;

	EXPECT_EQ(res, v2);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector <int> v1(3);
	TVector <int> v2(3);
	TVector <int> res(3);
	v1[0] = 1;
	v1[2] = 3;

	v2[0] = 0;
	v2[1] = -1;
	v2[2] = 2;
	res = v1 - 1;

	EXPECT_EQ(res, v2);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector <int> v1(3);
	TVector <int> v2(3);
	TVector <int> res(3);
	v1[0] = 1;
	v1[2] = 3;

	v2[0] = 2;
	v2[1] = 0;
	v2[2] = 6;
	res = v1 * 2;

	EXPECT_EQ(res, v2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> a(2), b(2);
	TVector<int> actual(2);
	TVector<int> expected(2);
	a[0] = 1;
	a[1] = 2;

	b[0] = 1;
	b[1] = 2;

	actual = a + b;

	expected[0] = 2;
	expected[1] = 4;

	EXPECT_EQ(expected, actual);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(3);

	ASSERT_ANY_THROW(a + b);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> a(2), b(2);
	TVector<int> actual(2);
	TVector<int> expected(2);
	a[0] = 2;
	a[1] = 4;

	b[0] = 1;
	b[1] = 3;

	actual = a - b;

	expected[0] = 1;
	expected[1] = 1;

	EXPECT_EQ(expected, actual);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(3);

	ASSERT_ANY_THROW(a - b);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> a(2), b(2);
	TVector<int> actual(2);
	TVector<int> expected(2);
	a[0] = 2;
	a[1] = 4;

	b[0] = 1;
	b[1] = 3;

	actual = a * b;

	expected[0] =2 ;
	expected[1]=12;

	EXPECT_EQ(expected, actual);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> a(2), b(3);

	ASSERT_ANY_THROW(a*b);
}


