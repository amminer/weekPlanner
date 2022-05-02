#pragma once

#include <iostream>

using namespace std;
typedef unsigned int uint;

/* Amelia Miner
 * 04/29/22
 * cs 202 section 003
 * PROGRAM #:		2
 * FILE:			WeekdayTime.h
 * PURPOSE: 		Class WeekdayTime is composed of an enum to
 *					represent the day of the week and an int to
 *					represent the minute of the day.
 *					WeekdayTimes are meant to represent only one point
 *					in time, to be used as the start or stop value for
 *					class Event.
 */

//week starts on Sunday, should maybe change to monday? Going to be important later
enum Weekday{sunday, monday, tuesday, wednesday, thursday, friday, saturday};

class WeekdayTime
{
	public:
		WeekdayTime(Weekday, int);
		WeekdayTime(Weekday, int, int);

		bool operator==(const WeekdayTime&) const; //check for overlapping times
		bool operator!=(const WeekdayTime&) const; //see above
		bool operator< (const WeekdayTime&) const; //op1 before 
		bool operator<=(const WeekdayTime&) const; //op1 before  with overlap (?)
		bool operator> (const WeekdayTime&) const; //op1 after 
		bool operator>=(const WeekdayTime&) const; //op1 after  with overlap (?)

		friend ostream& operator<<(ostream&, const WeekdayTime&);
		friend istream& operator>>(istream&, WeekdayTime&);

		uint hhmm_to_m(int, int) const;
		string m_to_hhmm(uint, int=0) const;
		string weekday_to_string(Weekday) const;

	private:
		Weekday weekday;
		uint minute;
};
