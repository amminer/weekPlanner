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

//initializes the new event for setup
//important that start and stop are at their lower and upper limits respectively!
Event::Event(void)
	: start(WeekdayTime(sunday, 0, 0)),
	  stop(WeekdayTime(saturday, 24, 59)),
	  name(nullptr), location("NOT SET"), event_type("event") {}
//do not call setup from constructor - allow consuming code to decide what i/o

Event::Event(string in_name, string in_loc) //testing, will probably remove TODO
	: start(WeekdayTime(sunday, 0, 0)),
	  stop(WeekdayTime(saturday, 24, 59)),
	  name(to_dyn_charp(in_name)), location(in_loc), event_type("event") {}

Event::Event(Weekday in_start_day, int in_start_hour, int in_start_min, //testing, will probably remove TODO
			 Weekday in_stop_day,  int in_stop_hour,  int in_stop_min,
			 string in_name, string in_loc)
	: start(WeekdayTime(in_start_day, in_start_hour, in_start_min)),
	  stop( WeekdayTime(in_stop_day,  in_stop_hour,  in_stop_min )),
	  name(to_dyn_charp(in_name)), location(in_loc), event_type("event") {}
//WARNING calls new; converts a std::string to a new dynamic cstring for constr //TODO probably remove
char* Event::to_dyn_charp(const string in_str) const
{
	char* new_cstring = new char[in_str.length() + 1];
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

/*		PRIVATE FUNCTIONS		*/
//(currently these are just for use in setup)
//Wrapper to set_name(char*)
void Event::set_name(string in_name)
{
	set_name(in_name.c_str());
}

//Enforces start <= stop
void Event::set_start(string new_weekday, string new_time)
{
	WeekdayTime new_start {
		WeekdayTime(string_to_weekday(new_weekday),
					 string_to_min(new_time)) };
	if (new_start > stop){
		stringstream message;
		message << new_start << " > " << stop;
		string message_str = message.str(); //pass by ref
		throw start_greater_than_stop(message_str);
	}
	else
		start = new_start;
}

//Enforces stop >= start
void Event::set_stop(string new_weekday, string new_time)
{
	WeekdayTime new_stop {
		WeekdayTime(string_to_weekday(new_weekday),
					 string_to_min(new_time)) };
	if (new_stop < start)
		throw stop_less_than_start();
	else
		stop = new_stop;
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

//Check for overlapping times (events w/ no gaps between do not count as overlapped)
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
//	Used by client code to initialize the values of an event from cin
//all function-scope variables used to catch input are passed in as arguments
//with a default value of "_" to detect whether there was previous input.
//	*Some arguments are never passed explicitly in this implementation,
//but are still declared as arguments for ease of maintenance should new
//functionality need to be implemented.
bool Event::setup_from_cin(string new_name,		string new_loc,
						   string startweekday,	string starttime,
						   string stopweekday,	string stoptime)
{
	bool ret {true};
	try{
		if (new_name == "_"){
			cout << "Enter a name {!q to quit}: ";
			getline(cin, new_name); //not validated
			if (new_name == "!q") ret = false;
			else set_name(new_name); //no validation needed but must convert str to cstr
		}
		if (new_loc == "_" and ret){
			cout << "Enter a location {!q to quit}: ";
			getline(cin, new_loc); //not validated
			if (new_loc == "!q") ret = false;
			else location = new_loc; //data type matches and no validation needed
		}
		if ((startweekday == "_" or starttime == "_") and ret){
			cout << "When does \"" << name << "\" start?\n";
		}
		if (startweekday == "_" and ret){
			cout << "Day of week {!q to quit}: ";
			getline(cin, startweekday);
			if (startweekday == "!q") ret = false;
			else{
				//TODO slightly inefficient (extra instantiation of weekdaytime)
				set_start(startweekday, "0:00"); //validates weekday before asking for time
				
				cout << "Time {24h, h:m, !q to quit}: ";
				getline(cin, starttime);
			}
			if (starttime == "!q" or !ret) ret = false;
			else set_start(startweekday, starttime); //validates time
		}
		if ((stopweekday == "_" or stoptime == "_") and ret){
			cout << "When does \"" << name << "\" stop?\n";
		}
		if (stopweekday == "_" and ret){
			cout << "Day of week {!q to quit}: ";
			getline(cin, stopweekday);
			if (stopweekday == "!q") ret = false;
			else{
				//TODO slightly inefficient (extra instantiation of weekdaytime)
				set_stop(stopweekday, starttime); //validates weekday before asking for time
				cout << "Time {24h, h:m, !q to quit}: ";
				getline(cin, stoptime);
			}
			if (stoptime == "!q" or !ret) ret = false;
			else set_stop(stopweekday, stoptime); //validates time
		}
	}

	catch (const string_is_not_weekday& time_error){
		if (time_error.message != ""){
			cout << time_error.message;
		}
		else{
			cout << "That ";
		}
		cout << " is not a valid weekday!\nPlease try again.\n";
		return setup_from_cin(name, location);
	}

	catch (const string_is_not_time& time_error){
		if (time_error.message != ""){
			cout << time_error.message << ' ';
		}
		else{
			cout << "That ";
		}
		cout << " is not a valid time!\nPlease try again.\n";
		return setup_from_cin(name, location);
	}

	catch (const time_exception& time_error){
		cout << "Start day & time must be less than or equal to stop day & time!\n"
		 	 << time_error.message << '\n';
		cout << "Please try again.\n";
		if (stopweekday == "_") //Only works because we ask for start then stop
			return setup_from_cin(name, location, startweekday);
		else
			return setup_from_cin(name, location, startweekday, starttime, stopweekday);
	}

	return ret;
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
