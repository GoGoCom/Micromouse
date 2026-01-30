/*
 * Nodes.cpp
 *
 *  Created on: 18 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Adam Li / adam2392
 */
#include <Mice.h>
#include <BrainConfig.h>

#include <Nodes.h>

Nodes::Nodes() {
	// TODO Auto-generated constructor stub

}

Nodes::~Nodes() {
	// TODO Auto-generated destructor stub
}


/* Node Constructor */
Node * Nodes::new_Node (const uint8_t x, const uint8_t y) {

	Node * this_node;

	if (debug_on)
		printf("log allocating %hd, %hd\n", x, y);

	this_node = (Node *) malloc(sizeof(Node));

	this_node->x = x;
	this_node->y = y;
	this_node->visited = false;
	this_node->pathCount =  0;

	for(int i=0; i<4; i++)
		this_node->passCount[i] = 0;  // 0 : no used
	//

	this_node->enteredDir = 15;
	this_node->exitedDir  = 15;


	if (x < GoalRight && y < GoalUpper)
		this_node->floodval = (GoalRight - 1 - x) + (GoalUpper - 1 - y) ;
	else if (x < GoalRight && y >= GoalUpper)
		this_node->floodval = (GoalRight - 1 - x) + (y - GoalUpper) ;
	else if (x >= GoalRight && y < GoalUpper)
		this_node->floodval = (x - GoalRight) + (GoalUpper - 1 - y) ;
	else
		this_node->floodval = (x - GoalRight) + (y - GoalUpper) ;

	return this_node;
}

/* Node Destructor */
void Nodes::delete_Node (Node ** npp) {

	/* debug statements */
	if (debug_on)
		printf("log deallocating %d, %d\n", (*npp)->x, (*npp)->y);

	free (*npp);
	*npp = 0;
}

/*** Node Functions ***/





