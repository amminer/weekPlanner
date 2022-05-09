#include "EventList.h"

/* Amelia Miner
 * 05/06/22
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		EventList.cpp
 * PURPOSE:		Class EventList uses a doubly linked list (class LLL) to store a
 *				collection of Event objects.
 *				It uses Event::overlaps(Event&) and the event's type to prevent scheduling
 *				conflicts - flights and dinners may be scheduled simultaneously, but
 *				otherwise no two events may overlap, and no more than one of each
 *				event type may overlap with another whose type matches its own;
 *				Put simply, one dinner may overlap one flight and vice versa, but
 *				otherwise no overlaps are allowed.
 *				Unfortunately if you have, for instance, a flight spanning monday morning
 *				through wednesday evening and you want to schedule a dinner monday evening
 *				and a dinner tuesday evening, this will not be allowed even though it
 *				would intuitively seem possible to do this in real life. Fortunately,
 *				few if any people ever have a flight that lasts that long.
 */

/*	CONSTRUCTORS	*/
EventList::EventList(int week_num_in)
	: week_num(week_num_in) {}

/*	OPERATORS	*/
ostream& operator<<(ostream& out, EventList& op2)
{	
	out << "\nWeek " << op2.week_num << ":\n";
	if (	op2.flights.is_empty()
		and op2.dinners.is_empty()
		and op2.yogas.is_empty()  ){
		cout << "No events this week - add some!\n";
	}
	else
		op2.display_chronological();
	return out;
}
//Displays all events in chron. order, regardless of event type.
//since each LLL is sorted on insertion, we can just check the first elements, then
//the remaining 2 first and the next of the type that was the min before, etc.
//until there's nothing left to output. We do this by passing the indices as args
//and only incrementing them if they are used to print an event. Once an index is greater than
//or equal to the len of the list it is indexing, we stop considering it in our event comparisons.
//all arguments default to 0, so if we just call the function with no args we display everything.
void EventList::display_chronological(size_t flights_index, size_t dinners_index, size_t yogas_index) const
{
	vector<Event*> to_comp; //empty vector will store 0, 1, 2, or 3 events to compare
	if (flights_index < flights.length())
		to_comp.push_back(&flights.at(flights_index)); //still have flights to compare
	if (dinners_index < dinners.length())
		to_comp.push_back(&dinners.at(dinners_index)); //still have dinners to compare
	if (yogas_index < yogas.length())
		to_comp.push_back(&yogas.at(yogas_index)); //still have yogas to compare
	if (to_comp.empty())
		return; //nothing left to compare/print (base case).
	else{
		//find min of to_comp
		vector<Event> actually_comp; //need to compare events, not event*s
		for (Event* elmt: to_comp){			//[0] pushed back, [1] pushed back, etc.
			actually_comp.push_back(*elmt); //order of vectors should match
		}
		auto min_event_iterator = min_element(actually_comp.begin(), actually_comp.end());
		//we now know the distance from begin to min elmt for both vectors;
		//get the element of to_comp (an Event*) at this index and use it to downcast
		Event* min_event = to_comp.at(distance(actually_comp.begin(), min_event_iterator));
		//print it and increment its index
		if (Flight* fp = dynamic_cast<Flight*>(min_event); fp){
			cout << '\n' << *fp << '\n';
			++flights_index;
		}
		else if (Dinner* dp = dynamic_cast<Dinner*>(min_event); dp){
			cout << '\n' << *dp << '\n';
			++dinners_index;
		}
		else if (Yoga* yp = dynamic_cast<Yoga*>(min_event); yp){
			cout << '\n' << *yp << '\n';
			++yogas_index;
		}
		//recurse with its type_index incremented by 1 until all indices >= their list's len
		return display_chronological(flights_index, dinners_index, yogas_index);
	}
}

/*	PUBLIC FUNCTIONS	*/
void EventList::add_event(void)
{
	string type;
	string new_name; //used to check for name conflicts after event creation
	cout << "(Options are flight, dinner, or yoga)\n"
		 << "Choose an event type {!q to cancel}: ";
	getline(cin, type);
	try{
		if (type == "!q")
			return;
		else if (type == "flight"){
			Flight f = Flight();
			if (f.setup_from_cin()){
				new_name = f.get_name();
				if (!creates_time_conflict(&f) and !creates_name_conflict(new_name))
					flights.insert_sorted(f);
				else //TODO exception handling should be used here to communicate about conflicting event
					cout << "Error adding " << new_name
						 << "; there is a conflict with an existing event.\n"; 
			}
		}
		else if (type == "dinner"){
			Dinner d = Dinner();
			if (d.setup_from_cin()){
				new_name = d.get_name();
				if (!creates_time_conflict(&d) and !creates_name_conflict(new_name))
					dinners.insert_sorted(d);
				else //TODO exception handling should be used here to communicate about conflicting event
					cout << "Error adding " << new_name
						 << "; there is a conflict with an existing event.\n"; 
			}
		}
		else if (type == "yoga"){
			Yoga y = Yoga();
			if (y.setup_from_cin()){
				new_name = y.get_name();
				if (!creates_time_conflict(&y) and !creates_name_conflict(new_name))
					yogas.insert_sorted(y);
				else //TODO exception handling should be used here to communicate about conflicting event
					cout << "Error adding " << new_name
						 << "; there is a conflict with an existing event.\n"; 
			}
		}
		else{
			cout <<"Invalid input! Try again.\n";
			add_event();
		}
	} //end try

	catch (runtime_error&){
		cout << "Error adding the event... please try again.\n";
	}
}

void EventList::remove_event(void)
{
	string name;
	cout << "Enter the name of the event you would like to remove {!q to cancel}: ";
	getline(cin, name);
	if (name != "!q"){
		if (!remove_flight(name) and !remove_dinner(name) and !remove_yoga(name)){
			throw name; //is it worth throwing a string? Calling code already knows name
		}
	}
	return;
}
bool EventList::remove_flight(string& name)
{
	Flight key_f {Flight(name)}; //list takes a ref as arg to lookup
	bool ret = flights.remove(key_f);
	return ret; //stored in local scope for readability
}
bool EventList::remove_dinner(string& name)
{
	Dinner key_d {Dinner(name)}; //list takes a ref as arg to lookup
	bool ret = dinners.remove(key_d);
	return ret; //stored in local scope for readability
}
bool EventList::remove_yoga(string& name)
{
	Yoga key_y {Yoga(name)}; //list takes a ref as arg to lookup
	bool ret = yogas.remove(key_y);
	return ret; //stored in local scope for readability
}

/*	PRIVATE FUNCTIONS	*/
bool EventList::creates_name_conflict(const string& new_name) const
{
	//LLL::lookup uses T==T, and Event==Event checks for name match
	if (creates_name_conflict(new_name, flights)
	 or creates_name_conflict(new_name, dinners)
	 or creates_name_conflict(new_name, yogas))
		return true;
	else
		return false;
}
bool EventList::creates_name_conflict(const string& new_name, const LLL<Flight>& check_list) const
{
	Flight key = Flight(new_name);
	return (bool) check_list.lookup(key);
}
bool EventList::creates_name_conflict(const string& new_name, const LLL<Dinner>& check_list) const
{
	Dinner key = Dinner(new_name);
	return (bool) check_list.lookup(key);
}
bool EventList::creates_name_conflict(const string& new_name, const LLL<Yoga>& check_list) const
{
	Yoga key = Yoga(new_name);
	return (bool) check_list.lookup(key);
}

//Uses downcasting to determine event type; flight and dinner may overlap with one of each other,
//otherwise no overlaps are allowed. Not used currently, but likely to be useful in the future.
bool EventList::creates_time_conflict(Event* event) const //check for conflicts before adding a new event
{
	if (Flight* fp = dynamic_cast<Flight*>(event); fp)
		return creates_time_conflict(fp);
	else if (Dinner* dp = dynamic_cast<Dinner*>(event); dp)
		return creates_time_conflict(dp);
	else if (Yoga* yp = dynamic_cast<Yoga*>(event); yp)
		return creates_time_conflict(yp);
	else{ //uhoh - no plain old event-type objects allowed, currently
		auto ex {runtime_error("You must specify the type of the event to add to the EventList!")};
		throw ex; //this will be seen by programmers who try to misue the class, not by users, ideally
	}
}
//flight may overlap with one dinner but nothing else
bool EventList::creates_time_conflict(Flight* flight) const
{
	int dinner_collisions = 0; //increment on collision
	const int collisions_allowed = 1; //only 1 flight-dinner collision allowed

	for (size_t i = 0; i < flights.length(); ++i){
		if (flights.at(i).overlaps(*flight))
			return true; //no flight-flight overlaps allowed
	}
	for (size_t j = 0; j < dinners.length(); ++j){
		if (dinners.at(j).overlaps(*flight)){
			++dinner_collisions;
			if (dinner_collisions > collisions_allowed)
				return true; //more than {collisions_allowed} flight-dinner overlaps not allowed
		}
	}
	for (size_t k = 0; k < yogas.length(); ++k){
		if (yogas.at(k).overlaps(*flight))
			return true; //no flight-yoga overlaps allowed
	}
	return false; //no disallowed collisions if we make it here
}
//see creates_time_conflict(Flight*), this has the same behavior but swap flight and dinner
bool EventList::creates_time_conflict(Dinner* dinner) const
{
	int flight_collisions = 0; //increment on collision
	const int collisions_allowed = 1; //only 1 flight-dinner collision allowed
	for (size_t i = 0; i < flights.length(); ++i){
		if (flights.at(i).overlaps(*dinner)){
			++flight_collisions;
			if (flight_collisions > collisions_allowed)
				return true; //more than {collisions_allowed} flight-dinner overlaps not allowed
		}
	}
	for (size_t j = 0; j < dinners.length(); ++j){
		if (dinners.at(j).overlaps(*dinner))
			return true; //no dinner-dinner overlaps allowed
	}
	for (size_t k = 0; k < yogas.length(); ++k){
		if (yogas.at(k).overlaps(*dinner))
			return true; //no dinner-yoga overlaps allowed
	}
	return false; //no disallowed collisions if we make it here
}
//simpler - yoga may not overlap with any event type
bool EventList::creates_time_conflict(Yoga* yoga) const
{
	for (size_t i = 0; i < flights.length(); ++i){
		if (flights.at(i).overlaps(*yoga))
			return true; //no overlaps allowed
	}
	for (size_t j = 0; j < dinners.length(); ++j){
		if (dinners.at(j).overlaps(*yoga))
			return true; //no overlaps allowed
	}
	for (size_t k = 0; k < yogas.length(); ++k){
		if (yogas.at(k).overlaps(*yoga))
			return true; //no overlaps allowed
	}
	return false; //no collisions if we make it here
}
