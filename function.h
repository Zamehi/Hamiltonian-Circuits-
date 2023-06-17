
#include <iostream>
#include <vector>

using namespace std;


// display vector
template <class T>
void display(vector<T>myVector)
{
    for (int i = 0; i < myVector.size(); i++) 
    {
        cout << "Element " << i << " : " << myVector[i] << endl;
    }
    cout << endl;

}



