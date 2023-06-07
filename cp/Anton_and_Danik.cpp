#include <iostream>

using namespace std;

int main()
{
	int	c, a = 0, d = 0;
	string str;
	cin >> c >> str;
	
	for (int i = 0; i < c ; i++)
	{
		if (str[i] == 'A')
			a++;
		else
			d++;
	}
	if (a > d)
		cout << "Anton" << endl;
	else if (d > a)
		cout << "Danik" << endl;
	else
		cout << "Friendship" << endl;
	return 0;
}