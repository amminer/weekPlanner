#pragma once

#include "WeekdayTime.h"
#include <cstring>
#include <iostream>

using namespace std;

/* Amelia Miner
 * 04/29/22
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		Event.h
 * PURPOSE:		Contains a base class Event and three derived
 *				classes Flight, Dinner, and Yoga.
 *				Event objects are composed of one WeekdayTime to
 *				represent start time, one for stop time, two char*s
 *				for name and location, and derived data depending
 *				on the subclass.
 *				These classes + the linked list and node class templates
 *				are for operator overloading practice.
 */

class Event
{
	public: //TODO prune
		Event(void);
		Event(string in_name, string in_loc);
		Event(Weekday, int, int, Weekday, int, int, string, string);
		Event(const Event&);
		~Event();

		Event& operator=(const Event&); //called by copy constr

		bool operator==(const Event&) const; //check for overlapping times
		bool operator!=(const Event&) const; //see ==
		bool operator< (const Event&) const; //op1 before 
		bool operator<=(const Event&) const; //op1 before  with overlap (?)
		bool operator> (const Event&) const; //op1 after 
		bool operator>=(const Event&) const; //op1 after  with overlap (?)

		friend ostream& operator<<(ostream&, const Event&);
		friend istream& operator>>(istream&, Event&);

		void set_name(string); //wrapper for set_name(const char*)
		void set_start(string, string);
		void set_stop(string, string);

	private:
		WeekdayTime start;
		WeekdayTime stop;
		char* name;			//requirements list an inherited char*
		string location;
		string event_type;

		char* to_dyn_charp(const string) const; //used to translate string i/o; calls new
		void set_name(const char*); //used by copy constructor to set name
};

class Dinner; //Flight depends on Dinner - further declared below
class Flight: public Event
{
	public:
		Flight(WeekdayTime strt, WeekdayTime stp, char* nm, char* lctn); //TODO
		//combines times, results in name "<flightname> + dinner for <dinnersz>"
		Flight operator+(const Dinner&) const; 
		Flight& operator+=(const Dinner&);

	private:
		string destination;
		uint num_bags;
};

//Dinner depends on Flight - declared above.
class Dinner: public Event
{
	public:
		Dinner(WeekdayTime strt, WeekdayTime stp, char* nm, char* lctn); //TODO
		// combines times, results in name "<dinnername> + flight to <flightdest>"
		Dinner operator+(const Flight&) const;
		Dinner& operator+=(const Flight&);

	private:
		uint num_diners;
		char* food_allergies;	//requirements list a derived char*
};

class Yoga: public Event
{
	public:
		Yoga(WeekdayTime strt, WeekdayTime stp, char* nm, char* lctn); //TODO

	private:
		uint resting_heart_rate;		//safety reasons
		uint skill_level;
};
