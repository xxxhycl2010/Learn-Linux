#include <iostream>

int main()
{
	using namespace std;
	int updates = 6;
	int *p_updates;

	p_updates = &updates;
	cout << "values:updates = "<< updates;
	cout <<", *p_updates=" << *p_updates << endl;
	cout << "addressess:&updates = " << &updates;
	cout << ", p_updates= " << p_updates << endl;
	
	*p_updates = *p_updates + 1;
	cout << "Now Updates = " << updates << endl;
	return 0;
}
