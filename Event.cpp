#include "Event.h"

/* Ameli Miner
nPolicy RemoteSigned -Scope CurrentUser'
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
	: start(WeekdayTime(sunday, 0, 0)),
	  stop(WeekdayTime(saturday, 24, 59)),
	  name(nullptr), location("NOT SET"), event_type("event") {}

//Initializes the new event for setup.
//Important that start and stop are at their lower and upper limits respectively!
//(This is the constructor that is called from derived constructors)
Event::Event(const string type)
	: start(WeekdayTime(sunday, 0, 0)),
	  stop(WeekdayTime(saturday, 24, 59)),
	  name(nullptr), location("NOT SET"), event_type(type) {}

//Used to create a key to pass as a reference to linkedlist lookup function
//since list checks for matching names using Event::operator==(Event&) and
//knows nothing about event internals (templated)
Event::Event(const string& new_name, const string& new_type)
	: name(nullptr), event_type(new_type)
{
	set_name(new_name);
}

//for testing class Event&derived, not for use in client code
Event::Event(Weekday in_start_day, int in_start_hour, int in_start_min,
			 Weekday in_stop_day,  int in_stop_hour,  int in_stop_min,
			 string in_name, string in_loc)
	: start(WeekdayTime(in_start_day, in_start_hour, in_start_min)),
	  stop( WeekdayTime(in_stop_day,  in_stop_hour,  in_stop_min )),
	  name(nullptr), location(in_loc), event_type("event")
{
	set_name(in_name);
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

bool Event::operator==(const Event& op2) const
{
	return strcmp(name, op2.name) == 0;
}

bool Event::operator!=(const Event& op2) const //see ==
{
	return !( *this == op2 );
}

bool Event::operator< (const Event& op2) const //op1 before 
{
	//return (stop < op2.start); //old method, must not overlap
	return (start < op2.start);
}

bool Event::operator<=(const Event& op2) const //op1 before  with overlap (?)
{
	return (*this < op2)
		or (*this == op2);
	// old return (stop <= op2.stop and stop > op2.start);
}

bool Event::operator> (const Event& op2) const //op1 after 
{
	//return (start > op2.stop); //old method, must not overlap
	return (start > op2.start);
}

bool Event::operator>=(const Event& op2) const //op1 after  with overlap (?)
{
	return (*this > op2)
		or (*this == op2);
	// old return (start >= op2.start and start < op2.stop);
}

/*		PUBLIC FUNCTIONS		*/

//Check for overlapping times (events w/ no gaps between do not count as overlapped)
//DOES NOT imply containment-in-time - no need for this behavior for now,
//but can be achieved using combinations of existing operators, probably
bool Event::overlaps(const Event& other) const
{
	return (stop > other.start and stop <= other.stop)
		or (stop > other.start and start < other.stop);
}

//	Used by client code to initialize the values of an event from cin.
//	All function-scope variables used to catch input are passed in as args
//with a default value of "_" to detect whether there was previous input.
//	*Some arguments are never passed explicitly in this implementation,
//but are still declared as arguments for ease of maintenance should new
//functionality need to be implemented.
//	this recursive-to-a-point-in-execution behavior makes the function very
//long, but I think it is worthwhile - how could I break this up into helpers?
bool Event::setup_from_cin(string new_name,		string new_loc,
						   string startweekday,	string starttime,
						   string stopweekday,	string stoptime)
{
	bool ret {true}; //maybe should've started with false...
	//VOID no longer doing this to simplify client code; just check weekday and time at once
	//string default_start = "00:00"; //used temporarily to check input
	//string default_stop  = "23:59";
	try{
		if (new_name == "_"){
			cout << "Enter a name {!q to cancel}: ";
			getline(cin, new_name); //not validated
			if (new_name == "!q") ret = false;
			else set_name(new_name); //no validation needed but must convert str to cstr
		}
		if (new_loc == "_" and ret){
			cout << "Enter a location {!q to cancel}: ";
			getline(cin, new_loc); //not validated
			if (new_loc == "!q") ret = false;
			else location = new_loc; //data type matches and no validation needed
		}
		if ((startweekday == "_" or starttime == "_") and ret){
			cout << "When does \"" << name << "\" start?\n";
		}
		if (startweekday == "_" and ret){
			cout << "Day of week {!q to cancel}: ";
			getline(cin, startweekday);
			if (startweekday == "!q") ret = false;
			else{
				//slightly inefficient (extra instantiation of weekdaytime)...
				//set_start(startweekday, default_start); //validates weekday before time
				cout << "Time {24h, h:m, !q to cancel}: ";
				getline(cin, starttime);
			}
			if (starttime == "!q" or !ret) ret = false;
			else set_start(startweekday, starttime); //validates time
		}
		if ((stopweekday == "_" or stoptime == "_") and ret){
			cout << "When does \"" << name << "\" stop?\n";
		}
		if (stopweekday == "_" and ret){
			cout << "Day of week {!q to cancel}: ";
			getline(cin, stopweekday);
			if (stopweekday == "!q") ret = false;
			else{
				//slightly inefficient (extra instantiation of weekdaytime)...
				//set_stop(stopweekday, default_stop); //validates weekday before time
				cout << "Time {24h, h:m, !q to cancel}: ";
				getline(cin, stoptime);
			}
			if (stoptime == "!q" or !ret) ret = false;
			else set_stop(stopweekday, stoptime); //validates time
		}
	}

	catch (const string_is_not_weekday& time_error){
		if (*time_error.what() != '\0'){
			cout << time_error.what();
		}
		else{
			cout << "That ";
		}
		cout << " is not a valid weekday!\nPlease try again.\n";
		return setup_from_cin(name, location);
	}

	catch (const string_is_not_time& time_error){
		if (*time_error.what() != '\0'){
			cout << time_error.what() << ' ';
		}
		else{
			cout << "That";
		}
		cout << " is not a valid time!\nPlease try again.\n";
		return setup_from_cin(name, location);
	}

	catch (const time_exception& time_error){
		cout << "Start day & time must be less than or equal to stop day & time!\n";
		if (*time_error.what() != '\0')
		 	 cout << time_error.what() << '\n';
		cout << "Please try again.\n";
		return setup_from_cin(name, location);
	}
	return ret;
}

string Event::get_name(void) const
{
	return string(name); //no internal string to reference, must return value
}

/*		PRIVATE FUNCTIONS		*/
//(currently these are just for use in setup)

//Wrapper to set_name(char*)
void Event::set_name(const string& in_name)
{
	set_name(in_name.c_str());
}

//Enforces start <= stop
void Event::set_start(const string& new_weekday, const string& new_time)
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
void Event::set_stop(const string& new_weekday, const string& new_time)
{
	WeekdayTime new_stop {
		WeekdayTime(string_to_weekday(new_weekday),
					 string_to_min(new_time)) };
	if (new_stop < start){
		stringstream message;
		message << new_stop << " < " << start;
		string message_str = message.str(); //pass by ref
		throw stop_less_than_start(message_str);
	}
	else
		stop = new_stop;
}


/*	CLASS FLIGHT	*/
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/
Flight::Flight(void)
	: Event("flight"), bags_checked(-1), bags_carryon(-1) {}

//Used to create a key to pass as a reference to linkedlist lookup function
//since list checks for matching names using Event::operator==(Event&) and
//knows nothing about event internals (templated)
Flight::Flight(const string& new_name)
	: Event(new_name, "flight_key") {}

Flight::Flight(const Flight& cpy) //may not be necessary, event cpy constr sufficient?
	: Event(static_cast<const Event&>(cpy)),
	  bags_checked(cpy.bags_checked), bags_carryon(cpy.bags_carryon) {}

Flight::~Flight(void) {} //must overload virtual base destructor

/*		OPERATORS		*/
ostream& operator<<(ostream& out, const Flight& op2)
{
	out << static_cast<const Event&>(op2) << '\n';
	out << "bags: " << op2.bags_checked << " checked, "
		<< op2.bags_carryon << " carry-on";
	return out;
} 

/*		PUBLIC FUNCTIONS		*/
//on bad input, does not currently reset to user's last correct input, can be implemented if desired
//by changing how error is thrown/caught
bool Flight::setup_from_cin(bool base_set, string checked_in, string carryon_in)
{
	bool ret {true};
	if (!base_set) ret = Event::setup_from_cin();
	if (ret){ //guards against user quitting from event::setup
		try{
			if (checked_in == "-1"){
				cout << "Checked bags {!q to cancel}: ";
				getline(cin, checked_in);
				if (checked_in == "!q") ret = false;
				else set_bags_checked(stoi(checked_in));
			}
			if (carryon_in == "-1" and ret){
				cout << "Carry-on bags {!q to cancel}: ";
				getline(cin, carryon_in);
				if (carryon_in == "!q") ret = false;
				else set_bags_carryon(stoi(carryon_in));
			}
		}

		catch (invalid_argument& int_error){
			cout << "Input be zero or a positive whole number!\n"; //not specifying bags, flexible?
			if (*int_error.what() != '\0')
				cout << '(' << int_error.what() << " is not valid)\n";
			cout << "Please try again.\n";
			return Flight::setup_from_cin(true);
		}
	}
	return ret;
}

/*		PRIVATE FUNCTIONS		*/
void Flight::set_bags_checked(const int checked_in){
	if (checked_in < 0)
		throw invalid_argument(to_string(checked_in));
	else
		bags_checked = checked_in;
}

void Flight::set_bags_carryon(const int carryon_in){
	if (carryon_in < 0)
		throw invalid_argument(to_string(carryon_in));
	else
		bags_carryon = carryon_in;
}

/*	CLASS DINNER	*/
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/
Dinner::Dinner(void)
	: Event("dinner"), num_guests(-1), food_allergies(nullptr) {}

//Used to create a key to pass as a reference to linkedlist lookup function
//since list checks for matching names using Event::operator==(Event&) and
//knows nothing about event internals (templated)
Dinner::Dinner(const string& new_name)
	: Event(new_name, "dinner_key"), food_allergies(nullptr) {}

Dinner::Dinner(const Dinner& cpy)
	: Event(static_cast<const Event&>(cpy)),
	  num_guests(cpy.num_guests), food_allergies(nullptr)
{
	food_allergies = new char[strlen(cpy.food_allergies) + 1];
	strcpy(food_allergies, cpy.food_allergies);
}

Dinner::~Dinner(void)
{
	if (food_allergies)
		delete [] food_allergies;
}
/*		OPERATORS		*/
ostream& operator<<(ostream& out, const Dinner& op2)
{
	out << static_cast<const Event&>(op2) << '\n';
	out << "guests: " << op2.num_guests << '\n'
		<< "allergies: "  << op2.food_allergies;
	return out;
} 

/*		PUBLIC FUNCTIONS		*/
//on bad input, does not currently reset to user's last correct input, can be implemented if desired
//by changing how error is thrown/caught
bool Dinner::setup_from_cin(bool base_set, string guests_in, string allergies_in)
{
	bool ret {true};
	if (!base_set) ret = Event::setup_from_cin();
	if (ret){ //guards against user quitting from event::setup
		try{
			if (guests_in == "-1"){
				cout << "Number of guests {!q to cancel}: ";
				getline(cin, guests_in);
				if (guests_in == "!q") ret = false;
				else set_num_guests(stoi(guests_in));
			}
			if (allergies_in == "_" and ret){
				cout << "Enter food allergies for your table(s)\n{!q to cancel, enter if none}: ";
				getline(cin, allergies_in);
				if (allergies_in == "!q") ret = false;
				else set_allergies(allergies_in);
			}
		}

		catch (invalid_argument& int_error){
			cout << "Input be a positive whole number!\n"; //not specifying bags, flexible?
			if (*int_error.what() != '\0')
				cout << '(' << int_error.what() << " is not valid)\n";
			cout << "Please try again.\n";
			guests_in = "-1"; 
			return Dinner::setup_from_cin(true);
		}
	}
	return ret;
}

/*		PRIVATE FUNCTIONS		*/
void Dinner::set_allergies(string& allergies_in)
{
	if (allergies_in == "")
		allergies_in = "None";
	set_allergies(allergies_in.c_str());
}
void Dinner::set_allergies(const char* allergies_in)
{
	if (food_allergies)
		delete [] food_allergies;
	food_allergies = new char[strlen(allergies_in) + 1];
	strcpy(food_allergies, allergies_in);
}

void Dinner::set_num_guests(const int guests_in)
{
	if (guests_in < 0)
		throw invalid_argument(to_string(guests_in));
	else
		num_guests = guests_in;
}

/*	CLASS YOGA	*/
/*		CONSTRUCTORS, DESTRUCTORS, helpers		*/
Yoga::Yoga(void)
	: Event("yoga"), resting_heart_rate(-1), skill_level(-1) {}

//Used to create a key to pass as a reference to linkedlist lookup function
//since list checks for matching names using Event::operator==(Event&) and
//knows nothing about event internals (templated)
Yoga::Yoga(const string& new_name)
	: Event(new_name, "yoga_key") {}

Yoga::Yoga(const Yoga& cpy) //may not be necessary, base copy constr is sufficient?
	: Event(static_cast<const Event&>(cpy)),
	  resting_heart_rate(cpy.resting_heart_rate),
	  skill_level(cpy.skill_level) {}

Yoga::~Yoga(void) {} //must overload virtual base destructor

/*		OPERATORS		*/
ostream& operator<<(ostream& out, const Yoga& op2)
{
	out << static_cast<const Event&>(op2) << '\n';
	out << "resting heart rate: " << op2.resting_heart_rate << '\n'
		<< "skill level: "  << op2.skill_level;
	return out;
} 

/*		PUBLIC FUNCTIONS		*/
//on bad input, does not currently reset to user's last correct input, can be implemented if desired
//by changing how error is thrown/caught
bool Yoga::setup_from_cin(bool base_set, string bpm_in, string skill_in)
{
	bool ret {true};
	if (!base_set) ret = Event::setup_from_cin();
	if (ret){ //guards against user quitting from event::setup
		try{
			if (bpm_in == "-1"){
				cout << "Your resting heart rate {!q to cancel}: ";
				getline(cin, bpm_in);
				if (bpm_in == "!q") ret = false;
				else set_resting_heart_rate(stoi(bpm_in));
			}
			if (skill_in == "-1" and ret){
				cout << "Your skill level from 1 to 10 {!q to cancel}: ";
				getline(cin, skill_in);
				if (skill_in == "!q") ret = false;
				else set_skill_level(stoi(skill_in));
			}
		}

		catch (invalid_argument& int_error){
			cout << "Input be a positive whole number!\n"; //not specifying bags, flexible?
			if (*int_error.what() != '\0')
				cout << '(' << int_error.what() << " is not valid)\n";
			cout << "Please try again.\n";
			return Yoga::setup_from_cin(true);
		}
	}
	return ret;
}

/*		PRIVATE FUNCTIONS		*/
void Yoga::set_resting_heart_rate(const int bpm_in)
{
	if (bpm_in <=0)
		throw invalid_argument(to_string(bpm_in));
	else
		resting_heart_rate = bpm_in;
}

void Yoga::set_skill_level(const int skill_in)
{
	if (skill_in <= 0)
		throw invalid_argument(to_string(skill_in));
	else
		skill_level = skill_in; //accepts braggart values (>10)
}
