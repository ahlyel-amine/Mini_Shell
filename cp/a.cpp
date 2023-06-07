#include <iostream>
using namespace std;
#include <vector>

#define vi vector<int>



void	print_vector(vi a)
{
	for (int i = 0; i < a.size(); i++){
		cout << a[i] << endl;
	}
}
void	alo(vi *a)
{
	static int call;
	call ++;
	if (call == 6)
		return ;
	(*a).push_back(call);
	alo(a);
}
int main()
{
	vi a;

	alo(&a);
	print_vector(a);

}
