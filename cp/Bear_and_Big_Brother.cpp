#include <iostream>

using namespace std;

int main()
{
	int	a,b,i = 0;
	cin >> a >> b;
	while (1)
	{
		a *= 3;
		b *= 2;
		i++;
		if (a > b)
			break;
	}
	cout << i << endl;
}
