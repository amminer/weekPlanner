#pragma once

#include <iostream>
#include <exception>
#include <locale>
#include <sstream>
#include <regex>

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

struct start_greater_than_stop:	public exception {};
struct stop_less_than_start:	public exception {};
struct string_is_not_weekday:	public exception {};
struct string_is_not_time:		public exception {};

//week starts on Sunday, should maybe change to monday? Going to be important later
enum Weekday{sunday, monday, tuesday, wednesday, thursday, friday, saturday};

//weekday-related functions in global namespace
string weekday_to_string(const Weekday);
Weekday string_to_weekday(const string);
uint hhmm_to_m(int, int);
string m_to_hhmm(uint, int=0);
uint string_to_m(string);

class WeekdayTime
{
	public: //TODO prune
		WeekdayTime(void);
		WeekdayTime(Weekday, int);
		WeekdayTime(Weekday, int, int);
		WeekdayTime(string, int);
		WeekdayTime(string, int, int);

		bool operator==(const WeekdayTime&) const; //check for overlapping times
		bool operator!=(const WeekdayTime&) const; //see above
		bool operator< (const WeekdayTime&) const; //op1 before 
		bool operator<=(const WeekdayTime&) const; //op1 before  with overlap (?)
		bool operator> (const WeekdayTime&) const; //op1 after 
		bool operator>=(const WeekdayTime&) const; //op1 after  with overlap (?)

		friend ostream& operator<<(ostream&, const WeekdayTime&);
		friend istream& operator>>(istream&, WeekdayTime&);

	private:
		Weekday weekday;
		uint minute;
};
