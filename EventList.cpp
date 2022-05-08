#include "EventList.h"

/* Amelia Miner
 * 05/06/22
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		EventList.cpp
 * PURPOSE:		Class EventList uses a doubly linked list (class LLL) to store a
 *				collection of Event objects.
 *				It uses Event::operator== and the event's type to prevent scheduling
 *				conflicts - flights and dinners may be scheduled simultaneously, but
				otherwise no two events may overlap, and no more than one of each
				event type may overlap with another whose type matches its own;
				Put simply, one dinner may overlap one flight and vice versa, but
				otherwise no overlaps are allowed. TODO this behavior adds significant complexity - may want to go simpler...
 */

/*	CONSTRUCTORS	*/
EventList::EventList(void)
	: week_num(-1) {}

EventList::EventList(int week_num_in)
	: week_num(week_num_in) {}

/*	OPERATORS	*/
ostream& operator<<(ostream& out, EventList& op2)
{	
	out << "Week " << op2.week_num << ":\n";
	op2.display_chronological();
	return out;
}
//Displays all events in chron. order, regardless of event type.
//since each LLL is sorted on insertion, we can just check the first elements, then
//the remaining 2 first and the next of the type that was the min before, etc.
//until there's nothing left to output. We do this by passing the indices as args
//and only incrementing them if they are used to print an event. Once an index is greater
//than the len of the list it is indexing, we stop considering it in our event comparisons.
void EventList::display_chronological(size_t flights_index, size_t dinners_index, size_t yogas_index)
{
	vector<Event*> to_comp {};
	if (flights_index < flights.length())
		to_comp.push_back(&flights.at(flights_index));
	if (dinners_index < dinners.length())
		to_comp.push_back(&dinners.at(dinners_index));
	if (yogas_index < yogas.length())
		to_comp.push_back(&yogas.at(yogas_index));
	if (to_comp.empty())
		return; //nothing left to print
	else{
		//find min of to_comp
		auto min_event_iterator = min_element(to_comp.begin(), to_comp.end());
		Event* min_event = to_comp.at(distance(to_comp.begin(), min_event_iterator));
		//print it and increment its index
		if (Flight* fp = dynamic_cast<Flight*>(min_event); fp){
			cout << *fp;
			++flights_index;
		}
		else if (Dinner* dp = dynamic_cast<Dinner*>(min_event); dp){
			cout << *dp;
			++dinners_index;
		}
		else if (Yoga* yp = dynamic_cast<Yoga*>(min_event); yp){
			cout << *yp;
			++yogas_index;
		}
		cout << '\n';
		//recurse with its type_index incremented 1
		return display_chronological(flights_index, dinners_index, yogas_index);
	}
}

/*	PUBLIC FUNCTIONS	*/
//TODO in progress, does not currently use private helpers. Helpers will call
//isinconflict to check for conflicting events
//meaning this is not checking for conflict;
void EventList::add_event(void)
{
	string type;
	cout << "(Options are flight, dinner, or yoga)\n"
		 << "Choose an event type {!q to quit}: ";
	getline(cin, type);
	if (type == "!q")
		return;
	else if (type == "flight"){ //TODO exception handling/input validator function?
		Flight f = Flight();
		if (f.setup_from_cin()){
			//TODO check for conflicts before inserting
			flights.insert_sorted(f);
		}
	}
	else if (type == "dinner"){
		Dinner d = Dinner();
		if (d.setup_from_cin()){
			//TODO check for conflicts before inserting
			dinners.insert_sorted(d);
		}
	}
	else if (type == "yoga"){
		Yoga y = Yoga();
		if (y.setup_from_cin()){
			//TODO check for conflicts before inserting
			yogas.insert_sorted(y);
		}
	}
	else{
		cout <<"Invalid input! Try again.\n";
		add_event();
	}
}

/*	PRIVATE FUNCTIONS	*/
bool EventList::is_in_conflict(Event&) //check for conflicts before adding a new event
{
	
}

void EventList::insert_flight(Flight&)
{
}

void EventList::insert_dinner(Dinner&)
{
}

void EventList::insert_yoga(Yoga&)
{
}

