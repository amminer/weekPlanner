#include "Event.h"

void compare(Event& a, Event& b)
{
	if (a < b)
		cout << a << "\nless than\n" << b << '\n';
	else if (a > b)
		cout << a << "\ngreater than\n" << b << '\n';
	else
		cout << a << "\nequal to\n" << b << '\n';
}

void test_add_event(void)
{
	string name, loc, startweekday, stopweekday, starttime, stoptime;
	cout << "Adding new event...\n"
		 << "Enter a name: ";
	getline(cin, name);
	cout << "Enter a location: ";
	getline(cin, loc);
	auto new_event {Event(name, loc)};

	cout << "When does it start?\n"
		 << "Day of week: ";
	getline(cin, startweekday);
	new_event.set_start(startweekday, "0:00"); //error checking
	cout << "Time: ";
	getline(cin, starttime);
	new_event.set_start(startweekday, starttime); //actual value

	cout << "When does it stop?\n"
		 << "Day of week: ";
	getline(cin, stopweekday);
	new_event.set_stop(stopweekday, starttime); //error checking
	cout << "Time: ";
	getline(cin, stoptime);
	new_event.set_stop(stopweekday, stoptime); //actual value

	cout << "Your new event:\n" << new_event << '\n';
}

int main(void)
{
test_add_event();

/*
auto test {Event(saturday, 12, 30, saturday, 14, 45,
				 "Big Event", "Your father's house")};

Event test2;
test2 = test;
auto test3 = Event(test2);

cout << test << '\n';
cout << test2 << '\n';
cout << test3 << '\n';

cout << "rename that last one:\n>";
cin >> test3;

auto test4 {Event(saturday, 13, 2, saturday, 13, 5,
				 "Something else", "Your mother's house")};


if (test3 == test4)
	cout << test3 << "\nequal to\n" << test4 << '\n';
else
	cout << test3 << "\nNOT equal to\n" << test4 << '\n';
//compare(test, test4);
*/
}
