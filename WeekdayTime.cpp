#include "WeekdayTime.h"

/* Amelia Miner
 * 04/29/22
 * cs 202 section 003
 * PROGRAM #:		2
 * FILE:			WeekdayTime.cpp
 * PURPOSE: 		Class WeekdayTime is composed of an enum to
 *					represent the day of the week and an int to
 *					represent the minute of the day.
 *					Implementation depends on iostream, std::string
 *					and associated functions.
 */

/*	I/O EXCEPTIONS	*/
time_exception::time_exception(const string& new_message)
	: runtime_error(new_message) {}
//inherits time_exception
start_greater_than_stop::start_greater_than_stop(const string& new_message)	
	: time_exception(new_message) {}
//inherits time_exception
stop_less_than_start::stop_less_than_start(const string& new_message)
	: time_exception(new_message) {}

string_is_not_weekday::string_is_not_weekday(const string& new_message)
	: runtime_error(new_message) {}

string_is_not_time::string_is_not_time(const string& new_message)
	: runtime_error(new_message) {}

/*		PUBLIC, GLOBAL FUNCTIONS		*/
string to_lower(const string& in_string)
{
	stringstream out_ss;
	for (size_t i=0; i < in_string.length(); ++i){
		out_ss << (char) tolower(in_string[i]);
	}
	return out_ss.str();
}

//returns the string representation of a weekday enum-int-thing
string weekday_to_string(const Weekday day)
{
	switch (day){
		case sunday:
			return "sunday";
		case monday:
			return "monday";
		case tuesday:
			return "tuesday";
		case wednesday:
			return "wednesday";
		case thursday:
			return "thursday";
		case friday:
			return "friday";
		case saturday:
			return "saturday";
		default:
			return "ERROR";
	}
}

//returns a member of weekday enum based on string input
Weekday string_to_weekday(const string& day)
{
	string lday = to_lower(day);
	if 		(lday == "sunday" or lday == "sun")
		return sunday;
	else if (lday == "monday" or lday == "mon")
		return monday;
	else if (lday == "tuesday" or lday == "tue")
		return tuesday;
	else if (lday == "wednesday" or lday == "wed")
		return wednesday;
	else if (lday == "thursday" or lday == "thu")
		return thursday;
	else if (lday == "friday" or lday == "fri")
		return friday;
	else if (lday == "saturday" or lday == "sat")
		return saturday;
	else
		throw string_is_not_weekday(day);
}

//returns the number of minutes from midnight to the time passed in
//with the argument formatted "h:m", "hh:m", "h:mm", or "hh:mm"
//lest an exception be thrown
uint string_to_min(string timestring)
{
	regex pattern {"([0]?[0-9]|[1][0-9]|[2][0-3]):([0-5]?[0-9])"};
	smatch sm;
	if (regex_match(timestring, sm, pattern); sm.size() == 3)
		return hhmm_to_m(stoi(sm[1]), stoi(sm[2]));
	else
		throw string_is_not_time(timestring);
}

//converts hour & minute input into minutes-from-midnight output
uint hhmm_to_m(const int hr, const int min)
{
	if (hr <= 0)
		return (uint) min;
	else
		return (uint) 60 + hhmm_to_m(hr-1, min);
}

//converts minutes-from-midnight input into hour & minute output
string m_to_hhmm(uint out_min, int out_hr)
{
	if (out_min < 0)
		return "ERROR";
	else if (out_min <= 9)
		return to_string(out_hr) + ":0" + to_string(out_min);
	else if (out_min < 60)
		return to_string(out_hr) + ':' + to_string(out_min);
	else
		return m_to_hhmm(out_min - 60, out_hr + 1);
}

WeekdayTime::WeekdayTime(void)
	: weekday(sunday), minute(0) {}

//should only be used if you've converted a time to minutes-from-midnight
WeekdayTime::WeekdayTime(const Weekday in_weekday, const int in_minute)
	:weekday(in_weekday), minute(in_minute) {}

//should be called with a 24-hour hour and a minute-within-that-hour
WeekdayTime::WeekdayTime(const Weekday in_weekday, const int in_hour, const int in_minute)
	:weekday(in_weekday), minute(hhmm_to_m(in_hour, in_minute)) {}

//should only be used if you've converted a time to minutes-from-midnight
WeekdayTime::WeekdayTime(const string in_weekday, const int in_minute)
	:weekday(string_to_weekday(in_weekday)), minute(in_minute) {}

//should be called with a 24-hour hour and a minute-within-that-hour
WeekdayTime::WeekdayTime(const string in_weekday, const int in_hour, const int in_minute)
	:weekday(string_to_weekday(in_weekday)), minute(hhmm_to_m(in_hour, in_minute)) {}

bool WeekdayTime::operator==(const WeekdayTime& op2) const
{
	return weekday == op2.weekday and minute == op2.minute;
}

bool WeekdayTime::operator!=(const WeekdayTime& op2) const
{
	return !( *this == op2 );
}

bool WeekdayTime::operator< (const WeekdayTime& op2) const
{
	return ( weekday < op2.weekday )
		or ( weekday == op2.weekday and minute < op2.minute );
}

bool WeekdayTime::operator<=(const WeekdayTime& op2) const
{
	return ( weekday < op2.weekday )
		or ( weekday == op2.weekday and minute <= op2.minute );
}

bool WeekdayTime::operator> (const WeekdayTime& op2) const
{
	return ( weekday > op2.weekday )
		or ( weekday == op2.weekday and minute > op2.minute );
}

bool WeekdayTime::operator>=(const WeekdayTime& op2) const
{
	return ( weekday > op2.weekday )
		or ( weekday == op2.weekday and minute >= op2.minute );
}

ostream& operator<<(ostream& out, const WeekdayTime& op2)
{
	out << weekday_to_string(op2.weekday)
		<< " at " << m_to_hhmm(op2.minute);
	return out;
}

//allows user to set minute, not really useful but had to define this op
istream& operator>>(istream& in, WeekdayTime& op2)
{
	in >> op2.minute;
	in.clear();
	in.ignore(100, '\n');
	return in;
}
