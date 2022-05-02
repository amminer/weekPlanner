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

//should only be used if you've converted a time to minutes-from-midnight
WeekdayTime::WeekdayTime(Weekday in_weekday, int in_minute)
	:weekday(in_weekday), minute(in_minute) {}

//should be called with a 24-hour hour and a minute-within-that-hour
WeekdayTime::WeekdayTime(Weekday in_weekday, int in_hour, int in_minute)
	:weekday(in_weekday), minute(hhmm_to_m(in_hour, in_minute)) {}

uint WeekdayTime::hhmm_to_m(int hr, int min) const
{
	if (hr <= 0)
		return (uint) min;
	else
		return (uint) 60 + hhmm_to_m(hr-1, min);
}

string WeekdayTime::m_to_hhmm(uint out_min, int out_hr) const
{
	if (out_min < 0)
		return "ERROR";
	else if (out_min <= 0)
		return to_string(out_hr) + ":0" + to_string(out_min);
	else if (out_min < 60)
		return to_string(out_hr) + ':' + to_string(out_min);
	else
		return m_to_hhmm(out_min - 60, out_hr + 1);
}

string WeekdayTime::weekday_to_string(Weekday day) const
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

bool WeekdayTime::operator==(const WeekdayTime& op2) const
{
	return weekday == op2.weekday and minute == op2.minute;
}

bool WeekdayTime::operator!=(const WeekdayTime& op2) const
{
	return !( *this == op2 );
}

//op1 before 
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
	out << op2.weekday_to_string(op2.weekday)
		<< " at " << op2.m_to_hhmm(op2.minute);
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
