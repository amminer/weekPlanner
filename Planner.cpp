#include "Planner.h"

/* Amelia Miner
 * 05/08/2022
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		Planner.h
 * PURPOSE: 	In the main loop, basic logic for obtaining information
				from the user and managing a sort of viewport into the
 8				planner is implemented. Each time the main loop restarts,
 *				the current_week of the viewport is displayed. Some
 *				Uses std::list to maintain a collection 
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

size_t Planner::size(void) const
{
	return weeks.size();
}

void Planner::print_week(size_t week_num)
{
	cout << *this->week(week_num);
}

void Planner::add_weeks(size_t num_weeks)
{
	if (num_weeks <= 0){
		return;
	}
	else{
		weeks.push_back(EventList(weeks.size() + 1));
		add_weeks(num_weeks - 1);
		return;
	}
}

//arg for future extensibility, could add multiple events
//or could allow addition of an event to a different week
//than the current week in the main loop if needed
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
		advance(it, week_num - 1); //0 indexed
		return &*it; //iterator points to elmt
	}
}

/*	UI FUNCTION(S)	*/

//changes all invalid inputs to 0 for error check since
//zero is never a valid option in the main loop.
int get_size_t(size_t min=0, size_t max=pow(2, 16)) //size_t min 16bit precision
{
	int ret;
	cin >> ret;
	cin.clear();
	cin.ignore(1000, '\n');
	if ((size_t)ret <= 0 or (size_t)ret < min or (size_t)ret > max){
		cout << "Invalid input!\n";
		ret = 0;
	}
	return (size_t) ret;
}

/*	MAIN LOOP	*/

int main(void)
{
	Planner planner;
	bool cont{true};
	size_t choice = 0; //main menu & subsequent choices
	size_t current_week = 1; //tracks which week we're looking at/working on
	//eventually, I would set this up to display an ascii book with a page on the
	//left side that is always populated by a week number and a grid of boxes,
	//one for each day of the week much like the notebook that I use as a planner.
	//The right side page is populated if there is an even numbered page following
	//the left side page, and the user can flip between 2-page spreads in the same
	//way that they switch between viewing different weeks above the main menu.
	//the "page" only "turns" 
	cout << "Welcome to Planner And Integrated Notebook!\n";
	while (cont){
		choice = 0;
		planner.print_week(current_week);
		cout << "\n(Out of " << planner.size() << " weeks in the planner)\n";
		cout << "/~ Main Menu ~/\n"
			 << " 1 - Add weeks to the planner\n"
			 << " 2 - Add an event to the current week\n"
			 << " 3 - Remove an event from the current week\n"
			 << " 4 - Go to the next week\n"
			 << " 5 - Go to the previous week\n"
			 << " 6 - Go to another week by number\n"
			 << " 7 - Exit Planner And Integrated Notebook\n\nChoose an option: ";
		choice = get_size_t(1, 7);
		cout << '\n';
		//current_week is passed to helpers for ease of extension
		switch (choice){
			case 1:
				cout << "How many more weeks ahead do you need to plan?: ";
				//no max besides 2^16 for now... slightly dangerous?
				choice = get_size_t();
				if (choice > 0)
					planner.add_weeks(choice);
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
				choice = get_size_t(0, planner.size());
				if (choice > 0)
					current_week = choice;
				break;
			case 7:
				cont = false;
				break;
			default: //in case invalid input somehow gets past get_size_t
				break;
		}
	}
	cout << "Exiting...\n\n";
}
