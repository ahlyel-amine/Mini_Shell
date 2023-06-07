#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;

int find(vi arr, int tar)
{
	for (int i=0; i<arr.size(); i++)
		if (tar == arr[i])
			return i;
	return -1;
}

void	solve(pair <int, int> pos)
{
	int a = 0;

	a += pos.first > 2 ? pos.first - 2 :  2 - pos.first; 
	a += pos.second > 2 ? pos.second - 2 :  2 - pos.second;
	cout << a << endl;
}

int main()
{
	pair <int, int> pos;
	vi arr;
	arr.resize(5, 0);
	for (int i=0; i<5;i++)
	{
		for (int j=0; j<5; j++)
			cin >> arr[j];
		int idx = find(arr, 1);
		if (idx != -1)
		{
			pos.first = i;
			pos.second = idx;
		}
	}
	solve(pos);
	return 0;
}
