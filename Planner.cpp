#include "Planner.h"

/* Amelia Miner
 * 05/08/2022
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		Planner.h
 * PURPOSE: 	Uses std::list to maintain a collection 
 *				of EventLists representing consecutive weeks.
 *				Also includes main function, which uses a while loop
 *				to display the current week and the main menu.
 *				Think of this as being the page currently being viewed.
 *				The user can add new pages, add new events to the
 *				current page, flip the page forward or backward,
 *				go to any page by its number, or remove events from
 *				the current page.
 *				Removing and copying weeks/pages would be easy to
 *				implement using this design, but I chose to keep it
 *				simple.
 *				The planner must have at least one week, if you wish
 *				to use or extend this class you should keep this in mind,
 *				but it would not be difficult to remove this limitation.
 *				I did not do so since you want at least one week if you
 *				are running the program - would be annoying to have to
 *				add the first week each time you run this.
 */

/*	CONSTRUCTORS	*/

Planner::Planner(void) //called by main loop, sets up first week
	: weeks({EventList(1)}) {}

/*	PUBLIC FUNCTIONS	*/

size_t Planner::size(void)
{
	return weeks.size();
}

void Planner::print_week(size_t week_num)
{
	cout << *this->week(week_num);
}

void Planner::add_week(void)
{
	weeks.push_back(EventList(weeks.size() + 1));
}

void Planner::add_event(size_t week_num)
{
	week(week_num)->add_event();
}

void Planner::remove_event(size_t week_num)
{
	try{
		week(week_num)->remove_event();
	}
	catch (string& bad_name){
		cout << "Error removing " << bad_name << " - is it in the current week?\n";
	}
}

/*	PRIVATER FUNCTIONS	*/

//access the week/EventList at index week_num-1
EventList* Planner::week(size_t week_num)
{
	if (week_num > weeks.size())
		return nullptr;
	else{
		auto it {weeks.begin()};
		advance(it, week_num-1); //0 indexed
		return &*it; //iterator points to elmt
	}
}

/*	MAIN LOOP	*/

int main(void)
{
	Planner planner;
	bool cont{true};
	size_t choice = 0, go_to = 0; //main menu choice & week number choice
	size_t current_week = 1; //tracks which week we're looking at/working on
	cout << "Welcome to Planner And Integrated Notebook!\n";
	while (cont){
		choice = 0;
		planner.print_week(current_week);
		cout << "\n(Out of " << planner.size() << " weeks in the planner)\n";
		cout << "/~ Main Menu ~/\n"
			 << " 1 - Add a week to the planner\n"
			 << " 2 - Add an event to the current week\n"
			 << " 3 - Remove an event from the current week\n"
			 << " 4 - Go to the next week\n"
			 << " 5 - Go to the previous week\n"
			 << " 6 - Go to another week by number\n"
			 << " 7 - Exit Planner And Integrated Notebook\n\nChoose an option: ";
		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << '\n';
		//current_week is passed to helpers for ease of extension
		switch (choice){
			case 1:
				planner.add_week();
				break;
			case 2:
				planner.add_event(current_week);
				break;
			case 3:
				planner.remove_event(current_week);
				break;
			case 4:
				if (current_week == planner.size())
					cout << "No next week - add one!\n";
				else
					++current_week;
				break;
			case 5:
				if (current_week == 1)
					cout << "No previous week - time travel is not allowed!\n";
				else
					--current_week;
				break;
			case 6:
				cout << "What week number?: ";
				cin >> go_to;
				cin.clear();
				cin.ignore(1000, '\n');
				if (go_to >= 1 and go_to <= planner.size())
					current_week = go_to;
				else
					cout << "Invalid input! Is that week in the planner?\n";
				break;
			case 7:
				cont = false;
				break;
			default:
				cout << "Invalid input!\n";
				break;
		}
	}
	cout << "Exiting...\n\n";
}
