/*  *****************************************************************
Class ID generator
******************************************************************** 
The program takes the Student ID as an input;
scrambles it and uses portions as "seed" for the srand(seed) function
used by the random-number  generator function rand();

The outcomes of the rand() are subsequently converted to 
an alphanumeric string, which generates the final output -- 
a string to be used as your class ID;

NOTE:
The output is also written in a text-file under the name "My317_Fall13_ID.txt,
that will be stored in the same directory (folder) as 
the Project that you build for this program;
***********************************************************************  */


#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) 

{
  
  unsigned int sid_num, sid_p1, sid_p2, sid_p3;
  int firstRandom, secondRandom;
  int  sid_p3_d1, sid_p3_d4, sh1, sh2;
  int seed;
  char uuid[128];
  FILE *filePointer;
  char sid[25];


  /* Retrieve user input */
  cout << "Enter your 7-digit student ID (as it appears on your Wildcard): ";
  cin >> sid;

  if(strlen(sid) != 7) {
    cerr << endl << "The student ID that you have entered is not 7 digits long." 
		 << endl 
		 << endl 
		 << "PROGRAM TERMINATED! Please run it again!" 
		 << endl 
		 << endl;
    system("pause");
	exit(1);
  }
  
  /* Convert user's string to a valid integer */
  sid_num = atoi(sid);
  cout << endl << "SID: " << sid_num << endl;
  
  /* Scramble the user ID and produce the student's class ID */
  sid_p1 = sid_num / 1000000;
  sid_p2 = (sid_num - sid_p1 * 1000000) / 10000;
  sid_p3 = sid_num - sid_p1 * 1000000 - sid_p2 * 10000;
  
  sid_p3_d1 = sid_p3 / 1000;
  sid_p3_d4 = sid_p3 % 10;

  sh1 = sid_p3_d1 * 10 + sid_p3_d4;
  sh2 = (sid_p3 - sid_p3_d1 * 1000 - sid_p3_d4) / 10 + sh1;

  /* Avoid 0s : they are the source of duplicate alias */
  seed = 1;
  if (sid_p1 !=0)
	  seed *= sid_p1;
  if (sid_p3_d1 !=0)
	  seed *= sid_p3_d1;
  if (sid_p3_d4 != 0)
	  seed *= sid_p3_d4;

  srand(seed);
  firstRandom = rand() % 100;

  seed = 1;
  if (sid_p2 !=0)
	  seed *= sid_p2;
  if (sh2 !=0)
	  seed *= sh2;

  srand(seed);
  secondRandom = rand() % 1000;

  	  
  /* Fix of previous versions: 
  normalize the values so that out of all the ASCII characters
  the "special symbols" such as "#" are avoided and only 
  alphabetical characters and digits are being generated*/
	
  cout << "RAND_MAX = " << RAND_MAX << endl;


	cout << "sh1 = " << sh1 << endl;
	cout << "sh2 = " << sh2 << endl;

  if (sh1 > 25 && sh1 < 32 || sh1 > 57)
  {
	  srand(sh1);
	  if (sid_p3_d1 %2)
		  sh1 = rand() % 26;
	  else
		  sh1 = 32+rand() % 26;
  }
  
  if (sh2 > 25 && sh2 < 32 || sh2 > 57)
  {
	  srand(sh2);
	  if (sid_p3_d1 %2)
		  sh2 = rand() % 26;
	  else
		  sh2 = 32+rand() % 26;
  }
	
	cout << "sh1 = " << sh1 << endl;
	cout << "sh2 = " << sh2 << endl;

  
  if(sid_p3_d4 % 2)
	sprintf(uuid, "%d%d%c%c", firstRandom, secondRandom, sh1+65, sh2+65);
  else
	sprintf(uuid, "%c%c%d%d", sh1+65, sh2+65, firstRandom, secondRandom);

  /* Display results */
  cout << endl << "Your unique class id is: " 
	   << uuid 
	   << endl 
	   << endl 
	   << "Please report your name, email address and this self-generated class id to your TAs:"
	   << endl 
	   << endl
	   << "Besim Avci: \n"
	   << "besimavci2016@u.northwestern.edu \n \n \n"
       << endl
	   << "Bing Zhang: \n"
	   << "bingzhang2017@u.northwestern.edu \n \n \n"
	   << endl
	   << endl
	   << "Do NOT use your Northwestern Student ID number \n in the tests and assignments for this class" 
	   << endl 
	   << endl;

  system("pause");


  /* Open the My317_ID.txt file, accessed via
  the filePointer variable, in a write-mode;
  write the explanation strings in there;
  write the value of the string that denotes the
  course ID for EECS 317*/
 
  filePointer = fopen("My317_Fall13_ID.txt", "w+");
  fprintf(filePointer, "Your unique class id is %s Please report your name, email address and this class id to your TAs", uuid);
  fclose(filePointer);

  // cout << "Press any key to terminate";

  return 0;
}