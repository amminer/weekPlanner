#include "../EventList.h"

int main(void)
{

EventList myweek(1);
int e;
cout <<"How many events would you like to add?: ";
cin >> e;
cin.clear(); cin.ignore(100, '\n');

for (int i = e; i > 0; --i){
	myweek.add_event();
}

cout << myweek << '\n';

}
