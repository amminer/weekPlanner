#pragma once

#include "LinkedList.h"
#include "Event.h"
#include <algorithm>	//std::min_element

/* Amelia Miner
 * 05/06/22
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		EventList.h
 * PURPOSE:		Class EventList uses a doubly linked list (class LLL) to store a
 *				collection of Event objects, limiting addition of new events if
 *				their WeekdayTime members create a scheduling conflict.
 */

class EventList
{
	public:
		EventList(void);
		EventList(int);

		friend ostream& operator<<(ostream&, EventList&); //instead of display()...

		void add_event(void);

	private:
		int week_num;
		LLL<Flight> flights;
		LLL<Dinner> dinners;
		LLL<Yoga> yogas;

		void display_chronological(size_t=0, size_t=0, size_t=0);
		bool is_in_conflict(Event*);   //wrapper; based on input subtype, calls...
		bool is_in_conflict(Flight*);  //...this,
		bool is_in_conflict(Dinner*);  //or this,
		bool is_in_conflict(Yoga*);    //or this to allow some overlaps but not others.
};
