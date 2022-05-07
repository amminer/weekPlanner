#include "../Event.h"
#include <list>

void compare(const Event& a, const Event& b)
{
	if (a < b)
		cout << a << "\nless than\n" << b << '\n';
	else if (a > b)
		cout << a << "\ngreater than\n" << b << '\n';
	else if (a == b)
		cout << a << "\nequal to\n" << b << '\n';
	else
		cout << a << "\nERROR\n" << b << '\n';
	cout << '\n';
}
void compare_gele(const Event& a, const Event& b)
{
	if (a <= b){
		cout << a << "\nLE\n" << b << '\n';
	}
	if (a >= b){
		cout << a << "\nGE\n" << b << '\n';
	}
	cout << '\n';
}

/* should note the format of desired input in docstring */
// may be doing this wrong: see
// https://stackoverflow.com/questions/35102079/c-upcasting-and-downcasting
void test_add_event()
{
	string type;
	cout << "(Options are flight, dinner, or yoga)\n"
		 << "Choose an event type {!q to quit}: ";
	getline(cin, type);
	if (type == "!q")
		return;
	else if (type == "flight"){ //TODO exception handling/input validator function
		Flight f = Flight();
		if (f.setup_from_cin())
			cout << "Your new event:\n" << f << '\n';
	}
	else if (type == "dinner"){
		Dinner d = Dinner();
		if (d.setup_from_cin())
			cout << "Your new event:\n" << d << '\n';
	}
	else if (type == "yoga"){
		Yoga y = Yoga();
		if (y.setup_from_cin())
			cout << "Your new event:\n" << y << '\n';
	}
	else{
		cout <<"invalid input! Try again.\n";
		test_add_event();
	}
}

void test_comparative_ops(void) //still missing some edge cases...
{
	auto test {Event(saturday, 12, 30, saturday, 14, 45,
					 "Big Event", "base")};
	//all possible relationships with test:
	//== contains
	auto test2 {Event(saturday, 13, 2, saturday, 14, 5,
					 "Something else", "base contains")};
	//== is contained by
	auto test3 {Event(saturday, 8, 30, saturday, 21, 45,
					 "Party", "base is contained by")};
	//==/>= start overlaps stop
	auto test4 {Event(saturday, 8, 30, saturday, 13, 10,
					 "Block Party", "base is ==/>=")};
	//==/<= stop overlaps start
	auto test5 {Event(saturday, 13, 30, saturday, 18, 10,
					 "Citywide Rager", "base is ==/<=")};
	//<
	auto test6 {Event(saturday, 10, 30, saturday, 11, 10,
					 "Universally Lit National Holiday", "base is >")};
	//>
	auto test7 {Event(saturday, 15, 30, saturday, 18, 10,
					 "Apocalyptic Shindig", "base is <")};

	list<Event> events {test2, test3, test4, test5, test6, test7};
	for (Event other: events){
		compare(test, other);
		compare_gele(test, other);
	}
}

int main(void)
{
//basics
//multi day event
Event q = Event(monday, 12, 30, wednesday, 8, 20, "test", "test2");
//moment event
Event w = Event(tuesday, 10, 5, tuesday, 10, 5, "test3", "test4");

test_add_event();
//test_comparative_ops();

}
