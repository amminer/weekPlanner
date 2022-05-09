#pragma once

#include "WeekdayTime.h"
#include <cstring>
#include <iostream>
#include <sstream> //allows use of operator<< to throw exception w/ message

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
	public:
		Event(void);
		//this is the only constructor that will be called from the finished code
		//used to initialize an event for storage in practice
		Event(const string); //arg is not ref so it can handle string literals
		Event(const string&, const string&);	//for creating a key to lookup in template DLL
		Event(Weekday, int, int, Weekday, int, int, string, string); //for testing
		Event(const Event&);
		virtual ~Event();

		Event& operator=(const Event&); //called by copy constr

		bool operator==(const Event&) const; //returns whether names match
		bool operator!=(const Event&) const; //see ==
		bool operator< (const Event&) const; //op1 before 
		bool operator<=(const Event&) const; //op1 before  with overlap (?)
		bool operator> (const Event&) const; //op1 after 
		bool operator>=(const Event&) const; //op1 after  with overlap (?)

		friend ostream& operator<<(ostream&, const Event&); // display
		friend istream& operator>>(istream&, Event&); // wrapper for setup

		//called from top level UI code to prompt user
		virtual bool setup_from_cin(string="_", string="_", string="_",
									string="_", string="_", string="_");
		//used for simple display in client code, a case where a getter is ok?
		string get_name(void) const; //no internal string to reference, must return value
		//used to check for overlap with another event (end-to-end is not overlap!)
		bool overlaps(const Event& other) const;

	private:
		WeekdayTime start;
		WeekdayTime stop;
		char* name;			//requirements list an inherited char*
		string location;
		string event_type; //this may not be necessary since dynamic_cast is a thing,
						   //but it does simplify some things

		//validation/setter functions called by setup func(s)
		void set_name(const char*); //also used by copy constructor
		void set_name(const string&); //wrapper for set_name(const char*)
		void set_start(string&, string&);
		void set_stop(string&, string&);
};

class Dinner; //Flight depends on Dinner - further declared below
class Flight: public Event
{
	public:
		Flight(void);
		Flight(const string&); //used to make a key for lookup in template LLL
		Flight(const Flight& cpy);
		~Flight(void);

		//combines times, results in name "<flightname> + dinner for <dinnersz>"
		Flight operator+(const Dinner&) const; 
		Flight& operator+=(const Dinner&);
		friend ostream& operator<<(ostream&, const Flight&); // display

		bool setup_from_cin(bool base_set=false, string checked_in="-1", string carryon_in="-1");
	private:
		int bags_checked;
		int bags_carryon;

		void set_bags_checked(int checked_in);
		void set_bags_carryon(int carryon_in);
};

//Dinner depends on Flight - declared above.
class Dinner: public Event
{
	public:
		Dinner(void);
		Dinner(const string&); //used to make a key for lookup in template LLL
		Dinner(const Dinner& cpy);
		~Dinner(void);

		// combines times, results in name "<dinnername> + flight to <flightdest>"
		Dinner operator+(const Flight&) const;
		Dinner& operator+=(const Flight&);
		friend ostream& operator<<(ostream&, const Dinner&); // display

		bool setup_from_cin(bool base_set=false, string guests_in="-1", string allergies_in="_");
	private:
		int num_guests;
		char* food_allergies;	//requirements list a derived char*

		void set_num_guests(int guests_in);
		void set_allergies(string& allergies_in);
		void set_allergies(const char* allergies_in);
};

class Yoga: public Event
{
	public:
		Yoga(void);
		Yoga(const string&); //used to make a key for lookup in template LLL
		Yoga(const Yoga& cpy);
		~Yoga(void);

		friend ostream& operator<<(ostream&, const Yoga&); // display

		bool setup_from_cin(bool base_set=false, string bpm_in="-1", string skill_in="-1");
	private:
		int resting_heart_rate;		//safety reasons
		int skill_level;

		void set_resting_heart_rate(int bpm_in);
		void set_skill_level(int skill_in);
};
