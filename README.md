// You must create some necessary .txt files to run this program...

Extending Simulation Functionality
Last updated: 4/24/2024 @ 11:02 am.

The drive-in theater for Radiator Springs continues to be a huge hit! With all the new traffic from Route 66, we need to improve the program to handle some showing more movies and having more theater screens. This program is a continuation of Program 2.



Photo by Dominique Hicks on Unsplash



Your job is to implement the functions below in the movie_simulation_functions.cpp file. You CANNOT edit movie_simulation_program_3.cpp or the .h file. 

Part 0: Documenting the Code and Following Programming Standards (10 points)

A majority of this code base already been documented for you, including the functions you are going to implement. If you write any additional functions, make sure you properly document them using the provided template below. Additionally, be sure to follow the programming standards document on Canvas. 

Code Block 7.4.1: Function Header Template
/*********************************************************************
function prototype
Purpose:
    Description of the purpose of the function.
Parameters:
    List each of each parameter including data type and description. 
    Each item should begin with whether the parameter is passed in, out or both.
    I Passed in. 
    O Passed out.
    I/O Modified. 
Return Value:
    List of values returned by the function, excluding parameters.
Notes:
    Description of any special information regarding this function. 
    This is a good place to state any assumptions the function makes.
*********************************************************************/
Part 1: Function to Prompt for a Filepath (05 points)

Below is the function prototype of the function to implement.

string promptForFilename();


This function should continue to prompt the user to enter a filename until a valid one is entered or the word "exit" has been entered. A valid filename must end with ".txt" and cannot contain any spaces. This function returns either a valid filename once one has been entered OR the string "EXIT" if the user enters exit for the filename. 

Note: This function DOES NOT check if the file exists, only that the filename is valid. 



Part 2: Function to Populate Theater Information from a File Stream (10 points)

Below is the function prototype of the function to implement.

void processTheaterInformation(fstream& fileInput, Theater& myTheater);


Previously, the program read from a file containing theater information. Unlike the previous theater file, the program 3 theater file will now have indivdual theater screens listing the theater room name, how many parking spots there are and what movie is being shown. Your job is to write a function that takes information from the theater file and processes it into the myTheater structure. The function requirements are listed below:

The function should continue to ask the user for a filename until a valid filename is provided AND the file already exists.
If the user enters "exit" for the filename prompt, it should exit the function early stating ""Exiting function due to early exiting of file prompt".
The function is responsible for BOTH opening and closing the file stream.
The file will always have the following:
Theater name
Number of Theater Rooms
*Theater Rooms*
1 or more theater room information where each Room Name, Parking Spots, Movie Name is on it's own line.
*Pricing*: 
Adult Ticket Price
Senior Ticket Price
Child Ticket Price
Member Ticket Price
Memership Fee
Note: The comments will not be in the text file provided, there are just here to provide clarity. 

Code Block 7.4.2: theater.txt
Route 66 Theater                        // Theater name
3                                       // Number of Theater Rooms
*Theater Rooms*
Alto 30 Hatchback_to_the_Future         // Room1 Name, Room1 Spots, Room1 Movie
Nexon 20 Guardians_of_the_Ford_Galaxy   // Room2 Name, Room2 Spots, Room2 Movie
Vento 25 No_Country_for_Oldsmobiles     // Room3 Name, Room3 Spots, Room3 Movie
*Pricing*
10.99                                   // Adult Ticket Price
8.99                                    // Senior Ticket Price
6.99                                    // Child Ticket Price
5.99                                    // Theater Member Ticket Price
6.00                                    // Membership Fee
Part 3: Function to Display A Provided Menu (05 points)

Below is the function prototype of the function to implement.

void displayMenu(string szMenuName, string szChoicesArr[], int iChoices);


This function should display the menu choices that it is provided as an array to the function. The format of the menu is the exact same as the previous program, where menu choices are displayed starting at 1 counting up. The last menu option should always be displayed as -1 as it is used to exit the menu. 

Note: This function is used to both display the normal menu and the admin menu so don't just hardcode the menu. Do not handle user input in this function.

Example:

Menu

*****************************

1. Display theater information

2. Display now showing

3. Buy tickets

4. Refund tickets

5. Admin Menu

-1. Exit program

*****************************



Part 4: Function to Display Theater Information (2.5 points)

Below is the function prototype of the function.

void displayTheaterInfo(const Theater myTheater);


This function should display the theater information provided by the file. This theater information display format should be in the exact same format as program 2.

Example:

Theater Information

*****************************

Name: Route 66 Theater

Rooms: 3

Total seats: 75

*****************************



Part 5: Function to Display Movies Now Showing (2.5 points)

Below is the function prototype of the function to implement.

void displayNowShowing(const Theater myTheater);


This function program should display the movies the theater is now showing. This now showing display format should be displayed similar to displayMenu where each menu option is a movie. However, unlike displayMenu, the menu choices should begin a 0 and not have a -1 option. 

Example:

Now Showing

*****************************

0. Hatchback to the Future

1. Guardians of the Ford Galaxy

2. No Country for Oldsmobiles

*****************************



Part 6: Function to Buy Tickets (30 points)

Below is the function prototype of the function to implement.

CustomerTicket buyTickets(Theater& myTheater);


This function program should provide the functionality for allowing a customer to buy tickets. To simplfy the problem, a customer cannot back out of a ticket purchase once the process has started.

First, the function should ask the customer to enter their name. Once getting their name, the function should check if they are already a theater member. If they are a member, it should print "Welcome back " followed by the customer name. Otherwise, it should ask them if they would like to become a theater member. If the customer says yes, their name should be added to the theater members, add the membership fee to the purchase and the function should continue the ticket process as if they were members. 

*Make sure to note that they bought membership with the purchase using the bBoughtMembership data member. 

After getting the customer name, it should should check if they have already purchased tickets. If they have already purchased tickets, the function should print "You are only allowed 1 ticket purchase per account" and should return a blank customer with no name.

If they have not purchased any tickets, it should ask them what movie would they like to see. This function should call the displayNowShowing function so customers can see what movies are there are. Once they select a movie, they should be prompted with the movie location followed by the number of spots remaining. The function requirements are list below:

If the customer enters a movie that is sold out, print "Sorry, that movie is sold out. Please buy a ticket for a different movie." and ask the customer what movie they would like to see again OR have the restart the ticket buying process.
If the customer enters a movie that still has spots avaliable:
General Rules:
If a customer tries to purchase 0 tickets or more tickets than are avaliable, the function should print "Please make sure you order at least one ticket and not over the availability." and ask them again how many tickets they want.
You can assume that customers will not enter a negative number of tickets when purchasing tickets.
Rewards Members: 
The program should continue the ticket process as if they were members. They should not be charged the membership fee more than once. 
Non Members:
The program should continue the ticket process as if they were non members by asking how many adult, senior and child tickets they would like to buy.
Successfully buying tickets should display the customer total, update tempCust, and subtract from the number of avaliable spots in the theater room. 



Part 7: Function to Calculate Total Sales (05 points)

Below is the function prototype of the function to implement.

double calculateTotalSales(const Theater& myTheater);


This function program should provide the functionality for calculating the total amount of money the theater has earned. It should return that total sales. 



Part 8: Function to Store Data into a File (10 points)

Below is the function prototype of the function to implement.

void storeData(const Theater myTheater, fstream& fileMemberIO, string szMode);


This function program should provide the functionality for storing information into a text file. This function has 2 modes: "Customers" and "Members". If the user does not provide one of these two modes, it should print the message "Invalid mode" and exit the function. 

The function should continue to ask the user for a filepath until a valid filepath is provided. Once a valid filepath is provided, it should create the text file (overwriting the file if it already exists) and store data on it's own line in the text file depending on the mode provided. 

Customers  
Each line should contain the following information seperated by a single space:
Customer Name (If the customer has a first and last name, Replace the spaces in the movie title with underscores)
Movie title customer is seeing (Replace the spaces in the movie title with underscores)
Number of tickets customer bought
Total purchase cost of the customer's transaction (including tax)
Int stating if customer bought membership with the transaction
Example: Sally No_Country_for_Oldsmobiles 3 25.89 1
Members
Each line should contain the following information seperated by a single space:
Customer Name
Example: Sally
The function is responsible for BOTH opening and closing the file stream.



Part 9: Function to Clear Data from the Theater Structure (10 points)

Below is the function prototype of the function to implement.

void clearData(Theater& myTheater, string szMode);


This function program should provide the functionality for clearing customers and members from the theater structure. This function has 2 modes: "Customers" and "Members". If the user does not provide one of these two modes, it should print the message "Invalid mode" and exit the function. 

The function should clear data from the theater depending on what mode is provided.

Customers
Deleting the customer information should do the following:
Loop over each customer and set the following:
Customer Name to an empty string
Movie title to an empty string
Number of tickets to 0
Total purchase cost to 0
Customer bought membership flag to false
Reset the theater customer count to 0.
Members
Deleting the member information should do the following:
Loop over each member and set the following:
Member Name to an empty string
Reset the theater member count to 0.
Part 10: Function to Load Data from a File (10 points)

Below is the function prototype of the function to implement.

void loadData(Theater& myTheater, fstream& fileMemberIO, string szMode);


This function program should provide the functionality for loading customer and member information from a text file. This function has 2 modes: "Customers" and "Members". If the user does not provide one of these two modes, it should print the message "Invalid mode" and exit the function.

The function should continue to ask the user for a filepath until a valid filepath is provided. Once a valid filepath is provided, it should open the text file (can assume that only an appropriate file will be provided) and load the data depending on the mode provided. Below is the process that should be used to load in information.

Open the file for reading
Loop over file and read information into and store it in the correct array
Customers should go to myTheater.customersArr
Members should go to myTheater.membersArr
Close the file


Extra Credit: Function to Refund Tickets (10 + 100/n points)

Below is the function prototype of the function to implement.

void refundTickets(Theater& myTheater);


This function program should provide the functionality for allowing a customer to refund tickets. First, the function should ask the customer to enter their name. 

After getting the customer name, it should check if they are a customer who has bought tickets. The function requirements are list below:

If the customer name entered has not purchased tickets, the function should just display "No customer found" and exit the function.
If the customer name entered has purchased tickets:
It should print the following Customer Information
Name
Movie
# of Tickets
Cost
If the customer bought theater membership with the purchase, the function should display "Please note: The membership fee cannot be refunded.".
The function should then ask "Would you like to refund this purchase?".
If they enter 'y' or 'Y', the customer should be refunded the tickets and removed from the purchase should be removed from the customerArr. If they bought membership with the purchase, the customer should be left in the array with the purchase cost being set to the membership fee. All other information should be set to blank. Refunds should be concluded with the message "Your purchase has been refunded".
All other inputs are treated as no and exit the function.
YOU MUST DOCUMENT THIS FUNCTION AND FOLLOW C++ STANDARDS TO GET THE EXTRA CREDIT! 

Program Requirements:

Your program MUST follow the C++ Standards Document provided on CANVAS.
Your program MUST compile for you to get credit. 
Your program CANNOT use vectors.
Your program should match the provided program output. 
Your program should use the appropriate datatypes for each variable. 
Your program should close any files it opens.
Any output which uses money should have a $ and  should be properly rounded to the nearest hundredth place (or cent).
Use the provided szBreakMessage variable to print out the stars shown in the program.
Program Tips:

This program has several components. Work on a single part at a time and fully test it before moving on to the next part. Since there is no penalty for submitting multiple times (only the last submission is graded), I recommend you submit the assignment each time you finish developing a part. That way, if you don't finish it all in time, you will still receive partial credit.
You do not have to develop these parts in the order listed on the assignment. If you get stuck on a part, it may be a good idea to skip it and move on to the next one.
It may be a good idea to write helper functions for tasks you repeat multiple times. For example, you might want a function which determines if someone is a theater member.  
