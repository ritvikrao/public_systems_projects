#include "unity.h"
#include "mystack.h"
#include <limits.h>


// free the queue

// Fill a stack to capacity, then empty it. Refill then empty it again.
void test_stack_refill() {
	int i;
	stack_t* q1 = create_stack(5);
	for (i = 101; i <= 105; i++)
		// TEST_ASSERT_EQUAL(0, stack_enqueue(q1, i));
		TEST_ASSERT_MESSAGE(0 == stack_enqueue(q1, i), "Stack enqueue failed");

	for (i = 105; i >= 101; i--)
		TEST_ASSERT_MESSAGE(i == stack_dequeue(q1), "Stack dequeue failed");
	for (i = 501; i <= 505; i++)
		// TEST_ASSERT_EQUAL(0, stack_enqueue(q1, i));
		TEST_ASSERT_MESSAGE(0 == stack_enqueue(q1, i), "Stack enqueue failed on refill");

	free_stack(q1);
}

// Try to overfill a stack (set capacity to 10, then create a loop to try to fill with 100 items)
void test_stack_overflow() {
	int i;
	stack_t* q2 = create_stack(10);
	for (i = 301; i <= 400; i++) {
		if(i > 310) {
			TEST_ASSERT_MESSAGE(-1 == stack_enqueue(q2, i), "Stack overflow");			
	}
		else {
			TEST_ASSERT_MESSAGE(0 == stack_enqueue(q2, i), "Stack enqueue failed");
		}
	}

	free_stack(q2);
}		

// Fill the stack up halfway, empty a few items, then fill up stack until it is full
void test_stack_half_refill() {
	int i;
	stack_t* q3 = create_stack(12);
	for (i = 701; i<= 706; i++)
		TEST_ASSERT_MESSAGE(0 == stack_enqueue(q3, i), "Stack enqueue failed");
	for (i = 706; i > 703; i--)
		TEST_ASSERT_MESSAGE(i == stack_dequeue(q3), "Stack dequeue failed");
	for (i = 704; i<= 712; i++)
		TEST_ASSERT_MESSAGE(0 == stack_enqueue(q3, i), "Stack enqueue failed");	

	TEST_ASSERT_MESSAGE(-1 == stack_enqueue(q3, 1000), "Stack overflow");
	free_stack(q3);
}

// Create a really large stack (Allocate maximum capacity MAX_INT)
void test_stack_max_int() {
	// MIGHT CRASH THE SYSTEM !!!
	// stack_t* q4 = create_stack(INT_MAX);
	// TEST_ASSERT_MESSAGE(NULL != q4, "Maximum stack creation failed");

	stack_t* q5 = create_stack(USHRT_MAX);
	TEST_ASSERT_MESSAGE(NULL != q5, "Maximum stack creation failed");
	free_stack(q5);
}

// Create a queue, add 10 items, then check that size = 10. Remove 5 items, and check that size is 5.
void test_stack_size() {
	int i;
	stack_t* q6 = create_stack(10);
	for (i = 1001; i<= 1010; i++)
		TEST_ASSERT_MESSAGE(0 == stack_enqueue(q6, i), "Stack enqueue failed");

	TEST_ASSERT_MESSAGE(10 == stack_size(q6), "Wrong stack size");

	for (i = 1010; i>= 1006; i--){
		TEST_ASSERT_MESSAGE(i == stack_dequeue(q6), "Stack dequeue failed");
	}

	TEST_ASSERT_MESSAGE(5 == stack_size(q6), "Wrong stack size");
	free_stack(q6);		
}

// Try to remove from an empty queue.
void test_stack_empty() {
	stack_t* q7 = create_stack(5);
	TEST_ASSERT_MESSAGE(-1 == stack_dequeue(q7), "Stack underflow");	
	free_stack(q7);
}

// Run Unit tests using unity test-suite
int main(void) {
UNITY_BEGIN();
RUN_TEST(test_stack_refill);
RUN_TEST(test_stack_overflow);
RUN_TEST(test_stack_half_refill);
RUN_TEST(test_stack_size);
RUN_TEST(test_stack_empty);
return UNITY_END();
}
