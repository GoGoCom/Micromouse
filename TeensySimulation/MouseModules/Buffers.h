/*
 * Buffers.h
 *
 *  Created on: 13 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Adam Li / adam2392
*/

#ifndef BUFFERS_H_
#define BUFFERS_H_

#include <Nodes.h>

// Buffer Constants
#define SPI 1			// Stack Pointer Index
#define SSI 0 			// Stack Size Index
#define STACK_OFFSET 2
#define STACKSIZE 8192 //4096

#define QPPI 2			// Queue Pointer Put Index
#define QPGI 1			// Queue Pointer Get Index
#define QSI 0 			// Queue Size Index
#define QUEUE_OFFSET 3
#define QUEUESIZE 500 //255  //1024

typedef struct runInfo {
	uint8_t distance;
	uint8_t direction;
} runInfo ;

typedef struct Stack {
	short properties [STACK_OFFSET];
	Node * the_stack [STACKSIZE];
} Stack;

typedef struct Queue {
	uint8_t mouse_dir;
	short properties [QUEUE_OFFSET];
	runInfo the_queue [QUEUESIZE];
} Queue;

class Buffers {
public:
	Buffers();
	virtual ~Buffers();

	bool debug_on = false;    /* debug flag */

	// Stack Functions
	Stack * new_Stack();
	void delete_Stack (Stack ** spp);
	bool is_empty_Stack (Stack * this_stack);
	void pop (Stack * this_stack, Node ** npp);
	void push (Stack * this_stack, Node * this_node);

	// Queue Functions
	Queue * new_Queue();
	void delete_Queue (Queue ** spp);
	bool is_empty_Queue (Queue * this_queue);
	bool get (Queue * this_Queue, runInfo *rip);
	bool put (Queue * this_Queue, runInfo ri);

};


#endif /* BUFFERS_H_ */
