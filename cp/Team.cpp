#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int	c;
	int a = 0;
	vector<int> arr;
	cin >> c;
	arr.resize(c);
	for (int i = 0; i < c ; i++)
	{
		int l , p , k;
		cin >> l >> p >> k;
		a += ((l + p + k) >= 2);
	}
	cout << a << endl;
	return 0;
}
