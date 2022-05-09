/* Amelia Miner
 * 05/08/2022
 * cs 202 section 003
 * PROGRAM #:		2
 * FILE:			Planner.h
 * PURPOSE: 		Uses std::list to maintain a collection 
 *					of EventLists representing consecutive weeks.
 */ //TODO add more about implementation

void Planner::help(void)
{
	cout << "The planner has a page for each week. To keep it simple, at startup\n"
		 << "no pages have been set up - you have a blank canvas and only\n"
		 << "need to keep track of weeks as far into the future as you know/\n"
		 << "only need to consider reservations one week at a time.
		 << "you need to. Do not try to use this application like a calendar!\n"
		 << "That being noted, 3 kinds of reservations can be added to the planner,\n"
		 << "a flight, a dinner, or a yoga class. Reservations must not overlap\n"
		 << "each other's times, except that a flight may overlap with exactly one\n"
		 << "dinner and vice versa. Reservations may not begin in one week and end\n"
		 << "in another - weeks start Sunday at midnight, 0:00, and end Saturday at 23:59.\n"
		 << "This is loosely based on the way that I use my planner in real life,\n"
		 << "As my planner is just a blank notebook that I organize into one week per page.\n"
		 << "I just thought it would be more fun than doing a calendar.\n";
}

int main(void)
{
	Planner planner;
	bool cont{true};
	int choice = 0; //main menu choice
	cout << "Welcome to a questionably designed planner application!\n\n";
	while (cont){
		choice = 0;
		cout << "/~ Main Menu ~/\n"
			 << " 1 - \n"
			 << " 2 - Inspect the current roster for the next race\n"
			 << " 3 - Add a new animal to stables\n"
			 << " 4 - Remove an animal from stables\n"
			 << " 5 - Choose an animal from the stables for the next race\n"
			 << " 6 - Remove an animal from the roster for the next race\n"
			 << " 7 - Set up a race with the current roster\n"
			 << " 8 - Exit Animal Racing Simulator Extreme\n\n";
		display_cursor();
		choice = get_int();
		switch (choice){
	}
}
