#include <bits/stdc++.h>

using namespace std;

void	gravity_flip(vector<int> arr, int c)
{
	for (int i = 0; i < c; i++)
	{
		for (int j = i + 1; j < c; j++)
		{
			if (arr[i] > arr[j])
			{
				arr[i] ^= arr[j];
				arr[j] ^= arr[i];
				arr[i] ^= arr[j];
			}
		}
	}
	for (int i = 0; i < c; i++)
	{
		cout << arr[i];
		if (i + 1 != c)
			cout << " ";
	}
}

int main()
{
	int c;
	vector<int> arr;
	cin >> c;
	arr.resize(c);
	for (int i = 0; i < c; i++)
		cin >> arr[i];
	gravity_flip(arr, c);
}
