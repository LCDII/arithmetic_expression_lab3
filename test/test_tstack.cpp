#include <gtest.h>

#include"TStack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int>s(5));
}
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int>s(MAX_STACK_SIZE + 1));
}
TEST(TStack, cant_create_stack_with_length_less_then_1)
{
	ASSERT_ANY_THROW(TStack<int>s(-1));
}
TEST(TStack, can_create_copied_stack)
{
	TStack<int> s(10);

	ASSERT_NO_THROW(TStack<int> s1(s));
}
TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> s(2);
	s.push(1);
	s.push(2);
	TStack<int> s1(s);
	EXPECT_EQ(s.pop(), s1.pop());
	EXPECT_EQ(s.pop(), s1.pop());
}
TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> s(2);
	s.push(1);	
	s.push(2);	
	TStack<int> s1(s);
	s.pop();
	s.pop();
	s.push(0);
	s.push(0);
	EXPECT_NE(s.pop(), s1.pop());
	EXPECT_NE(s.pop(), s1.pop());
}
TEST(TStack, can_be_full)
{
	TStack<int> s(2);
	s.push(1);
	s.push(2);
	EXPECT_EQ(s.isFull(), true);
}
TEST(TStack, can_be_empty)
{
	TStack<int> s(2);
	EXPECT_EQ(s.isEmpty(), true);
}
TEST(TStack, can_push)
{
	TStack<int> s(2);
	ASSERT_NO_THROW(s.push(0));
}
TEST(TStack, can_pop)
{
	TStack<int> s(2);
	s.push(0);
	ASSERT_NO_THROW(s.pop());

}
TEST(TStack, can_top)
{
	TStack<int> s(2);
	s.push(0);
	ASSERT_NO_THROW(s.top());
}
TEST(TStack, cant_push_when_full)
{
	TStack<int> s(2);
	s.push(0);
	s.push(0);
	ASSERT_ANY_THROW(s.push(0));
}
TEST(TStack, cant_pop_when_empty)
{
	TStack<int> s(2);
	ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, cant_top_when_empty)
{
	TStack<int> s(2);
	ASSERT_ANY_THROW(s.top());
}

