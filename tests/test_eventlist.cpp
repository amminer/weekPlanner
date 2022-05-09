#include "../EventList.h"

EventList myweek(1); //manipulate this from subroutines

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

void remove(void)
{
	try{
		myweek.remove_event();
	}
	catch (string& exc){
		cout << exc << " could not be deleted - is it in the list?\n";
	}
}

int main(void)
{
manual();
remove();

cout << myweek << '\n'; //spits out weeknum and calls display_chronological()
}
