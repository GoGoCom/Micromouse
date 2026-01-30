/*
 * Floodfill.h
 *
 *  Created on: 13 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Adam Li / adam2392
*/

#ifndef FLOODFILL_H_
#define FLOODFILL_H_

#include <Buffers.h>
#include <Nodes.h>

class Floodfill {
public:
	Floodfill();
	virtual ~Floodfill();

	int debug_on = false;    /* debug flag */

	Buffers bufs;

	void flood_fill (Node * this_node, Stack * this_stack, const short reflood_flag) ;
	short floodval_check(Node * this_node) ;
	void update_floodval (Node * this_node);
	short get_smallest_neighbor (Node * this_node);
	void push_open_neighbors (Node * this_node, Stack * this_stack);
	short get_smallest_neighbor_dir (Node * this_node, const short preferred_dir);
};

#endif /* FLOODFILL_H_ */
