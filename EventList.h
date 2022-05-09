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
		//default destructor and cpy constr are ok, no dyn mem

		friend ostream& operator<<(ostream&, EventList&); //instead of display()...

		//these use exception handling, no returns needed
		void add_event(void); //prompts user, inserts to one of the LLL members
		void remove_event(void); //prompts user, calls a remove_type helper

	private:
		int week_num;
		LLL<Flight> flights;
		LLL<Dinner> dinners;
		LLL<Yoga> yogas;

		bool remove_flight(string&);
		bool remove_dinner(string&);
		bool remove_yoga(string&);
		void remove_event(Event& name_to_match); //must pass an object since DLL is templated
		void display_chronological(size_t=0, size_t=0, size_t=0) const;
		bool creates_name_conflict(const string& new_name) const; //wrapper, calls each of the following:
		bool creates_name_conflict(const string& new_name, const LLL<Flight>& check_list) const; //returning true if any
		bool creates_name_conflict(const string& new_name, const LLL<Dinner>& check_list) const; //of these helpers
		bool creates_name_conflict(const string& new_name, const LLL<Yoga>& check_list) const;   //return true.
		bool creates_time_conflict(Event*) const;   //wrapper; based on input subtype, calls...
		bool creates_time_conflict(Flight*) const;  //...this,
		bool creates_time_conflict(Dinner*) const;  //or this,
		bool creates_time_conflict(Yoga*) const;    //or this to allow some overlaps but not others.
};
