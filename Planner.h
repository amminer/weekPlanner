#pragma once

#include "EventList.h"
#include <list> //have to use something other than vector for asgmt2.
//In reality using a list here is kind of silly; internally it's
//implemented as a DLL, so you get constant time insertion and removal
//but slow lookup. We barely ever have to add or remove elements (weeks)
//to the planner compared to how often we have to look them up,
//so something with constant time lookup like a dynamic array
//might make more sense; vector is implemented as a dynamic array.

/* Amelia Miner
 * 05/08/2022
 * cs 202 section 003
 * PROGRAM #:		2
 * FILE:			Planner.h
 * PURPOSE: 		Uses std::list to maintain a collection 
 *					of EventLists representing consecutive weeks.
 *					Handles basic user I/O,
 *					scheduling conflicts are handled on a weekly
 *					basis inside class EventList.
 */

class Planner
{
	public:
		Planner(void); //called by main loop
		//default destructor and cpy constr are ok, no dyn mem

	private:
		list<EventList> weeks;

		help(void); //loosely explains how to use the program
};
