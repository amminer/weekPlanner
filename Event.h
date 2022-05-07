#pragma once

#include "WeekdayTime.h"
#include <cstring>
#include <iostream>
#include <sstream>

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

/*	IO EXCEPTIONS	*/
struct must_be_positive_int: public invalid_argument
{
	must_be_positive_int(const string& new_message="");
};

class Event
{
	public:
		//this is the only constructor that will be called from the finished code
		Event(string);			//delete other constrs? Would still be good for testing?
		Event(void);			//for testing class functionality w/o all user input
		Event(string, string);	//for testing class functionality w/o all user input
		Event(Weekday, int, int, Weekday, int, int, string, string); //see above
		Event(const Event&);
		virtual ~Event();

		Event& operator=(const Event&); //called by copy constr

		bool operator==(const Event&) const; //check for overlapping times
		bool operator!=(const Event&) const; //see ==
		bool operator< (const Event&) const; //op1 before 
		bool operator<=(const Event&) const; //op1 before  with overlap (?)
		bool operator> (const Event&) const; //op1 after 
		bool operator>=(const Event&) const; //op1 after  with overlap (?)

		friend ostream& operator<<(ostream&, const Event&); // display
		friend istream& operator>>(istream&, Event&); // wrapper for setup

		//called from top level UI code to prompt user
		virtual bool setup_from_cin(string="_", string="_", string="_", string="_", string="_", string="_");

	protected:
		//used to translate string i/o; calls new; needed for init lists
		char* to_dyn_charp(const string) const; //no ref arg, accepts literals

	private:
		WeekdayTime start;
		WeekdayTime stop;
		char* name;			//requirements list an inherited char*
		string location;
		string event_type;

		//validation/setter functions called by setup func(s)
		void set_name(const char*); //also used by copy constructor
		void set_name(string&); //wrapper for set_name(const char*)
		void set_start(string&, string&);
		void set_stop(string&, string&);
};

class Dinner; //Flight depends on Dinner - further declared below
class Flight: public Event
{
	public:
		Flight(void);
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
		~Yoga(void);

		friend ostream& operator<<(ostream&, const Yoga&); // display

		bool setup_from_cin(bool base_set=false, string bpm_in="-1", string skill_in="-1");
	private:
		int resting_heart_rate;		//safety reasons
		int skill_level;

		void set_resting_heart_rate(int bpm_in);
		void set_skill_level(int skill_in);
};
