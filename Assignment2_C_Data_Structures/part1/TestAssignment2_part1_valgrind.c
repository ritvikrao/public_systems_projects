#include "myqueue.h"


// free the queue

// Fill a queue to capacity, then empty it. Refill then empty it again.
void test_queue_refill() {
  int i;
  queue_t* q1 = create_queue(5);
  for (i = 101; i <= 105; i++)
    // TEST_ASSERT_EQUAL(0, queue_enqueue(q1, i));
    queue_enqueue(q1, i);

  for (i = 101; i <= 105; i++)
    queue_dequeue(q1);

  for (i = 501; i <= 505; i++)
    // TEST_ASSERT_EQUAL(0, queue_enqueue(q1, i));
    queue_enqueue(q1, i);

  free_queue(q1);
}



// Run Unit tests using unity test-suite
int main(void) {
  RUN_TEST(test_queue_refill);
}
