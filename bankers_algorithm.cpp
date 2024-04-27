// Darien Yoder
// 4-26-2024
// Operating Systems
// Programming Assignment 2

#include <iostream>
#include <fstream>
#include <vector>

int process_count = 5;
int resource_count = 3;

int main()
{
    // Get data from input file
    std::ifstream input("input.txt");
    if(!input)
    {
        std::cout << "input.txt not found.\n";
        return 0;
    }

    // Put data in a single long vector
    int next_number = 0;
    std::vector<int> input_vector;
    while(input >> next_number)
    {
        input_vector.push_back(next_number);
    }

    // Fill matrices with data from input vector
    int allocation[process_count][resource_count] =
    {
        { input_vector[0],  input_vector[1],  input_vector[2]  },
		{ input_vector[6],  input_vector[7],  input_vector[8]  },
		{ input_vector[12], input_vector[13], input_vector[14] },
		{ input_vector[18], input_vector[19], input_vector[20] },
		{ input_vector[24], input_vector[25], input_vector[26] },
    };
    int max[process_count][resource_count] =
    {
        { input_vector[3],  input_vector[4],  input_vector[5]  },
		{ input_vector[9],  input_vector[10], input_vector[11] },
		{ input_vector[15], input_vector[16], input_vector[17] },
		{ input_vector[21], input_vector[22], input_vector[23] },
		{ input_vector[27], input_vector[28], input_vector[29] },
    };
    int available[resource_count] = { input_vector[30], input_vector[31], input_vector[32] };

    // Mark all processes as unfinished
    // Create a list for storing the safe sequence
    bool finished_processes[process_count];
    int order[process_count];
    int order_index = 0;
    for (int i = 0; i < process_count; ++i)
    {
    	finished_processes[i] = false;
    }

    // Determine the resources needed to finish each process
    int need[process_count][resource_count];
    for (int i = 0; i < process_count; ++i)
    	for (int j = 0; j < resource_count; ++j)
    	    need[i][j] = max[i][j] - allocation[i][j];

    int y = 0;
    for (int k = 0; k < 5; k++)
    {
    	for (int i = 0; i < process_count; ++i)
        {
    	    if (!finished_processes[i])
            {
    		    bool finishable = true;
    		    for (int j = 0; j < resource_count; ++j)
                {
                    // If not enough resources, mark process as unfinishable
            		if (need[i][j] > available[j])
                    {
            			finishable = false;
            			break;
            		}
    		    }

                // If finishable, mark as finished,
                // add to safe sequence, free process's resources,
                // and increment insertion position in sequence
    		    if (finishable)
                {
    	            order[order_index] = i;
                    ++order_index;
        		    for (y = 0; y < resource_count; y++)
        			    available[y] += allocation[i][y];
        		    finished_processes[i] = true;
        		}
    	    }
	    }
    }

    // Determines if sequence is safe
    // (all processes are finished)
    bool all_finished = true;
    for(int i = 0; i < process_count; i++)
    {
        if(finished_processes[i])
    	{
    		all_finished = false;
    		break;
    	}
    }

    // Print whether sequence is safe
    if (all_finished)
    {
    	std::cout << "The sequence is safe.\n";
    	for (int i = 0; i < process_count - 1; i++)
    		std::cout << " P" << order[i] << " ->";
    	std::cout << " P" << order[process_count - 1] << "\n";
    }
    else
    {
        std::cout << "The sequence is NOT safe.\n";
    }

	return 0;
}
