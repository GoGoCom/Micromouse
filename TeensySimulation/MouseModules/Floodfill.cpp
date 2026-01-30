/*
 * Floodfill.cpp
 *
 *  Created on: 13 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Adam Li / adam2392
*/
#include <Mice.h>
#include <BrainConfig.h>

#include <Floodfill.h>


Floodfill::Floodfill() {
	// TODO Auto-generated constructor stub

}

Floodfill::~Floodfill() {
	// TODO Auto-generated destructor stub
}

/* main function for updating the flood values of this node */
void Floodfill::flood_fill (Node * this_node, Stack * this_stack, const short reflood_flag) {

	short status;  /* Flag for updating the flood value or not */

	if (debug_on)
		printf("log In flood_fill (%d, %d) \n", this_node->x, this_node->y);

	/* we want to avoid flooding the goal values - this is for non-reverse */
	if (!reflood_flag)
		if (this_node->y == GoalUpper || this_node->y == GoalLower )
    		if (this_node->x == GoalLeft || this_node->x == GoalRight )
    			return;

	/* we want to avoid flooding the goal values - this is reverse */
	if (reflood_flag)
		if (this_node->y == START_Y && this_node->x == START_X)
    		return;

	/* is the cell (1 + minumum OPEN adjascent cell) ? */
	status = floodval_check (this_node);

	/* if no, update curent cell's flood values,
	   then push open adjascent neighbors to stack. */
	if (!status) {
		update_floodval(this_node); /* Update floodval to 1 + min open neighbor */
		push_open_neighbors(this_node, this_stack); /* pushed, to be called later */
	}

	if (debug_on)
		printf ("log Exiting flood_fill (%d, %d)\n", this_node->x, this_node->y);

}

/* helper function for flood_fill
   checks if this node already fulfills flood value requirements*/
short Floodfill::floodval_check(Node * this_node) {
	// return a flag determining wheter this node should be updated
	//   aka, is this Node 1 + min open adj cell?
	if (get_smallest_neighbor (this_node) + 1 == this_node->floodval)
		return true;

	return false;
}


/* helper fuction for flood_fill
   updates this node's flood value to 1 greater than the smallest neighbor*/
void Floodfill::update_floodval (Node * this_node) {
	// set this node's value to 1 + min open adjascent cell
	this_node->floodval = get_smallest_neighbor (this_node) + 1;

	if (debug_on)
		printf("log setText %02d %02d %3hd %8x %8x %8x %8x\n", this_node->x ,this_node->y, this_node->floodval , (unsigned int ) this_node->neighbours[WEST],(unsigned int ) this_node->neighbours[EAST], (unsigned int ) this_node->neighbours[NORTH], (unsigned int ) this_node->neighbours[SOUTH]  );
}

/* pushes the open neighboring cells of this node to the stack */
void Floodfill::push_open_neighbors (Node * this_node, Stack * this_stack) {
	// A NULL neighbor represents a wall.
	// if neighbor is accessible, push it onto stack!
	for(int i=0; i<4; i++) {

		if (this_node->neighbours[i]  != NULL && this_node->neighbours[i]->neighbours[dir_info[i].opposite]!= NULL)
			bufs.push (this_stack, this_node->neighbours[i]);

	}
}

/* function for obtaining this_node's smallest neighbor's floodval */
short Floodfill::get_smallest_neighbor (Node * this_node) {
	// The Node's floodval will be 1 higher than the neigboring cell
	short smallestneighbor = LARGEVAL;

	for(int i=0; i<4; i++) {
		if ( this_node->neighbours[i] != NULL && ( this_node->neighbours[i]->neighbours[dir_info[i].opposite] != NULL) && this_node->neighbours[i]->floodval < smallestneighbor )
			smallestneighbor = this_node->neighbours[i]->floodval;
	}
	return smallestneighbor;
}

/* function for obtaining this nodes's smallest neighbor's direction */
short Floodfill::get_smallest_neighbor_dir (Node * this_node, const short preferred_dir) {
	short smallestval;		/* smallest neighbor value */

	/* get the smallest neighboring flood_val */
	smallestval = get_smallest_neighbor(this_node);

	/* A BUNCH OF DEBUG STATEMENTS! */
	if (debug_on) {
    	printf("log preferred_dir: %hd\n", preferred_dir);
    	printf("log smallestval: %hd\n", smallestval);
    	printf("log neighboring floodvals:\n");

    	for(int i=0; i<4; i++) {
       		if (this_node->neighbours[i] != NULL) {
        		printf("log this_node->%d: %hd\n", i, this_node->neighbours[i]->floodval);
        		if (this_node->neighbours[i]->floodval == smallestval)
        			printf("log %d cell reachable\n", i);
       		}

    	}

	}

	if ((this_node->neighbours[preferred_dir] != NULL) && (this_node->neighbours[preferred_dir]->floodval == smallestval)) return preferred_dir;

	for(int i=0; i<4; i++) {
		if ((this_node->neighbours[i] != NULL) && (this_node->neighbours[i]->floodval == smallestval) && (this_node->neighbours[i]->visited == false))   return i;
	}

	for(int i=0; i<4; i++) {
		if ((this_node->neighbours[i] != NULL) && (this_node->neighbours[i]->floodval == smallestval) ) return i;
	}

	printf("log unreachable! %d %d - %d\n", this_node->x, this_node->y, smallestval);
	return  15; // direction error
}


