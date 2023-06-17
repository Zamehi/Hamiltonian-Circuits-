#include <iostream>
#include <vector>
#include "reading.h"
#include "function.h"
#include <fstream>

using namespace std;

// 1. 
// First check the time limit and omit if there is no hamiltonian 

// Function to get minimum value and its index from a vector
int getmin(vector<int>& vector)
{
    int min_value = vector[0];
    int index = 0;

    for (int i = 0; i < vector.size(); i++)
    {
        if (vector[i] < min_value)
        {
            min_value = vector[i];
            index = i;
        }
    }

    // Return the minimum value and its index as a pair
    return index;
}

// -----------------------------------------
void find_hamiltonian_circuit(int**& adj_matrix, vector<int>& path, vector<bool>& visited, int current, vector <vector<int>>& h, int& count)
{

    // A Hamiltonian circuit has been found
    if (path.size() == count)
    {
        if (adj_matrix[current][0])
        {
            // Add the first vertex to complete the circuit
            path.push_back(0);

            h.push_back(path);
            path.pop_back();
        }
        return;
    }

    // All vertices all not covered
    for (int i = 0; i < count; i++)
    {
        if (!visited[i] && adj_matrix[current][i])
        {
            visited[i] = true;
            path.push_back(i);
            find_hamiltonian_circuit(adj_matrix, path, visited, i, h, count);
            path.pop_back();
            visited[i] = false;
        }
    }
}

// -----------------------------------------
// MAIN
int main() 
{

    string str[4] = { "C:\\Users\\Zunaira\\Downloads\\algo_project23\\P2_test1.txt",
          "C:\\Users\\Zunaira\\Downloads\\algo_project23\\P2_test2.txt",
         "C:\\Users\\Zunaira\\Downloads\\algo_project23\\P2_test3.txt",
          "C:\\Users\\Zunaira\\Downloads\\algo_project23\\P2_test4.txt" };
    cout << "Enter the number of graph to check 1 - 2" << endl;
    int st = 0; 
    cin >> st;
    while  (st > 4) 
    {
        cout << "Enter valid nnumber" << endl;
        cin >> st;
    }
    st = st - 1;
   


        // adjacency matrix
        int** adj_matrix;
        // vertices 
        vector<char>vertex;
        // no. of vertices
        int vertex_count = 0;
        // total time limit allowed
        int T = 0;
        // time for each vertex 
        vector<int> t;
        // no. of edges
        int edges = 0;
        // weights of edges 
        vector <int>weights;


        // ------------------------------------------------------------------------
        //                          READING FROM FILE 
        // ------------------------------------------------------------------------


        adj_matrix = read(str[st],weights, vertex_count, vertex, T, t, edges);


        // ------------------------------------------------------------------------
        //                                Timing 
        // ------------------------------------------------------------------------

        int s = 0;
        for (int i = 0; i < t.size(); i++)
        {
            s = s + t[i];
        }
        if (T < s)
        {
            cout << "Expected output: NO FEASIBLE CIRCUIT" << endl;
           
        }
        else
        {

            // ------------------------------------------------------------------------
            //                          HAMILTONIAN CIRCUIT
            // ------------------------------------------------------------------------

            // paths for hamiltonian circuit 
            vector<int> path = { 0 };
            // visited array 
            vector<bool> visited(vertex_count, false);
            visited[0] = true;
            // vectors of hamiltonian circuit 
            vector <vector<int>> h;
            find_hamiltonian_circuit(adj_matrix, path, visited, 0, h, vertex_count);
            if (h.empty()) 
            {
                cout << "Expected output: NO FEASIBLE CIRCUIT" << endl;
            }
            else
            {


                // Print out the elements of vec_of_vec
                cout << "hailtonian circuits are " << endl;
                for (int i = 0; i < h.size(); i++)
                {
                    for (int j = 0; j < h[i].size(); j++)
                    {
                        cout << h[i][j] << " ";
                    }
                    cout << endl;
                }
                vector <int> weight_sum;
                int sum = 0;


                // Adding weights 
                // Finding the hamiltonian circuit with minimum cost 
               // E = { (h,A),(h,B),(h,C),(A,B),(A,C),(B,C) }
               // Weights = { 1,2,3,4,5,6 }
                int k = 0;
                for (int i = 0; i < h.size(); i++)
                {
                    for (int j = 0; j < h[i].size(); j++)
                    {
                        if (j != h[i].size() - 1)
                        {
                            sum = sum + adj_matrix[h[i][j]][h[i][j + 1]];
                        }

                    }
                    weight_sum.push_back(sum);
                    sum = 0;
                }
                // returns index of the minimum sum 

                display(weight_sum);
                int min_ind = getmin(weight_sum);



                cout << "Expected output: (";
                for (int i = 0; i < vertex_count+1; i++)
                {
                    cout << vertex[h[min_ind][i]];
                    if (i != vertex_count - 2)
                    {
                        cout << ",";
                    }
                }
                cout << ")" << endl;
            }
        }

    

    return 0;
}
