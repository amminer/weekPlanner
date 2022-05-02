#include "WeekdayTime.h"
#include <vector>

void compare(WeekdayTime a, WeekdayTime b)
{
	if (a > b)
		cout << a << " greater than " << b << '\n';
	else if (a < b)
		cout << a << " less than " << b << '\n';
	else
		cout << a << " equal to " << b << '\n';
}

int main(void)
{

auto test1 {WeekdayTime(sunday, 10, 30)};
auto test2 {WeekdayTime(tuesday, 14, 45)};
auto test3 {WeekdayTime(tuesday, 13, 0)};

vector times {test1, test2, test3};

for (auto e: times){
	for (auto e2: times){
		compare(e, e2);
	}
}

}
