#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, h;
	int	width = 0;
	vector<int> arr;

	cin >> n >> h;
	arr.resize(n);
	for (int i =0; i<n; i++)
		cin >> arr[i];
	for (int i = 0; i < n; i++)
		width += (arr[i] > h) + 1;
	cout << width << endl;
	return 0;
}
