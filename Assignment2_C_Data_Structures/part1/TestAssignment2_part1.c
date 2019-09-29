#include "unity.h"
#include "myqueue.h"
#include <limits.h>


// free the queue

// Fill a queue to capacity, then empty it. Refill then empty it again.
void test_queue_refill() {
	int i;
	queue_t* q1 = create_queue(5);
	for (i = 101; i <= 105; i++)
		// TEST_ASSERT_EQUAL(0, queue_enqueue(q1, i));
		TEST_ASSERT_MESSAGE(0 == queue_enqueue(q1, i), "Queue enqueue failed");

	for (i = 101; i <= 105; i++)
		TEST_ASSERT_MESSAGE(i == queue_dequeue(q1), "Queue dequeue failed");

	for (i = 501; i <= 505; i++)
		// TEST_ASSERT_EQUAL(0, queue_enqueue(q1, i));
		TEST_ASSERT_MESSAGE(0 == queue_enqueue(q1, i), "Queue enqueue failed on refill");

	free_queue(q1);
}

// Try to overfill a queue (set capacity to 10, then create a loop to try to fill with 100 items)
void test_queue_overflow() {
	int i;
	queue_t* q2 = create_queue(10);
	for (i = 301; i <= 400; i++) {
		if(i > 310) {
			TEST_ASSERT_MESSAGE(-1 == queue_enqueue(q2, i), "Queue overflow");			
		}
		else {
			TEST_ASSERT_MESSAGE(0 == queue_enqueue(q2, i), "Queue enqueue failed");
		}
	}

	free_queue(q2);
}		

// Fill the queue up halfway, empty a few items, then fill up queue until it is full
void test_queue_half_refill() {
	int i;
	queue_t* q3 = create_queue(12);
	for (i = 701; i<= 706; i++)
		TEST_ASSERT_MESSAGE(0 == queue_enqueue(q3, i), "Queue enqueue failed");

	for (i = 701; i<= 703; i++)
		TEST_ASSERT_MESSAGE(i == queue_dequeue(q3), "Queue dequeue failed");

	for (i = 701; i<= 709; i++)
		TEST_ASSERT_MESSAGE(0 == queue_enqueue(q3, i), "Queue enqueue failed");	

	TEST_ASSERT_MESSAGE(-1 == queue_enqueue(q3, 1000), "Queue overflow");
	free_queue(q3);
}

// Create a really large queue (Allocate maximum capacity MAX_INT)
void test_queue_max_int() {
	// MIGHT CRASH THE SYSTEM !!!
	// queue_t* q4 = create_queue(INT_MAX);
	// TEST_ASSERT_MESSAGE(NULL != q4, "Maximum queue creation failed");

	queue_t* q5 = create_queue(USHRT_MAX);
	TEST_ASSERT_MESSAGE(NULL != q5, "Maximum queue creation failed");
	free_queue(q5);
}

// Create a queue, add 10 items, then check that size = 10. Remove 5 items, and check that size is 5.
void test_queue_size() {
	int i;
	queue_t* q6 = create_queue(10);
	for (i = 1001; i<= 1010; i++)
		TEST_ASSERT_MESSAGE(0 == queue_enqueue(q6, i), "Queue enqueue failed");

	TEST_ASSERT_MESSAGE(10 == queue_size(q6), "Wrong queue size");

	for (i = 1001; i<= 1005; i++)
		TEST_ASSERT_MESSAGE(i == queue_dequeue(q6), "Queue dequeue failed");

	TEST_ASSERT_MESSAGE(5 == queue_size(q6), "Wrong queue size");
	free_queue(q6);		
}

// Try to remove from an empty queue.
void test_queue_empty() {
	queue_t* q7 = create_queue(5);
	TEST_ASSERT_MESSAGE(-1 == queue_dequeue(q7), "Queue underflow");	
	free_queue(q7);
}

// Run Unit tests using unity test-suite
int main(void) {
UNITY_BEGIN();
RUN_TEST(test_queue_refill);
RUN_TEST(test_queue_overflow);
RUN_TEST(test_queue_half_refill);
RUN_TEST(test_queue_max_int);
RUN_TEST(test_queue_size);
RUN_TEST(test_queue_empty);
return UNITY_END();
}
