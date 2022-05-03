#include "Event.h"

/* Amelia Miner
 * 04/29/22
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		Event.cpp
 * PURPOSE:		Base class Event & derived classes Flight, Dinner, and Yoga.
 *				Implementation depends on iostream, std::string
 *				and associated functions.
 */

/*	CLASS EVENT	*/
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/

Event::Event(void)
	: name(nullptr) {}

Event::Event(string in_name, string in_loc)
	: start(WeekdayTime(sunday, 0, 0)),
	  stop(WeekdayTime(saturday, 24, 59)),
	  name(to_dyn_charp(in_name)), location(in_loc), event_type("event") {}

Event::Event(Weekday in_start_day, int in_start_hour, int in_start_min,
			 Weekday in_stop_day,  int in_stop_hour,  int in_stop_min,
			 string in_name, string in_loc)
	: start(WeekdayTime(in_start_day, in_start_hour, in_start_min)),
	  stop( WeekdayTime(in_stop_day,  in_stop_hour,  in_stop_min )),
	  name(to_dyn_charp(in_name)), location(in_loc), event_type("event") {}
//WARNING calls new; converts a string to a new dynamic cstring
char* Event::to_dyn_charp(const string in_str) const
{
	char* new_cstring = new char[in_str.length() + 1]; //+1 for null term
	strcpy(new_cstring, in_str.c_str());
	return new_cstring;
}

Event::Event(const Event& cpy)
	: start(cpy.start), stop(cpy.stop), name(nullptr),
	  location(cpy.location), event_type(cpy.event_type)
{
	set_name(cpy.name);
}
//WARNING calls new
void Event::set_name(const char* in_name)
{
	if (name)
		delete [] name;
	name = new char[strlen(in_name) + 1];
	strcpy(name, in_name);
}

Event::~Event(void)
{
	if (name)
		delete [] name;
}

/*		OPERATORS		*/

Event& Event::operator=(const Event& op2)
{
	set_name(op2.name);
	location = op2.location;
	start = op2.start;
	stop = op2.stop;
	event_type = op2.event_type;
	return *this;
}

ostream& operator<<(ostream& out, const Event& op2)
{
	out << op2.event_type << ": " << op2.name << " at " << op2.location << '\n'
		<< "start: " << op2.start << "\nstop:  " << op2.stop;
	return out;
} 

istream& operator>>(istream& in, Event& op2)
{
	string temp_name;
	getline(in, temp_name);
	op2.set_name(temp_name.c_str());
	return in;
}

//check for overlapping times (events w/ no gaps between do not count as overlapped)
//DOES NOT check for strict containment - no need for this behavior for now
bool Event::operator==(const Event& op2) const
{
	return (stop > op2.start and stop <= op2.stop)
		or (stop > op2.start and start < op2.stop);
	/* old - keeping in case bugs appear, but tested new code thoroughly and pretty sure this code sucks
	return (start >= op2.start and stop <= op2.stop) // 2 contains 1
		or (start <= op2.start and stop >= op2.stop) // 1 contains 2
		or (stop <= op2.stop and stop > op2.start) // 1 into 2
		or (stop >= op2.stop and start < op2.stop);// 2 into 1
	//make the 3rd anded condition >=/<= instead of >/< to include end-to-end events
	*/
}

bool Event::operator!=(const Event& op2) const //see ==
{
	return !( *this == op2 );
}

bool Event::operator< (const Event& op2) const //op1 before 
{
	return (stop < op2.start);
}

bool Event::operator<=(const Event& op2) const //op1 before  with overlap (?)
{
	return (*this < op2)
		or (*this == op2);
	// old return (stop <= op2.stop and stop > op2.start);
}

bool Event::operator> (const Event& op2) const //op1 after 
{
	return (start > op2.stop);
}

bool Event::operator>=(const Event& op2) const //op1 after  with overlap (?)
{
	return (*this > op2)
		or (*this == op2);
	// old return (start >= op2.start and start < op2.stop);
}

/*		PUBLIC FUNCTIONS		*/

void Event::set_name(string in_name)
{
	set_name(in_name.c_str());
}

void Event::set_start(string new_weekday, string new_time)
{
	auto new_start {
		WeekdayTime(string_to_weekday(new_weekday),
					 string_to_m(new_time)) };
	if (new_start > stop)
		throw start_greater_than_stop();
	else
		start = new_start;
}

void Event::set_stop(string new_weekday, string new_time)
{
	auto new_stop {
		WeekdayTime(string_to_weekday(new_weekday),
					 string_to_m(new_time)) };
	if (new_stop < start)
		throw stop_less_than_start();
	else
		stop = new_stop;
}

/*	CLASS FLIGHT	*/ //TODO
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/
/*		OPERATORS		*/
/*		PUBLIC FUNCTIONS		*/
/*	CLASS DINNER	*/ //TODO
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/
/*		OPERATORS		*/
/*		PUBLIC FUNCTIONS		*/
/*	CLASS YOGA	*/ //TODO
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/
/*		OPERATORS		*/
/*		PUBLIC FUNCTIONS		*/
