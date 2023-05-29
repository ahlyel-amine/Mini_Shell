#include <iostream>

using namespace std;

int main()
{
	string str;

	cin >> str;
	int	len = 0, s = str.size();
	for (int i = 0; i < s; i++)
	{
		for (int j = i + 1; j < s; j++)
		{
			if (str[i] == str[j])
				str[j] = '~';
			if (str[i] != '~')
				len++;
		}
	}
	cout << ((len % 2) ? "IGNORE HIM!" : "CHAT WITH HER!") << endl;
	return 0;
}