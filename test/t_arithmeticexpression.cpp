#include <gtest.h>

#include"ArithmeticExpression.h"	
#include"Exceptions.h"
#include"string"

TEST(ArithmeticExpression, cant_create_empty_expression)
{
	string s = "";
	ASSERT_ANY_THROW(ArithmeticExpression ae(s));
}
TEST(ArithmeticExpression, stops_when_chain_is_ended)
{
	string s = "2+3";
	ASSERT_NO_THROW(ArithmeticExpression ae(s));
}
TEST(ArithmeticExpression, throws_when_lexis_error)
{
	string s = "A+B";
	EXPECT_THROW(ArithmeticExpression ae(s), LanguageException);
}
TEST(ArithmeticExpression, throws_when_syntax_error)
{
	string s = "(34**56)";
	EXPECT_THROW(ArithmeticExpression ae(s), SyntaxisException);
}
TEST(ArithmeticExpression, can_count_unar)
{
	string s = "1-(-1)";
	ArithmeticExpression ae(s);
	int a = ae.getAnswer();
	EXPECT_EQ(ae.getAnswer(), 2);
}
TEST(ArithmeticExpression, can_create_copy_of_expression)
{
	string s = "54+76";
	ArithmeticExpression ae(s);
	ASSERT_NO_THROW(ArithmeticExpression a(ae));
}