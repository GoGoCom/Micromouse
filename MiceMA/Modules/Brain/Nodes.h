/*
 * Nodes.h
 *
 *  Created on: 18 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Adam Li / adam2392
*/
#ifndef NODES_H_
#define NODES_H_

typedef struct Node { /* data fields */

	bool  visited;
	short floodval;

	uint8_t x;
	uint8_t y;
	uint8_t exitedDir  : 4;
	uint8_t enteredDir : 4;
	uint8_t pathCount  : 2;
	uint8_t passCount[4];        // each direction's pass count
	struct Node * neighbours[4]; //  pointers to neighbors

} Node;

class Nodes {
public:
	Nodes();
	virtual ~Nodes();

	int debug_on = false;    /* debug flag */

	// Node Functions
	Node * new_Node (const uint8_t x, const uint8_t y); // (x, y)
	void delete_Node (Node ** npp);

};

#endif /* NODES_H_ */
