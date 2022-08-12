#pragma once

#include "LinkedList.h"
#include "Event.h"
#include <algorithm>	//std::min_element, std::distance

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
		//EventList(void); //not needed?
		EventList(int);
		//default destructor and cpy constr are ok, no dyn mem

		friend ostream& operator<<(ostream&, const EventList&); //instead of display()...

		//these use exception handling, no returns needed
		void add_event(void); //prompts user, inserts to one of the LLL members
		void remove_event(void); //prompts user, calls a remove_type helper

	private:
		int week_num;
		LLL<Flight> flights;
		LLL<Dinner> dinners;
		LLL<Yoga> yogas;

		void display_chronological(size_t=0, size_t=0, size_t=0) const;
		bool remove_flight(const string&);
		bool remove_dinner(const string&);
		bool remove_yoga(const string&);
		bool creates_name_conflict(const string& new_name) const; //wrapper, calls each of the following:
		bool creates_name_conflict(const string& new_name, const LLL<Flight>& check_list) const; //returning true if any
		bool creates_name_conflict(const string& new_name, const LLL<Dinner>& check_list) const; //of these helpers
		bool creates_name_conflict(const string& new_name, const LLL<Yoga>& check_list) const;   //return true.
		bool creates_time_conflict(Event*) const;   //wrapper; based on input subtype, calls...
		bool creates_time_conflict(const Flight*) const;  //...this,
		bool creates_time_conflict(const Dinner*) const;  //or this,
		bool creates_time_conflict(const Yoga*) const;    //or this to allow some overlaps but not others.
		//these bools could be void and throw exceptions, but I already wrote exception handling into events
		//so I can just do it this way right? Hope this is ok!
};
