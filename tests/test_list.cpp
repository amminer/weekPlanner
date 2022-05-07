#include "../LinkedList.h"

int main(void)
{
	LLL<int> mylist;
	mylist.insert_sorted(25);
	mylist.insert_sorted(30);
	mylist.insert_sorted(10);
	mylist.insert_sorted(15);
	mylist.display();
	//not exactly robust, should probably test more/with events
}
