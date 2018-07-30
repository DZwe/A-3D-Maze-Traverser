// Author: Zwe Phone Shein
// Project: 3
// U70232522

#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

// Class for Node objects which would also act as vertices
class Node
{
  public:
    int n,e,s,w,u,d,z,x,y;
    Node* north;
    Node* east;
    Node* south;
    Node* west;
    Node* up;
    Node* down;
    bool visited;
    bool discovered;

};

// Main functions
int main()
{

  ifstream infile; // input file stream
  ofstream outfile; // output file stream
  infile.open("input.txt"); // open file to read
  outfile.open("output.txt"); // open file to write

  // initialize variables
  int array[100000];
  char c = '?';
  int a = 0;
  int chars_read = 0;
  int num_problems = 0;
  bool flag = false;
  int level;
  int row;
  int col;
  int start[4];
  int end[4];
  int bin_buff[7];
  int z = 0;
  int count = 0;

  // Initialize an array of Nodes and pointers for starting node and ending node
  Node nodes[10000];
  Node* start_node;
  Node* end_node;

  infile.get(c); // ignore certain unnecessary characters
  num_problems = c - '0'; // read the number of problems and convert it to int
  infile.get(c); // ignore certain unnecessary characters
  infile.get(c); // ignore certain unnecessary characters

  for (int i = 1; i <= num_problems; i++)
  {
    // reset variables
    level = 0;
    row = 0;
    col = 0;
    z = 0;
    count = 0;
    chars_read = 0;

    memset(nodes, 0, 10000); // reset contents of node array to 0
    memset(array, 0, 100000); // reset contents of integer array to 0

    // Loop to read level, row, column and coordinates of starting and ending position
    for (int j = 1; j <= 3; j++)
    {
      for (int h = 1; h <= 3; h++)
      {
        infile >> a;
        array[chars_read] = a;
        chars_read++;
      }
    }

    // Put appropriate values from buffer into variables
    level = array[0];
    row = array[1];
    col = array[2];
    start[1] = array[3];
    start[2] = array[4];
    start[3] = array[5];
    end[1] = array[6];
    end[2] = array[7];
    end[3] = array[8];

    infile.get(c); // ignore certain unnecessary characters

    // Loop to read the binary numbers which would be used to join the vertices.
    for (int m = 0; m < level; m++)
    {
      for (int k = 0; k < row; k++)
      {
        for (int l = 0; l < col; l++)
        {
          chars_read = 0;
          memset(bin_buff, 0, 7); // reset bin_buff array
          while( infile && chars_read < 7 )
          {
            infile.get(c);

            if (c == '\n' || c == ' ') // if you meet a newline or whitespace, break loop
              break;

            bin_buff[chars_read] = c - '0'; // put binary digit in buffer
            chars_read++;

          }

          // Put appropriate values from binary buffer to values of the nodes
          nodes[count].n = bin_buff[0];
          nodes[count].e = bin_buff[1];
          nodes[count].s = bin_buff[2];
          nodes[count].w = bin_buff[3];
          nodes[count].u = bin_buff[4];
          nodes[count].d = bin_buff[5];
          nodes[count].z = z;
          nodes[count].x = k;
          nodes[count].y = l;

          // Initializing nodes' node pointers to null
          nodes[count].north = NULL;
          nodes[count].east = NULL;
          nodes[count].south = NULL;
          nodes[count].west = NULL;
          nodes[count].up = NULL;
          nodes[count].down = NULL;

          count++;

        }
        infile.get(c);
      }
      z++; // Go to next level
    }

    Node* temp; // Temporary pointer
    count = 0;
    int iter;

    // Connect the nodes with each other according to the rules.
    while (nodes[count].z <= level && nodes[count].x <= row && nodes[count].y <= col)
    {

      if (nodes[count].n == 1 && nodes[count].x != 0)
      {

        iter = 0;

        while (1)
        {
          temp = &(nodes[iter]);
          if (temp->z == nodes[count].z && temp->x == nodes[count].x - 1 && temp->y == nodes[count].y)
          {
            nodes[count].north = temp;
            break;
          }
          iter++;
        }
      }

      if (nodes[count].e == 1 && nodes[count].y != col-1)
      {
        iter = 0;

        while (1)
        {
          temp = &(nodes[iter]);
          if (temp->z == nodes[count].z && temp->x == nodes[count].x && temp->y == nodes[count].y + 1)
          {
            nodes[count].east = temp;
            break;
          }
          iter++;
        }
      }

      if (nodes[count].s == 1 && nodes[count].x != row-1)
      {
        iter = 0;

        while (1)
        {
          temp = &(nodes[iter]);
          if (temp->z == nodes[count].z && temp->x == nodes[count].x + 1 && temp->y == nodes[count].y)
          {
            nodes[count].south = temp;
            break;
          }
          iter++;
        }
      }

      if (nodes[count].w == 1 && nodes[count].y != 0)
      {
        iter = 0;

        while (1)
        {
          temp = &(nodes[iter]);
          if (temp->z == nodes[count].z && temp->x == nodes[count].x && temp->y == nodes[count].y - 1)
          {
            nodes[count].west = temp;
            break;
          }
          iter++;
        }
      }

      if (nodes[count].u == 1 && nodes[count].z != level-1)
      {
        iter = 0;

        while (1)
        {
          temp = &(nodes[iter]);
          if (temp->z == nodes[count].z + 1 && temp->x == nodes[count].x && temp->y == nodes[count].y)
          {
            nodes[count].up = temp;
            break;
          }
          iter++;
        }
      }

      if (nodes[count].d == 1 && nodes[count].z != 0)
      {
        iter = 0;

        while (1)
        {
          temp = &(nodes[iter]);
          if (temp->z == nodes[count].z - 1 && temp->x == nodes[count].x && temp->y == nodes[count].y)
          {
            nodes[count].down = temp;
            break;
          }
          iter++;
        }
      }

      count++;
    }



    // Initialize start and end node
    count = 0;
    while (1)
    {
      if (nodes[count].z == start[1] && nodes[count].x == start[2] && nodes[count].y == start[3])
        start_node = &(nodes[count]);
      if (nodes[count].z == end[1] && nodes[count].x == end[2] && nodes[count].y == end[3])
      {
        end_node = &(nodes[count]);
        break;
      }
      count++;
    }

    char buffer[1000]; // Buffer to store the path to exit
    int r = 0;

    // Start from the starting coordinate and traverse through the maze to find the exit.
    while (1)
    {
      // If you find the exit, stop the loop and insert an end signal for buffer.
      if (start_node->z == end_node->z && start_node->x == end_node->x && start_node->y == end_node->y)
      {
        buffer[r] = '#';
        break;
      }

      // While travelling put the path you took in buffer.

      // Go up if you can and if it's not discovered and not visited.
      if (start_node->u == 1 && (((start_node->up)->discovered != 1) && ((start_node->up)->visited != 1)))
      {
        start_node->visited = 1;
        start_node = start_node->up;
        buffer[r] = 'U';
        r++;
        continue;
      }

      // Go north if you can and if it's not discovered and not visited.
      if (start_node->n == 1 && (((start_node->north)->discovered != 1) && ((start_node->north)->visited != 1)))
      {
        start_node->visited = 1;
        start_node = start_node->north;
        buffer[r] = 'N';
        r++;
        continue;
      }

      // Go east if you can and if it's not discovered and not visited.
      if (start_node->e == 1 && (((start_node->east)->discovered != 1) && ((start_node->east)->visited != 1)))
      {

        start_node->visited = 1;
        start_node = start_node->east;
        buffer[r] = 'E';
        r++;
        continue;
      }

      // Go south if you can and if it's not discovered and not visited.
      if (start_node->s == 1 && (((start_node->south)->discovered != 1) && ((start_node->south)->visited != 1)))
      {
        start_node->visited = 1;
        start_node = start_node->south;
        buffer[r] = 'S';
        r++;
        continue;
      }

      // Go west if you can and if it's not discovered and not visited.
      if (start_node->w == 1 && (((start_node->west)->discovered != 1) && ((start_node->west)->visited != 1)))
      {
        start_node->visited = 1;
        start_node = start_node->west;
        buffer[r] = 'W';
        r++;
        continue;
      }

      // Go down if you can and if it's not discovered and not visited.
      if (start_node->d == 1 && (((start_node->down)->discovered != 1) && ((start_node->down)->visited != 1)))
      {
        start_node->visited = 1;
        start_node = start_node->down;
        buffer[r] = 'D';
        r++;
        continue;
      }

      start_node->discovered = 1; // If every direction is either unavailable or vistited, mark current node as discovered.

      // Look for available directions again, this time go even when it's being visited but not discovered. //

      if (start_node->u == 1 && ((start_node->up)->discovered != 1))
      {
        start_node = start_node->up;
        buffer[r] = 'U';
        r++;
        continue;
      }

      if (start_node->n == 1 && ((start_node->north)->discovered != 1))
      {
        start_node = start_node->north;
        buffer[r] = 'N';
        r++;
        continue;
      }

      if (start_node->e == 1 && ((start_node->east)->discovered != 1))
      {
        start_node = start_node->east;
        buffer[r] = 'E';
        r++;
        continue;
      }

      if (start_node->s == 1 && ((start_node->south)->discovered != 1))
      {
        start_node = start_node->south;
        buffer[r] = 'S';
        r++;
        continue;
      }

      if (start_node->w == 1 && ((start_node->west)->discovered != 1))
      {
        start_node = start_node->west;
        buffer[r] = 'W';
        r++;
        continue;
      }

      if (start_node->d == 1 && ((start_node->down)->discovered != 1))
      {
        start_node = start_node->down;
        buffer[r] = 'D';
        r++;
        continue;
      }

    }

    // Print the path from the buffer into a text file, output.txt
    for (int i = 0; buffer[i] != '#' ; i++)
    {
      outfile << buffer[i] << " ";
    }
    outfile << endl;

    }

  outfile.close(); // Close the outfile
  infile.close(); // Close the infile
  
  return 0;
}
