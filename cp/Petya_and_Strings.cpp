#include <iostream>
using namespace std;

char lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int main()
{
	string a, b;

	cin >> a >> b;
	for (int i =0; i < a.size(); i++)
	{
		if (tolower(a[i]) < tolower(b[i]))
			return (cout << -1 << endl, 0);
		else if (tolower(a[i]) > tolower(b[i]))
			return (cout << 1 << endl, 0);
	}
	cout << 0 << endl;
	return (0);
}
