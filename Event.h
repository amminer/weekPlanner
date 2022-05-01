#pragma once

#include"WeekdayTime.h"
#include<iostream>

using namespace std;
typedef unsigned short uint;

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
	public:
		Event(WeekdayTime strt, WeekdayTime stp, char* nm, char* lctn);
		Event(const Event& cpy);
		~Event();

		Event& operator=(const Event&); //called by copy constr

		bool operator==(const Event&) const; //check for overlapping times
		bool operator!=(const Event&) const; //see above
		bool operator< (const Event&) const; //op1 before 
		bool operator<=(const Event&) const; //op1 before  with overlap (?)
		bool operator> (const Event&) const; //op1 after 
		bool operator>=(const Event&) const; //op1 after  with overlap (?)

		friend ostream& operator<<(ostream&, const Event&);
		friend istream& operator>>(istream&, Event&);

	private:
		WeekdayTime start;
		WeekdayTime stop;
		char* name;			//requirements list an inherited char*
		string location;
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
