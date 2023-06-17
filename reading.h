#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// if line == 0    VERTICES 
template<class T>
vector<T> line1(string str, int& countvertex)
{
	vector<T>vertices;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '{')
		{
			i++;
			
			while ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57)) 
			{
				vertices.push_back(str[i]);
				countvertex++; i++;
			}
			
		}
		 if (str[i] == ',')
		{
			i++; countvertex++;
			vertices.push_back(str[i]);
		}
	}
	return vertices;
}

// if line == 2    EDGES  ----------------  CREATING 2D LINKED LIST  --------------------
//                        ---------------------------------------------------------------
void line2(string str, vector<char>& vertex, int ** &arr, vector<int>& weights)
{//                                    h,a,b,c,d                1,2,3,4,5,6
	vector <char> temp; char v1, v2; int count = 0; int weight_count = -1; int flag = 0;
	for (int i = 0; i < str.length(); i++)
	{
		// checking for (h,A)
		if (str[i] == '(')
		{
			if (flag == 0) 
			{
				weight_count++;
			}
			

			i++;    count++; 
			if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))
			{
				v1 = str[i];
				auto it = find(vertex.begin(), vertex.end(), str[i]);
				int index_of_v1 = it - vertex.begin();


				i += 2; count++; v2 = str[i];
				auto it2 = find(vertex.begin(), vertex.end(), str[i]);
				int index_of_v2 = it2 - vertex.begin();
				if (v1 != v2) 
				{
					arr[index_of_v1][index_of_v2] = weights[weight_count];
					arr[index_of_v2][index_of_v1] = weights[weight_count];
					cout << "The edge is " << "(" << v1 << "," << v2 << ")" << weights[weight_count] << endl; 
					flag = 0;
				}
				else 
				{
					flag = 1;
				}
				
			}
			
			//l[index_of_v2].insert(weights[weight_count], v1);
		}
	}

}

vector<int> line3(string str, int& countvertex)
{
	string x = "";
	vector<int>weight;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '{')
		{
			i++;

			while ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))
			{
				x.push_back(str[i]);
				countvertex++; i++;
			}
			weight.push_back(stoi(x));
			x = "";

		}
		if (str[i] == ',')
		{
			i++;
			while ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))
			{
				x.push_back(str[i]);
				countvertex++; i++;
			}
			weight.push_back(stoi(x));
			x = ""; i--;
		}
	}
	return weight; //{10, 11, 21}
}
// line == 4 get time taken 
void line4(string str, vector <int>& x)
{
	string y = ""; int y1 = 0;
	int flag = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '=')
		{
			i++;
			for (i; i < str.length(); i++)
			{
				
				if (str[i] == ',' )
				{
					flag = 1;
					break;
				}
				if ((str[i] >= 48 && str[i] <= 57))
				{
					if (i == str.length() - 1) 
					{
						flag = 1;
					}
					y.push_back(str[i]);
				}
				
			}
		}
		if (flag == 1)
		{
			y1 = stoi(y);
			x.push_back(y1);
			y = ""; flag = 0;
		}
	}

}

// line == 5 getting time limit 
void line_5(string str, int& x)
{
	string s;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '=')
		{
			i++;
			for (i; i < str.length(); i++)
			{
				if (str[i] >= 48 && str[i] <= 57) 
				{
					s.push_back(str[i]);
				}	
			}

		}
	}
	x = stoi(s);
}


int **read(string &p, vector<int>& weights, int &count/*, int** arr*/, vector<char>& vertex, int& time_limit, vector<int>& time_taken, int& edges)
{
	int** arr= NULL;
	string str= "";
	int line = 0; string l2 = ""; string l3 = "";
	fstream file;
	file.open(p);
	//file.is_open();
	



	while (getline(file, str)&& line < 5)
	{
		while (str == "") 
		{
			getline(file, str);
		}
		// Output the text from the file
		line++;
		//int count = 0;// will get number of vertces
		if (line == 1)
		{
			vertex = line1<char>(str, count);
			arr = new int* [count];
			for (int i = 0; i < count; i++) 
			{
				arr[i] = new int[count];
			}
			// initializing with zero
			for (int i = 0; i < count; i++) 
			{
				for (int j = 0; j < count; j++) 
				{
					arr[i][j] = 0;
				}
			}

		}
		else if (line == 2)
		{
			// edges 
			l2 = str;
		}
		else if (line == 3)
		{
			// weights 
			l3 = str;
		}
		else if (line == 4)
		{
			line4(str, time_taken);
		}
		else if (line == 5)
		{
			line_5(str, time_limit);
		}

		cout << str << endl;
	
	}
	// calculating int vector for number of weights
	weights = line3(l3, edges);

	 for (int i = 0; i < weights.size(); i++)
	 {
		 cout << "Weights " << i << " : " << weights[i] << endl;
	 }
	 cout << endl;

	//string str, vector<char>& vertex, List*& l, vector<int>& weights
	// 
	// 
	// creating linked list 
	line2(l2, vertex, arr, weights);
	for (int i = 0; i < count; i++) 
	{
		for (int j = 0; j < count; j++) 
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	return arr;
}



// ----   TEST CASE   ----
//1. V = { h,A,B,C }
//2. E = { (h,A),(h,B),(h,C),(A,B),(A,C),(B,C) }             -- l2
//3. Weights = { 1,2,3,4,5,6 } stored in adjacency matrix    -- l3 
//4. t(A) = 5, t(B) = 10, t(C) = 8
//5. T = 20