#include <gtest.h>

#include"TQueue.h"

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int>q(5));
}
TEST(TQueue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(TQueue<int>q(MAX_QUEUE_SIZE+1));
}
TEST(TQueue, cant_create_queue_with_length_less_then_2)
{
	ASSERT_ANY_THROW(TQueue<int>q(-1));
}
TEST(TQueue, can_create_copied_queue)
{
	TQueue<int> q(10);

	ASSERT_NO_THROW(TQueue<int> q1(q));
}
TEST(TQueue, copied_queue_is_equal_to_source_one)
{
	TQueue<int> q(2);
	q.push(1);
	q.push(2);
	TQueue<int> q1(q);
	EXPECT_EQ(q.pop(), q1.pop());
	EXPECT_EQ(q.pop(), q1.pop());
}
TEST(TQueue, copied_queue_has_its_own_memory)
{
	TQueue<int> q(2);
	q.push(1);
	q.push(2);
	TQueue<int> q1(q);
	q.pop();
	q.pop();
	q.push(0);
	q.push(0);
	EXPECT_NE(q.pop(), q1.pop());
	EXPECT_NE(q.pop(), q1.pop());
}
TEST(TQueue, can_be_full)
{
	TQueue<int> q(2);
	q.push(1);
	q.push(2);
	EXPECT_EQ(q.isFull(), true);
}
TEST(TQueue, can_be_empty)
{
	TQueue<int> q(2);
	EXPECT_EQ(q.isEmpty(), true);
}
TEST(TQueue, can_push)
{
	TQueue<int> q(2);
	ASSERT_NO_THROW(q.push(0));
}
TEST(TQueue, can_pop)
{
	TQueue<int> q(2);
	q.push(0);
	ASSERT_NO_THROW(q.pop());
}
TEST(TQueue, can_top)
{
	TQueue<int> q(2);
	q.push(0);
	ASSERT_NO_THROW(q.top());
}
TEST(TQueue, cant_push_when_full)
{
	TQueue<int> q(2);
	q.push(0);
	q.push(0);
	ASSERT_ANY_THROW(q.push(0));
}
TEST(TQueue, cant_pop_when_empty)
{
	TQueue<int> q(2);
	ASSERT_ANY_THROW(q.pop());
}
TEST(TQueue, cant_top_when_empty)
{
	TQueue<int> q(2);
	ASSERT_ANY_THROW(q.top());
}
TEST(TQueue, compare_equal_queues_return_true)
{
	TQueue<int> q1(2);
	TQueue<int> q2(2);
	q1.push(2);
	q1.push(3);
	q2.push(2);
	q2.push(3);
	EXPECT_EQ(q1 == q2, true);
}
TEST(TQueue, compare_not_equal_queues_return_false)
{
	TQueue<int> q1(2);
	TQueue<int> q2(2);
	q1.push(3);
	q1.push(2);
	q2.push(2);
	q2.push(3);
	EXPECT_EQ(q1 != q2, true);
}

