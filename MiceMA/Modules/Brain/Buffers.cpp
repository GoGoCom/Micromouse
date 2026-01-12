/*
 * Buffers.cpp
 *
 *  Created on: 17 Sep 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Adam Li / adam2392
*/

#include <Mouse.h>
#include <BrainConfig.h>

#include <Buffers.h>

Buffers::Buffers() {
	// TODO Auto-generated constructor stub

}

Buffers::~Buffers() {
	// TODO Auto-generated destructor stub
}

// Stack Constructor
Stack * Buffers::new_Stack() {

	Stack * this_stack = (Stack *) malloc(sizeof(Stack));

	this_stack->properties[SPI] = 0;
	this_stack->properties[SSI] = STACKSIZE;

	return this_stack;
}

Queue * Buffers::new_Queue() {

	Queue * this_queue = (Queue *) malloc(sizeof(Queue));

	this_queue->properties[QPPI] = 0;
	this_queue->properties[QPGI] = 0;
	this_queue->properties[QSI] =  QUEUESIZE;

	return this_queue;
}

// Stack Destructor
void Buffers::delete_Stack (Stack ** spp) {

	if (spp == 0 || *spp == 0) {
		printf("log NULL POINTER\n");
		return;
	}

	free(*spp);

	*spp = 0;

}

void Buffers::delete_Queue (Queue ** spp) {

	if (spp == 0 || *spp == 0) {
		printf("log NULL POINTER\n");
		return;
	}

	free(*spp);

	*spp = 0;

}

// Checks if this_stack is empty
bool Buffers::is_empty_Stack (Stack * this_stack) {

	if (debug_on)
	   printf("log %d\n", this_stack->properties[SPI]);

	if (this_stack->properties[SPI] == 0) return true;

	return false;
}


// Pops the top element of this_stack
void Buffers::pop (Stack * this_stack, Node ** npp) {


	short index;

	index = this_stack->properties[SPI] - 1;

	*npp = this_stack->the_stack[index];

	this_stack->properties[SPI] -= 1;

	if (debug_on)
		printf("log Stack Point = %d\n", this_stack->properties[SPI]);

}

// Pushes an element to the top of this_stack
void Buffers::push (Stack * this_stack, Node * this_node) {

	short index;

	index = this_stack->properties[SPI];

	this_stack->the_stack[index] = this_node;

	this_stack->properties[SPI] += 1;

	if (this_stack->properties[SPI] > this_stack->properties[SSI] )
		printf("log Over stack!\n");

	if (debug_on)
		printf("log Stack Point = %d\n", this_stack->properties[SPI]);

}

bool Buffers::is_empty_Queue (Queue * this_queue) {

	if (debug_on)
	   printf("log Queue points %d, %d\n", this_queue->properties[QPGI] , this_queue->properties[QPPI] );

	if (this_queue->properties[QPGI] == this_queue->properties[QPPI] ) return true;

	return false;
}


// Get the first element of this_queue
bool Buffers::get (Queue * this_queue, runInfo * rip) {

	short index;

	index = this_queue->properties[QPGI];

	if (index == this_queue->properties[QPPI] ) {
		printf("log Empty queue!\n");
		return false;
	}

	rip->direction = this_queue->the_queue[index].direction;
	rip->distance  = this_queue->the_queue[index].distance;

	if (index == this_queue->properties[QSI] - 1 )
		index = 0; // circular
	else
		index ++;

	this_queue->properties[QPGI] = index;

	if (debug_on)
		   printf("log Queue points %d, %d\n", this_queue->properties[QPGI] , this_queue->properties[QPPI] );

	return true;
}

// Put an element to the front of this_queue
bool Buffers::put (Queue * this_queue, runInfo  ri) {

	short old_index, new_index;

	old_index = this_queue->properties[QPPI];

	if (old_index == this_queue->properties[QSI] - 1 )
		new_index = 0; // circular
	else
		new_index = old_index + 1;

	if (this_queue->properties[QPGI] == new_index ) {
			printf("log full queue!\n");
			return false;
	}

	this_queue->the_queue[old_index].direction = ri.direction;
	this_queue->the_queue[old_index].distance  = ri.distance;

	this_queue->properties[QPPI] = new_index;

	if (debug_on)
		   printf("log Queue points %d, %d\n", this_queue->properties[QPGI] , this_queue->properties[QPPI] );

	return true;

}
