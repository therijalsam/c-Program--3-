#include "movie_simulation_program_3.h"

/*********************************************************************
string promptForFilename()
Purpose:
    Helper function ask the user for a valid file path
Parameters:
    -
Return Value:
    Valid filepath string
Notes:
    -
*********************************************************************/
string promptForFilename()
{
   string filepath;
    do {
        cout << "Please enter the filename : ";
        cin >> filepath;
        if (filepath == "exit") {
            return 0;
        } else if (filepath.find(".txt") != string::npos && filepath.find(" ") == string::npos) {
            return filepath;
        } else {
            cout<<endl;
            cout << "Invalid filename. Please enter a valid filename ending with '.txt' and without spaces." << endl;
        }
    } while (true);


}

/*********************************************************************
void processTheaterInformation(fstream& fileInput, Theater& myTheater)
Purpose:
    Function to read theater text file and process the information
    into a theater structure
Parameters:
    I/O fstream& fileInput   File stream to read theater info
    I/O Theater& myTheater   Theater structure to populate
Return Value:
    -
Notes:
    This function does not validate the file structure it is provided
*********************************************************************/
void processTheaterInformation(fstream& fileInput, Theater& myTheater)
{
    string filename;
    // to exit the file path
    do {
        cout << "Enter you file Path : ";
        cin >> filename;
        if (filename == "exit") {
            cout << "Exiting function due to early exiting of file prompt" << endl;
            return;
        }
        fileInput.open(filename);
        if (!fileInput.is_open()) {
            cout << "File not found or unable to open. Please enter a valid filename." << endl;
        }
    } while (!fileInput.is_open());

    
    getline(fileInput, myTheater.szName); // Read theater name (1st line) and store it in the theater structure

    
    fileInput >> myTheater.iNumberScreens;// Read the number of theater rooms (2nd line) and store it in the theater structure
    fileInput.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

    
    string line; // Read theater room information
    getline(fileInput, line); // Skip the line with '*Theater Rooms*'

    for (int i = 0; i < myTheater.iNumberScreens; ++i) {
        // Read room name, parking spots, and movie name
        getline(fileInput, line);
        stringstream ss(line);
        ss >> myTheater.roomsArr[i].szName >> myTheater.roomsArr[i].iParkingCapacity;
        myTheater.roomsArr[i].iParkingAvailable = myTheater.roomsArr[i].iParkingCapacity;
        getline(ss, myTheater.roomsArr[i].szMovieShowing, '\n'); 
        // Read the rest of the line
    }


    getline(fileInput, line);    // Ignore the line containing '*Pricing*'

    
    fileInput >> myTheater.dPricingArr[0] >> myTheater.dPricingArr[1] >> myTheater.dPricingArr[2] >> myTheater.dPricingArr[3] >> myTheater.dPricingArr[4];// Read pricing information and store it in the theater structure
    
   
    fileInput.close(); // Close the file after processing
}


/*********************************************************************
void displayMenu(string szMenuName, string szChoicesArr[], int iChoices)
Purpose:
    Function to display the menu choices of a provided menu
Parameters:
    I   string szMenuName       Title of the displayed menu
    I   string szChoicesArr     Menu choices to be displayed
    I   int iChoices            Number of menu choices    
Return Value:
    -
Notes:
    Menu options are displayed starting at 1
    The last menu option should always be displayed as -1
*********************************************************************/
void displayMenu(string szMenuName, string szChoicesArr[], int iChoices)
{
    cout << szBreakMessage;
    cout << szMenuName << endl;
    cout << szBreakMessage;
    for (int i = 0; i < iChoices-1; ++i) {
        cout << i + 1 << ". " << szChoicesArr[i] << endl;
    }
    cout << "-1. Exit " << szMenuName << endl;
    cout << szBreakMessage;

 

}
/*********************************************************************
void displayTheaterInfo(const Theater myTheater)
Purpose:
    Function to display basic theater information
Parameters:
    I   Theater myTheater   Populated Theater info   
Return Value:
    -
Notes:
    -
*********************************************************************/
void displayTheaterInfo(const Theater myTheater)
{
    cout << "Theater Information" << endl;
    cout << szBreakMessage;

    cout << "Name: " << myTheater.szName << endl;
    cout << "Rooms: " << myTheater.iNumberScreens << endl;

    int totalSeats = 0;
    for (int i = 0; i < myTheater.iNumberScreens; ++i) {
        totalSeats += myTheater.roomsArr[i].iParkingCapacity;
    }
    cout << "Total seats: " << totalSeats << endl;

    cout << szBreakMessage;
}

/*********************************************************************
void displayNowShowing(const Theater myTheater)
Purpose:
    Function to display all movies currently showing
Parameters:
    I   Theater myTheater   Populated Theater info   
Return Value:
    -
Notes:
    Movies are displayed starting at 0
*********************************************************************/
void displayNowShowing(const Theater myTheater)
{
     cout << "Now Showing" << endl;
    cout << szBreakMessage;

    // Display the movies currently showing from lines 4, 5, and 6 of the theater info
    for (int i = 0; i < 3; ++i) {
        string movieTitle = myTheater.roomsArr[i].szMovieShowing;
        // Loop through each character and replace underscores with spaces
        for (char& cbar : movieTitle) {
            if (cbar == '_') {
                cbar = ' ';
            }
        }
        cout << i << ". " << movieTitle << endl;
    }

    cout << szBreakMessage;
}
/*********************************************************************
CustomerTicket buyTickets(Theater& myTheater)
Purpose:
    Function to handle customer buying tickets
Parameters:
    I/O Theater myTheater       Populated Theater info
Return Value:
    Populated CustomerTicket if transaction was successful
    Empty Customer Ticker if transaction was unsuccessful
Notes:
    -
*********************************************************************/
/*********************************************************************
CustomerTicket buyTickets(Theater& myTheater)
Purpose:
    Function to handle customer buying tickets
Parameters:
    I/O Theater myTheater       Populated Theater info
Return Value:
    Populated CustomerTicket if transaction was successful
    Empty Customer Ticker if transaction was unsuccessful
Notes:
    -
*********************************************************************/
CustomerTicket buyTickets(Theater& myTheater) {
    CustomerTicket tempCust;
    int movieChoice;
     cout << szBreakMessage;
    cout << "Buying Tickets"<<endl;
    cout << szBreakMessage;

    cout << "Enter Customer Name: ";
    cin >> tempCust.szName;

    for (int i = 0; i < myTheater.iCurrentCustomers; i++) {
        if (myTheater.customersArr[i].szName == tempCust.szName) {
            cout << "You are only allowed 1 ticket purchase per account\n";
            tempCust.szName = "";
            cout << szBreakMessage << endl;
            return tempCust;
        }
    }

    //bool isMember = false;
    int i=0;
    for (i = 0; i < myTheater.iCurrentMembers; i++) {
        if (myTheater.membersArr[i].szName == tempCust.szName) {
            //myTheater.customersArr[i].bBoughtMembership = true;
            cout << "Welcome back " << tempCust.szName << endl;
            break;
        }
    }

    if (myTheater.customersArr[i].bBoughtMembership) {
        while (true) {
            displayNowShowing(myTheater);
            cout << "What movie would you like to see? ";
            cin >> movieChoice;
            cout << "Movie Location: " << myTheater.roomsArr[movieChoice].szName << endl;
            cout << "Seats Remaining: " << myTheater.roomsArr[movieChoice].iParkingAvailable<< endl;

            

            while (true) {
                cout << "\n# of member tickets: ";
                cin >> tempCust.iNumberTickets;
                if (tempCust.iNumberTickets <= 0 || tempCust.iNumberTickets > myTheater.roomsArr[movieChoice].iParkingCapacity) {
                    cout << "Please make sure you order at least one ticket and not over the availability.\n";
                    continue;
                } 
                else {
                    break;
                }
            }
            if (myTheater.roomsArr[movieChoice].iParkingAvailable == 0) {
                cout << "Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                continue;
            }

            myTheater.roomsArr[movieChoice].iParkingAvailable -= tempCust.iNumberTickets;
            tempCust.szMovie = myTheater.roomsArr[movieChoice].szMovieShowing;
            tempCust.dPurchaseCost = tempCust.iNumberTickets * (myTheater.dPricingArr[3]) * (1 + dSALES_TAX);

            break; // Exiting the loop after successful purchase
        }

    } 
    
    else {
        char choice;
        cout << "\nDo you want to become a member (Y/N)? ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            tempCust.bBoughtMembership = true;
            myTheater.membersArr[myTheater.iCurrentMembers].szName = tempCust.szName;
            myTheater.iCurrentMembers += 1;

            while (true) {
                displayNowShowing(myTheater);
                cout << "What movie would you like to see? ";
                cin >> movieChoice;
                cout << "Movie Location: " << myTheater.roomsArr[movieChoice].szName << endl;
                cout << "Seats Remaining: " << myTheater.roomsArr[movieChoice].iParkingAvailable<< endl;

                // if (myTheater.roomsArr[movieChoice].iParkingAvailable == 0) {
                //     cout << "Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                //     continue;
                // }

                while (true) {
                    cout << "\n# of member tickets: ";
                    cin >> tempCust.iNumberTickets;
                    if (tempCust.iNumberTickets <= 0 || tempCust.iNumberTickets > myTheater.roomsArr[movieChoice].iParkingCapacity) {
                        cout << "Please make sure you order at least one ticket and not over the availability.\n";
                        continue;
                    } 
                    else {
                        break;
                    }
                }
                
                if (myTheater.roomsArr[movieChoice].iParkingAvailable == 0) {
                    cout << "Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                    continue;
                }
                myTheater.roomsArr[movieChoice].iParkingAvailable -= tempCust.iNumberTickets;
                tempCust.szMovie = myTheater.roomsArr[movieChoice].szMovieShowing;
                tempCust.dPurchaseCost = (tempCust.iNumberTickets * (myTheater.dPricingArr[3]) + (myTheater.dPricingArr[4])) * (1 + dSALES_TAX);

                break; // Exiting the loop after successful purchase
            }

        } 
        
        else if (choice == 'N' || choice == 'n') {
            int tAdult, tSenior, tChild;

            while (true) {
                cout<<endl;
                cout<<endl;
                displayNowShowing(myTheater);
                cout << "What movie would you like to see? ";
                cin >> movieChoice;
                cout << "Movie Location: " << myTheater.roomsArr[movieChoice].szName << endl;
                cout << "Seats Remaining: " << myTheater.roomsArr[movieChoice].iParkingAvailable << endl;

               
                while (true) {
                    cout << "\n# of adult tickets: ";
                    cin >> tAdult;
                    cout << "# of senior tickets: ";
                    cin >> tSenior;
                    cout << "# of child tickets: ";
                    cin >> tChild;

                    tempCust.iNumberTickets = tAdult + tSenior + tChild;
                    if (tempCust.iNumberTickets <= 0 || tempCust.iNumberTickets > myTheater.roomsArr[movieChoice].iParkingCapacity) {
                        cout << "Please make sure you order at least one ticket and not over the availability.\n";
                        continue;
                    } 
                    else {
                        break;
                    }
                    
                }
                
                if (myTheater.roomsArr[movieChoice].iParkingAvailable == 0) {
                    cout << "Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                    continue;
                }

                myTheater.roomsArr[movieChoice].iParkingAvailable -= tempCust.iNumberTickets;
                tempCust.szMovie = myTheater.roomsArr[movieChoice].szMovieShowing;

                float Total = (tAdult * myTheater.dPricingArr[0]) + (tSenior * myTheater.dPricingArr[1]) + (tChild * myTheater.dPricingArr[2]);
                tempCust.dPurchaseCost = (1 + dSALES_TAX) * Total;

                break; 
            }
        }
    }

    cout << fixed << setprecision(2) << "\nTotal Price: $" << tempCust.dPurchaseCost << endl;
    //cout << szBreakMessage;
    return tempCust;
}



// Extra Credit Function
void refundTickets(Theater& myTheater) {
    string customerName;
    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, customerName);

    bool found = false;
    for (int i = 0; i < myTheater.iCurrentCustomers; ++i) {
        if (customerName == myTheater.customersArr[i].szName) {
            found = true;
            cout << "Customer Information:" << endl;
            cout << "Name: " << myTheater.customersArr[i].szName << endl;
            cout << "Movie: " << myTheater.customersArr[i].szMovie << endl;
            cout << "# of Tickets: " << myTheater.customersArr[i].iNumberTickets << endl;
            cout << "Cost: $" << fixed << setprecision(2) << myTheater.customersArr[i].dPurchaseCost << endl;

            if (myTheater.customersArr[i].bBoughtMembership) {
                cout << "Please note: The membership fee cannot be refunded." << endl;
            }

            char response;
            cout << "Would you like to refund this purchase? (Y/N): ";
            cin >> response;

            if (response == 'y' || response == 'Y') {
                // Refund the full purchase
                myTheater.roomsArr[i].iParkingAvailable += myTheater.customersArr[i].iNumberTickets;
                if (!myTheater.customersArr[i].bBoughtMembership) {
                    myTheater.customersArr[i] = CustomerTicket(); // Reset customer information
                } else {
                    // If customer bought membership with the purchase, set purchase cost to membership fee
                    double refundAmount = myTheater.dPricingArr[4] * (1 + dSALES_TAX); // Membership amount with sales tax
                    myTheater.customersArr[i].dPurchaseCost = refundAmount;
                }
                cout << "Your purchase has been refunded." << endl;
            } else {
                cout << "Refund cancelled." << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "No customer found." << endl;
    }
}


/*********************************************************************
double calculateTotalSales(const Theater& myTheater)
Purpose:
    Function to calculate the total sales of the theater
Parameters:
    I   Theater myTheater       Populated Theater info
Return Value:
    Total sales
Notes:
    This function should only be called by the admin
*********************************************************************/
double calculateTotalSales(const Theater& myTheater) {
    double totalSales = 0.0;

    for (int i = 0; i < myTheater.iCurrentCustomers; ++i) {
        totalSales += myTheater.customersArr[i].dPurchaseCost;
    }

    return totalSales;
}
/*********************************************************************
void storeData(const Theater myTheater, fstream& fileMemberIO, string szMode);
Purpose:
    Function to load data from the theater structure to a file
Parameters:
    I/O Theater& myTheater          Populated Theater info
    I/O fstream fileDataIO          File stream used to read file
    I   string szMode               What data to delete
Return Value:
    -
Notes:
    -
*********************************************************************/
void storeData(const Theater myTheater, fstream& fileMemberIO, string szMode)
{
  // Check if mode is valid
    if (szMode != "Customers" && szMode != "Members") {
        cout << "Invalid mode" << endl;
        return;
    }

    string filepath;
    // Ask for filepath until a valid one is provided
    do {
        cout << "Enter filepath: ";
        cin >> filepath;
        fileMemberIO.open(filepath, ios::out); // Open file for writing (overwrite if exists)
        if (!fileMemberIO.is_open()) {
            cout << "Unable to open file. Please enter a valid filepath." << endl;
        }
    } while (!fileMemberIO.is_open());

    // Write data to the file based on the mode
    if (szMode == "Customers") {
        // Write customer data
        for (int i = 0; i < myTheater.iCurrentCustomers; ++i) {
            // Replace spaces in customer name with underscores
            string customerName = myTheater.customersArr[i].szName;
            for (char& ch : customerName) {
                if (ch == ' ') {
                    ch = '_';
                }
            }

            // Replace spaces in movie title with underscores
            string movieTitle = myTheater.customersArr[i].szMovie;
            for (char& ch : movieTitle) {
                if (ch == ' ') {
                    ch = '_';
                }
            }

            fileMemberIO << customerName << " " << movieTitle << " "
                         << myTheater.customersArr[i].iNumberTickets << " "
                         << fixed << setprecision(2) << myTheater.customersArr[i].dPurchaseCost << " "
                         << myTheater.customersArr[i].bBoughtMembership << endl;
        }
    } else if (szMode == "Members") {
        // Write member data
        for (int i = 0; i < myTheater.iCurrentMembers; ++i) {
            fileMemberIO << myTheater.membersArr[i].szName << endl;
        }
    }

    // Close the file stream
    fileMemberIO.close();
}




/*********************************************************************
void loadData(Theater& myTheater, fstream& fileDataIO, string szMode);
Purpose:
    Function to load data from the theater structure to a file
Parameters:
    I/O Theater& myTheater          Populated Theater info
    I/O fstream fileDataIO          File stream used to read file
    I   string szMode               What data to delete
Return Value:
    -
Notes:
    -
*********************************************************************/

void loadData(Theater& myTheater, fstream& fileDataIO, string szMode)
{
    string szFilePath;
    szFilePath = promptForFilename();
    
    if(szFilePath == "EXIT") {
        cout << "Exiting without storing data." << endl;
        return;
    }

    fileDataIO.open(szFilePath);

    if (!fileDataIO.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    if(szMode == "Customers")
    {
        cout << "Loading Customers info from file\n";
        int i=0;
        
        while(!fileDataIO.eof())
        {
            fileDataIO >> myTheater.customersArr[i].szName;
            fileDataIO >> myTheater.customersArr[i].szMovie;
            fileDataIO >> myTheater.customersArr[i].iNumberTickets;
            fileDataIO >> myTheater.customersArr[i].dPurchaseCost;
            fileDataIO >> myTheater.customersArr[i].bBoughtMembership;
            i++;
        }
        myTheater.iCurrentCustomers = i+1;
    }

    else if(szMode == "Members")
    {

        cout << "Loading Members info from file\n";
        
        int i=0;
        while(!fileDataIO.eof())
        {
            fileDataIO >> myTheater.membersArr[i].szName;
            i++;
        }

    }

}


    

/*********************************************************************
void clearData(Theater& myTheater, string szMode);
Purpose:
    Function to delete data from the theater structure
Parameters:
    I/O Theater& myTheater          Populated Theater info
    I   string szMode               What data to delete
Return Value:
    -
Notes:
    Deleted theater customers are replaced with empty customers
*********************************************************************/
void clearData(Theater& myTheater, string szMode) {
    // Convert szMode to lowercase
    for (char& c : szMode) {
        c = tolower(c);
    }

    if (szMode == "customers") {
        // Clear customer data
        for (int i = 0; i < myTheater.iCurrentCustomers; ++i) {
            myTheater.customersArr[i].szName = "";
            myTheater.customersArr[i].szMovie = "";
            myTheater.customersArr[i].iNumberTickets = 0;
            myTheater.customersArr[i].dPurchaseCost = 0.0;
            myTheater.customersArr[i].bBoughtMembership = false;
        }
        myTheater.iCurrentCustomers = 0; // Reset the customer count
    } else if (szMode == "members") {
        // Clear member data
        for (int i = 0; i < myTheater.iCurrentMembers; ++i) {
            myTheater.membersArr[i].szName = "";
        }
        myTheater.iCurrentMembers = 0; // Reset the member count
    } else {
        // Invalid mode
        cout << "Invalid mode" << endl;
        return;
    }
}

