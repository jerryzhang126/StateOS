#include "test.h"

static unsigned sent = 0;
static unsigned received = 0;

static void proc1()
{
	unsigned length;

 	length = stm_wait(&stm0, &received, sizeof(received));
 	                                             assert(length == sizeof(received));
 	                                             assert(sent == received);
	        tsk_stop();
}

static void proc2()
{
	unsigned event;

	        sent = rand();
	event = stm_give(&stm0, &sent, sizeof(sent));
	                                             assert_success(event);
	        tsk_stop();
}

static void test()
{
	unsigned event;
		                                         assert_dead(tsk1);
	        tsk_startFrom(tsk1, proc1);
		                                         assert_dead(tsk2);
	        tsk_startFrom(tsk2, proc2);
	event = tsk_join(tsk2);                      assert_success(event);
	event = tsk_join(tsk1);                      assert_success(event);
}

void test_stream_buffer_0()
{
	int i;
	TEST_Notify();
	for (i = 0; i < PASS; i++)
		test();
}
