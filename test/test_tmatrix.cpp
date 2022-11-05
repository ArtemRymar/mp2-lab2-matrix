#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;

	ASSERT_NO_THROW(TDynamicMatrix<int> v1(v));
	TDynamicMatrix<int> v1(v);
	EXPECT_EQ(1, v == v1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> v1(v);
	v = v * 0;

	EXPECT_EQ(0, v1[0][0]);
	EXPECT_EQ(1, v1[0][1]);
	EXPECT_EQ(2, v1[1][0]);
	EXPECT_EQ(3, v1[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> v(4);
	EXPECT_EQ(4, v.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;

	EXPECT_EQ(0, v[0][0]);
	EXPECT_EQ(1, v[0][1]);
	EXPECT_EQ(2, v[1][0]);
	EXPECT_EQ(3, v[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> v(2);
	ASSERT_ANY_THROW(v.at(-1, 0) = 3);
	ASSERT_ANY_THROW(v.at(0, -1) = 3);
	ASSERT_ANY_THROW(v.at(-1, -1) = 3);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(2);
	ASSERT_ANY_THROW(v.at(MAX_MATRIX_SIZE + 1, 0) = 3);
	ASSERT_ANY_THROW(v.at(0, MAX_MATRIX_SIZE + 1) = 3);
	ASSERT_ANY_THROW(v.at(MAX_MATRIX_SIZE + 1, MAX_MATRIX_SIZE + 1) = 3);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;

	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(0, v[0][0]);
	EXPECT_EQ(1, v[0][1]);
	EXPECT_EQ(2, v[1][0]);
	EXPECT_EQ(3, v[1][1]);

}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> v1(2);

	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(0, v1[0][0]);
	EXPECT_EQ(1, v1[0][1]);
	EXPECT_EQ(2, v1[1][0]);
	EXPECT_EQ(3, v1[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> v1(4);
	TDynamicMatrix<int> v2(1);

	ASSERT_NO_THROW(v1 = v);
	ASSERT_NO_THROW(v2 = v);
	EXPECT_EQ(2, v1.size());
	EXPECT_EQ(2, v2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> v1(4);

	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(0, v1[0][0]);
	EXPECT_EQ(1, v1[0][1]);
	EXPECT_EQ(2, v1[1][0]);
	EXPECT_EQ(3, v1[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> v1(v);

	EXPECT_EQ(1, v == v1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;

	EXPECT_EQ(1, v == v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> v1(5);

	EXPECT_EQ(0, v == v1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> res(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> v1(v);

	ASSERT_NO_THROW(res = v + v1);
	EXPECT_EQ(0, res[0][0]);
	EXPECT_EQ(2, res[0][1]);
	EXPECT_EQ(4, res[1][0]);
	EXPECT_EQ(6, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> v1(4);

	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> res(2);
	v[0][0] = 0; v[0][1] = 1; v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> v1(v); v1 = v1 * 2;

	ASSERT_NO_THROW(res = v1 - v);
	EXPECT_EQ(0, res[0][0]);
	EXPECT_EQ(1, res[0][1]);
	EXPECT_EQ(2, res[1][0]);
	EXPECT_EQ(3, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> v1(4);

	ASSERT_ANY_THROW(v - v1);
}

