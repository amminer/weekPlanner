#include "../EventList.h"

EventList myweek(1);

void manual(void)
{
	int e;
	cout <<"How many events would you like to add?: ";
	cin >> e;
	cin.clear(); cin.ignore(100, '\n');

	for (int i = e; i > 0; --i){
		myweek.add_event();
	}
}

int main(void)
{

manual();
//can't do this, no param constrs for event subclasses, too lazy to undo manual function
//add them if you must, but my code just works so I don't need to B)
//(kidding, I understand that this is not best practice)
//automatic();

cout << myweek << '\n'; //spits out weeknum and calls display_chronological()

}
