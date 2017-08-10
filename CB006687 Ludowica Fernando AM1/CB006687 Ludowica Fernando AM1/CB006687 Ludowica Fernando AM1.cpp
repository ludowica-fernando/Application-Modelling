//libraries used
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

/*self-referential structure*/
struct customerdetails
{
	int customernic;
	int customerid;
	string name;
	string address;
	int age;
	string gender;
	string loantype;
	int loanamount;
	int loanduration;
	string loanstatus;
	struct customerdetails *nextPtr; /*pointer to next node*/
};/*end structure customerdetails*/

typedef struct customerdetails CustomerDetails;
typedef CustomerDetails *CustomerDetailsPtr;
CustomerDetailsPtr startPtr = NULL;

/*self-referential structure*/
struct loandetails
{
	int customernic;
	int customerid;
	string name;
	string address;
	int age;
	string gender;
	string loantype;
	int loanamount;
	int loanduration;
	string loanstatus;
	struct loandetails *nextPtr;/*pointer to next node*/
};/*end structure loandetails*/

typedef struct loandetails LoanDetails;
typedef LoanDetails *LoanDetailsPtr;
LoanDetailsPtr headPtr = NULL;
LoanDetailsPtr tailPtr = NULL;
//LoanDetailsPtr sstartPtr = NULL;

/*self-referential structure*/
struct approvereject
{
	int customernic;
	int customerid;
	string name;
	string address;
	int age;
	string gender;
	string loantype;
	int loanamount;
	int loanduration;
	string loanstatus;;
	struct approvereject *nextPtr;/*pointer to next node*/
}; /*end structure approvereject*/

typedef struct approvereject ApproveReject;
typedef ApproveReject *ApproveRejectPtr;
//ApproveRejectPtr topPtr = NULL;
ApproveRejectPtr stacksPtr = NULL;

/*prototypes*/
void mainmenu();

int register_customer();
int unregister_customer();
int ViewCustomer();
void ViewAllCustomers(CustomerDetailsPtr currentPtr);
int update_customer();
int ApplyLoan();
int approve_reject(LoanDetailsPtr currentPtr);
int update_loan();
void ViewApprovedCustomers(CustomerDetailsPtr currentPtr);
void ViewPendingCustomers(CustomerDetailsPtr currentPtr);
void ViewRejectedCustomers(CustomerDetailsPtr currentPtr);
void applyLoan(CustomerDetailsPtr *startPtr, LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, int cid);


void insert(CustomerDetailsPtr *startPtr, string customername, string customeraddress, int age, string customergender, int cid);
char deleteItem(CustomerDetailsPtr *startPtr, string customername, string customeraddress, int age, string customergender, int cid);
int isEmpty(CustomerDetailsPtr startPtr);
int printlist(CustomerDetailsPtr *startPtr, int num);
int applyLoan(CustomerDetailsPtr *startPtr, int cid, string name, char type, int amount, int duration, string status);
int approveReject(LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, int cid, string status);
int updateloan(CustomerDetailsPtr *startPtr, int cid, string status);
int queueEmpty(LoanDetailsPtr headPtr);
void enqueue(LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, int cid, string customeraddress, int customerage, string customergender, char type, int amount, int duration, string status);
int dequeue(LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, int cid, string status);
void printQueue(LoanDetailsPtr currentPtr);
void UpdateMainStat(ApproveRejectPtr *topPtr, CustomerDetailsPtr *startPtr);
void approveRejectQueue(LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, ApproveRejectPtr *topPtr);
void displayqueue(LoanDetailsPtr currentPtr);




//variable declarations globally
int option; //selecting options from the menu
int a; //nic numbers
int b, c;
int cid; //cid numbers
int random; //random generator
int element;
int customerid;


//arrays
const int array_size = 100; //number of customers
int NIC_list[array_size] = { 001, 002, 003, 004, 005 }; //NIC array
int CID_list[array_size] = { 1, 2, 3, 4, 5, 6, 7, 8, 10 }; //CID array


//welcome message
void welcome()
{
	cout << "								    -- PEOPLE'S BANK --\n\n\n ";
	cout << "Welcome to People's Bank.\n ";
	cout << "\n\n      We are here to provide financial services that contribute to the quality of life,";
	cout << "and enterprise development, via affordable, \naccessible, and efficiently delivered solutions. ";
	cout << "We contribute to national economic development and we are also competitively profitable. ";
	cout << "\nWe believe in 'giving back' to the society we operate in, while being sustainable in our business practice. ";
	cout << "\n\nPress ENTER to continue.";
	getchar();

}


//menu with options
void mainmenu()
{
	/*Menu with options to select*/
	cout << "          \n\nMenu: \n\n";


	cout << "		   Option 1 : Register Customer\n\n";
	cout << "		   Option 2 : Unregister Customer\n\n";
	cout << "		   Option 3 : Update Customer\n\n";
	cout << "		   Option 4 : View Customer\n\n";
	cout << "		   Option 5 : View all Customers\n\n";
	cout << "		   Option 6 : Apply for a loan\n\n";
	cout << "		   Option 7 : Approve/Reject loan\n\n";
	cout << "		   Option 8 : Update loan status\n\n";
	cout << "		   Option 9 : View approved customers\n\n";
	cout << "		   Option 10: View pending customers\n\n";
	cout << "		   Option 11: View rejected customers\n\n";


	cout << "\nPlease enter your option.\n";
	/*loop to check validity of the input*/
	while (!(cin >> option))
	{
		cout << " Please re-enter a valid option." << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}

	/*loop to check whether the option chosen is valid*/
	while (option < 1 || option > 11)
	{
		cout << "Invalid Option, Press ENTER to go back to the Main Menu \n\n";
		getchar();
		getchar();
		mainmenu();

		cout << "Your Selected Option is  " << endl;
	}

	if (option == 1)
	{
		cout << "REGISTER CUSTOMER.\n";
		register_customer();

	}//end if
	else if (option == 2)
	{
		cout << "UNREGISTER CUSTOMER.\n";
		unregister_customer();

	}//end else if
	else if (option == 3)
	{
		cout << "UPDATE CUSTOMER.\n \n";
		update_customer();
	}//end else if
	else if (option == 4)
	{
		cout << "VIEW CUSTOMER. \n \n";
		ViewCustomer();
	}//end else if
	else if (option == 5)
	{
		cout << "VIEW ALL CUSTOMERS.\n";
		ViewAllCustomers(startPtr);

	}//end else if
	else if (option == 6)
	{
		cout << "APPLY FOR A LOAN.\n";
		ApplyLoan();

	}//end else if
	else if (option == 7)
	{
		cout << "APPROVE/REJECT LOAN.\n";
		approveRejectQueue(&headPtr, &tailPtr, &stacksPtr);
	}//end else if
	else if (option == 8)
	{
		cout << "UPDATE LOAN STATUS.\n";
		UpdateMainStat(&stacksPtr, &startPtr);

	}//end else if
	else if (option == 9)
	{
		cout << "VIEW APPROVED CUSTOMERS.\n";
		ViewApprovedCustomers(startPtr);
	}//end else if
	else if (option == 10)
	{
		cout << "VIEW PENDING CUSTOMERS.\n";
		ViewPendingCustomers(startPtr);
	}//end else if
	else if (option == 11)
	{
		cout << "VIEW REJECTED CUSTOMERS.\n";
		ViewRejectedCustomers(startPtr);
	}//end else if

	cout << endl;
	cout << "Press enter." << endl;
	getchar();
}// end main menu


/*to return to main menu or exit the function*/
void returntoMenu()
{
	int choice;
	cout << "Press 0 to view the Main Menu or 1 to exit the Program  \n\n " << endl;

	/*loop to check the validity*/
	while (!(cin >> choice))
	{
		cout << "Invalid input!  \n   Press 0 to view the Main Menu or 1 to exit the Program \n\n   " << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}
	if (choice == 0)
	{
		mainmenu();
	}// end if
	else if (choice == 1)
	{
		exit(0);
	}// end else if
	else
	{
		cout << "Invalid Input" << endl;
		returntoMenu();
	}//end else

}/*end returntoMenu function*/


/*search through the nic and cid arrays*/
int linear_search(const int array[], int searchKey, int sizeOfArray)
{
	for (int a = 0; a < sizeOfArray; a++)
	{
		if (searchKey == array[a])
		{
			return a;
		}
	}
	return -1; //incase the element is not found (NIC)

	getchar();
	cin.get();
}


/*creates a random number*/
int random_generator()
{
	srand(time(0));
	random = rand() % 100;

	return random;
}


int binary_search(int array[], int searchkey, int low, int high)
{
	int middle;
	while (low <= high)
	{
		middle = (low + high) / 2;

		if (searchkey == array[middle])
		{
			return middle;
		}
		else if (searchkey < array[middle])
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}
	return -1;
}


int bubble_sort(int CID_list[])
{
	int hold; //to hold values temporarily

	for (c = b + 1; c < array_size; c++)
	{
		for (b = 0; b < array_size - 1; b++)
		{
			if (CID_list[b] > CID_list[c])
			{
				hold = CID_list[b];
				CID_list[b] = CID_list[c];
				CID_list[c] = hold;
			}
		}
	}
	return 0;
}

/*insert a new customer into the list in sorted order*/
void insert(CustomerDetailsPtr *startPtr, string customername, string customeraddress, int customerage, string customergender, int cid, int nic, string status)
{
	CustomerDetailsPtr newPtr = NULL; /*pointer to new node*/
	CustomerDetailsPtr previousPtr = NULL; /*pointer to previous node in list*/
	CustomerDetailsPtr currentPtr = NULL; /*pointer to current node in list*/

	newPtr = new CustomerDetails; /*create new node*/

	if (newPtr != NULL) /*if space is available*/
	{

		newPtr->name = customername; /*place customername in node*/
		newPtr->address = customeraddress;/*place customeraddress in node*/
		newPtr->age = customerage; /*place customerage in node*/
		newPtr->gender = customergender; /*place customergender in node*/
		newPtr->customerid = cid; /*place cid in node*/
		newPtr->customernic = nic; /*place nic in node*/
		newPtr->loanstatus = status; /*place status in node*/
		newPtr->nextPtr = NULL; /*node does not link to another node*/

		previousPtr = NULL;
		currentPtr = *startPtr;

		/*loop to find the correct location in the list*/
		while (currentPtr != NULL && customername > currentPtr->name)
		{
			previousPtr = currentPtr; /*walk to...*/
			currentPtr = currentPtr->nextPtr; /* ...next node*/
		}//end while

		/*insert new node at the beginning of the list*/
		if (previousPtr == NULL)
		{
			newPtr->nextPtr = *startPtr;
			*startPtr = newPtr;
		}// end if

		/*insert new node between previousPtr and currentPtr*/
		else
		{
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}//end else

	}// end if
	else
	{
		cout << "Customer details not inserted. No memory available.\n" << customername;
	}//end else
}


/*delete a customer from the list*/
char deleteItem(CustomerDetailsPtr *startPtr, int cid)
{
	CustomerDetailsPtr previousPtr = NULL; /*pointer to previous node in list*/
	CustomerDetailsPtr currentPtr = NULL; /*pointer to current node in list*/
	CustomerDetailsPtr tempPtr = NULL; /*temporary node pointer*/

	/*delete first node*/
	if (cid == (*startPtr)->customerid)
	{
		tempPtr = *startPtr; /*hold onto node being removed*/
		*startPtr = (*startPtr)->nextPtr; /*de-thread the node*/
		delete(tempPtr); /*free the de-threaded node*/
		return cid;
	} //end if

	else
	{
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->nextPtr;

		/*loop to find the correct location in the list*/
		while (currentPtr != NULL && currentPtr->customerid != cid) {
			previousPtr = currentPtr; /*walk to...*/
			currentPtr = currentPtr->nextPtr; /*...next node*/
		}//end while

		/*delete node at currentPtr*/
		if (currentPtr != NULL)
		{
			tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			delete(tempPtr);
			return cid;
		}//end if
	}//end else
	return '\0';
}//end delete function


/*check whether the list is empty*/
int isEmpty(CustomerDetailsPtr startPtr)
{
	return startPtr == NULL;
}//end isEmpty function


/*to print the customer details*/
int printlist(CustomerDetailsPtr *startPtr, int cid)
{
	CustomerDetailsPtr previousPtr = NULL; /*pointer to previous node*/
	CustomerDetailsPtr currentPtr = NULL; /*pointer to the current node*/

	if (cid == (*startPtr)->customerid)
	{
		cout << "______________________________________" << endl;
		cout << "\nCustomer Name :-------    " << (*startPtr)->name << endl;
		cout << "Customer ID :-------      " << (*startPtr)->customerid << endl;
		cout << "Customer Address :------  " << (*startPtr)->address << endl;
		cout << "Customer Age :-------     " << (*startPtr)->age << endl;
		cout << "Customer Gender :-------  " << (*startPtr)->gender << endl;
		cout << "Customer NIC :-------     " << (*startPtr)->customernic << endl;
		cout << "Customer status :-------  " << (*startPtr)->loanstatus << endl;
		cout << "______________________________________" << endl;
	}// end if

	else
	{
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->nextPtr;

		while (currentPtr != NULL && currentPtr->customerid != cid)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}//end while

		/*if list is not empty*/
		if (currentPtr != NULL)
		{
			cout << "______________________________________" << endl;
			cout << "\nCustomer Name :-------   " << currentPtr->name << endl;
			cout << "Customer ID :-------     " << currentPtr->customerid << endl;
			cout << "Customer Address :------ " << currentPtr->address << endl;
			cout << "Customer Age :-------    " << currentPtr->age << endl;
			cout << "Customer Gender :------- " << currentPtr->gender << endl;
			cout << "Customer NIC :-------    " << currentPtr->customernic << endl;
			cout << "Customer status :-------     " << currentPtr->loanstatus << endl;

			cout << "______________________________________" << endl;
		}// end if
	}//end else
	return '\0';

}/*end printlist function*/


/*to update the customer address*/
int updatecus(CustomerDetailsPtr *startPtr, int cid, string customeraddress)
{
	CustomerDetailsPtr previousPtr = NULL; /*pointer to the previous node*/
	CustomerDetailsPtr currentPtr = NULL; /*pointer to the current node*/

	/*if the node is the first node*/
	if (cid == (*startPtr)->customerid)
	{
		(*startPtr)->address = customeraddress;
	}// end if

	else
	{
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->nextPtr;

		/*loop to find the correct location in the list*/
		while (currentPtr != NULL && currentPtr->customerid != cid)
		{
			previousPtr = currentPtr; /*walk to...*/
			currentPtr = currentPtr->nextPtr; /*... next node*/
		}//end while

		/*update node at currentPtr*/
		if (currentPtr != NULL)
		{
			currentPtr->address = customeraddress;
		}//end if

	}//end else

	return '\0';

}//end updatecus function

/*to check whether the queue is empty*/
int queueEmpty(LoanDetailsPtr headPtr)
{
	return headPtr == NULL;
}/*end function queueEmpty*/


/*print queue*/
void printQueue(LoanDetailsPtr currentPtr)
{
	/*if queue is empty*/
	if (currentPtr == NULL)
	{
		cout << "Queue is empty.\n\n";
	}//end if
	else
	{
		cout << "The queue is:\n";

		/*while the node is not at the end of queue*/
		while (currentPtr != NULL)
		{
			cout << "______________________________________" << endl;
			cout << "Customer ID" << currentPtr->customerid << "-->";
			cout << "Customer Name" << currentPtr->name << "-->";
			cout << "Customer Loan Type" << currentPtr->loantype << "-->";
			cout << "Customer Loan Amount" << currentPtr->loanamount << "-->";
			cout << "Customer Loan Duration" << currentPtr->loanduration << "-->";
			cout << "Customer Loan Status" << currentPtr->loanstatus << "-->";
			cout << "______________________________________" << endl;
			currentPtr = currentPtr->nextPtr;
		}//end while

		cout << "NULL\n\n";
	}//end else
}/*end function printQueue*/


/*print stack*/
void printStack(ApproveRejectPtr currentPtr)
{
	/*if stack is empty*/
	if (currentPtr == NULL)
	{
		cout << "The stack is empty.\n\n";
	}//end if
	else
	{
		cout << "The stack is :\n " << endl;

		/*while not the end of the stack*/
		while (currentPtr != NULL)
		{
			cout << currentPtr->customerid << "-->";
			cout << currentPtr->loanstatus << "-->";
		}/*end while*/

	}/*end else*/

}/*end function printStack*/


/*to check whether the stack is empty*/
int stackEmpty(ApproveRejectPtr topPtr)
{

	return topPtr == NULL;

}/* end function stackEmpty*/


//option 1
int register_customer()
{
	int customernic;
	string name;
	int age;
	string address;
	string gender;
	char gender_choice;
	string m = "Male";
	string f = "Female";
	string status = "General";

	cout << "Enter customer NIC number.\n" << endl;
	while (!(cin >> customernic))    //validation check for the type of data

	{
		cout << " Please re-enter the NIC number. \n" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}//end while

	/*searching the NIC from the array*/
	element = linear_search(NIC_list, customernic, array_size);

	if (element != -1)
	{
		cout << "\n\nCustomer has already been registered in element number " << element << "." << endl;
	}//end if
	else
	{
		cout << "\n\n\nCustomer doesn't exist. Please continue with the registration.\n " << endl;

		//for (a = 0; a < array_size; a++)
		//{
		//	if (NIC_list[a] == 0)
		//	{
		//		NIC_list[a] = customernic;
		//	}//end if
		//}

		NIC_list[b] = customernic;
		b++;

		/*customer registration form*/
		cout << "\nEnter customer name.\n ";
		cin >> name;

		cout << "\nEnter customer address.\n ";
		cin >> address;

		cout << "\nEnter customer age.\n " << endl;
		while (!(cin >> age || age > 100 || age < 21)) /*loop to make sure the age is in the correct range*/
		{
			cout << "Invalid age category. Please try again.\n" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}//end while
		cout << endl;

		cout << "\nEnter customer gender. (Enter M if male or F if female.)\n ";
		cin >> gender_choice;

		while ((gender_choice != 'm') && (gender_choice != 'f')) /*loop to make sure the gender is valid*/
		{
			cout << " Please enter a valid  character for the customer gender " << endl;

			cout << "  Customer's gender is (m or f)" << endl;
			cin >> gender_choice;
		}//end while

		if (gender_choice == 'm' || gender_choice == 'M')
		{
			gender = m;
		}//end if
		else if (gender_choice == 'f' || gender_choice == 'F')
		{
			gender = f;
		}//end else if

		cout << endl;

		/*to generate a random CID*/
		random_generator();

		element = linear_search(CID_list, random, array_size);

		while (element != -1)
		{
			random_generator();
		}//end while

		int random = random_generator();

		/*	for (b = 0; b < array_size; b++)
		{
		if (CID_list[b] == 0)
		{
		CID_list[b] = random;
		}
		}
		*/
		cout << "\n\nThe Customer ID of the above customer is :--- " << random << ".\n" << endl;

		CID_list[b] = random;
		b++;

		/*inserting details into the customerdetails structure*/
		insert(&startPtr, name, address, age, gender, random, customernic, status);

		cout << "Customer registration was successful . . . \n\n " << endl;
	}//end else

	returntoMenu();
	getchar();
	return 0;
}/*end register_customer function*/


//option 2
int unregister_customer()
{
	/*if the list is not empty*/
	if (!isEmpty(startPtr))
	{
		cout << "Enter customer ID.\n" << endl;
		while (!(cin >> customerid)) /*validation check to make sure the input is valid*/
		{
			cout << "Please re-enter customer ID." << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}//end while
		element = linear_search(CID_list, customerid, array_size); /*searching for the customer ID through the array*/

		if (element == -1) /*customer ID not found*/
		{
			cout << "Customer doesn't exist.\n" << endl;
		}//end if

		if (deleteItem(&startPtr, customerid)) /*customer ID found*/
		{
			cout << "No customers in the list. \n " << endl << endl;
		}//end if
	}//end if

	else
	{
		cout << " Customer list is empty. " << endl << endl;
	}//end else

	returntoMenu();
	return 0;
}/*end unregister_customer function*/


//option 3
int update_customer()
{
	string address;

	/*if the list is not empty*/
	if (!isEmpty(startPtr))
	{
		cout << "Enter customer ID.\n" << endl;
		while (!(cin >> customerid))/*validation check to make sure the input is valid*/
		{
			cout << "Please re-enter customer ID." << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}//end while

		element = linear_search(CID_list, customerid, array_size); /*searching for the customer ID*/

		if (element == -1)/*customer id not found*/
		{
			cout << "Customer doesn't exist.\n" << endl;
		}//end if

		cout << "Enter New Address. " << endl;
		cin >> address;

		if (updatecus(&startPtr, customerid, address))/*if customer ID is found, customer exists*/
		{
			cout << "Customer has been removed. \n " << endl << endl;
		}//end if
	}//end if

	else/*customer list is empty*/
	{
		cout << " Customer doesn't exist." << endl;
	}//end else

	returntoMenu();
	return 0;
}/*end update_customer function*/


//option 4
int ViewCustomer()
{
	/*if list is not empty*/
	if (!isEmpty(startPtr))
	{
		cout << "Enter Customer ID. ";
		cin >> cid;
		cout << endl;

		/*prints customer details if customer ID is found*/
		if (printlist(&startPtr, cid))
		{
			cout << "Customer Details\n\n" << endl;
		}//end if
		else
		{
			cout << "Customer doesn't exist.\n" << endl;
		}//end else
	}//end if

	returntoMenu();
	return 0;
}//end ViewCustomer function

//option 5
void ViewAllCustomers(CustomerDetailsPtr currentPtr)
{
	/*if list is empty*/
	if (currentPtr == NULL)
	{
		cout << " Customer List is Empty !  ";
	}//end if

	else /*if list is not empty*/
	{
		cout << " Customer List is -  " << endl << endl;

		/*loop if the currentPtr is not empty*/
		while (currentPtr != NULL)
		{
			cout << "______________________________________" << endl;
			cout << "\nCustomer Name   :  " << currentPtr->name << endl << endl;
			cout << "Customer ID     :  " << currentPtr->customerid << endl;
			cout << "______________________________________" << endl;
			currentPtr = currentPtr->nextPtr;
			cout << endl;

		} // end while

	} // end else 
	returntoMenu();
}/*end ViewAllCustomers function*/


//option 6 
int ApplyLoan()
{
	cout << "Enter Customer ID ";
	while (!(cin >> customerid)) /*validation check for CID*/
	{
		cout << "Please enter Customer ID again" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}
	element = linear_search(CID_list, customerid, array_size);/*searching the Customer ID in the array*/

	if (element != -1)
	{
		applyLoan(&startPtr, &headPtr, &tailPtr, customerid); /*calls the applyLoan function*/
	}

	/*customer not found*/
	else
	{
		cout << "Customer ID doesnt exist\n\n" << endl;

	}


	returntoMenu();
	return 0;
}/*end ApplyLoan function*/

void applyLoan(CustomerDetailsPtr *startPtr, LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, int cid)
{
	LoanDetailsPtr newPtr;
	CustomerDetailsPtr currentPtr;
	CustomerDetailsPtr previousPtr;
	string loantype;
	char loan_choice;
	int loanamount;
	int loanduration;
	string stat_p = "Pending";
	string ed = "Education";
	string bu = "Business";

	/*locates the customer in the list*/
	if (cid == (*startPtr)->customerid)
	{
		/*customer type is general*/
		if ((*startPtr)->loanstatus == "General")
		{
			cout << "Enter Loan Type. ( B for Business and E for Education )\n" << endl;
			cin >> loan_choice;
			while ((loan_choice != 'b') && (loan_choice != 'e')) /*validation check for the correct loan type*/
			{
				cout << "Please re-enter Loan Type." << endl;
				cin >> loan_choice;
			}//end while

			if (loan_choice == 'b' || loan_choice == 'B')
			{
				loantype = bu;
				cout << bu << " Loan " << endl;
			}//end if
			else if (loan_choice == 'e' || loan_choice == 'E')
			{
				loantype = ed;
				cout << ed << " Loan " << endl;
			}//end else if

			cout << endl;

			cout << "Enter Loan Amount. " << endl;
			//	cin >> loanamount;
			while (!(cin >> loanamount))
			{
				cout << " Please re-enter loan amount.\n" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}//end while
			cout << endl;

			cout << "Enter Loan Duration (in months) " << endl;
			//cin >> loanduration;
			while (!(cin >> loanduration))
			{
				cout << " Please re-enter loan duration.\n" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}//end while
			cout << endl;

			/* updates the Customer details structure with the entered loan details */
			(*startPtr)->loanstatus = stat_p;
			(*startPtr)->loanamount = loanamount;
			(*startPtr)->loanduration = loanduration;
			(*startPtr)->loantype = loantype;

			newPtr = new LoanDetails;/*creates a new node*/

			/*if space is available*/
			if (newPtr != NULL)
			{
				/*passing the customer details from linked list to queue*/
				newPtr->name = (*startPtr)->name;
				newPtr->address = (*startPtr)->address;
				newPtr->age = (*startPtr)->age;
				newPtr->gender = (*startPtr)->gender;
				newPtr->customerid = (*startPtr)->customerid;
				newPtr->customernic = (*startPtr)->customernic;
				newPtr->loanamount = (*startPtr)->loanamount;
				newPtr->loanduration = (*startPtr)->loanduration;
				newPtr->loanstatus = (*startPtr)->loanstatus;
				newPtr->loantype = (*startPtr)->loantype;

				newPtr->nextPtr = NULL;

				/*if queue is empty*/
				if (*headPtr == NULL)
				{
					*headPtr = newPtr;
				}
				else /*if queue is not empty*/
				{
					(*tailPtr)->nextPtr = newPtr;
				}
				*tailPtr = newPtr;

				cout << "Loan was applied successfully.\n\n\n\n\n" << endl;
			}
			else
			{
				cout << " No memory available in queue" << endl;
			}

		}
		else
		{
			cout << " Customer " << customerid << " has already obtained a loan." << endl;
		}

	} // end if

	else
	{
		previousPtr = *startPtr; /*walk to...*/
		currentPtr = (*startPtr)->nextPtr; /*...next node*/

		/*locating the correct node*/
		while (previousPtr != NULL && currentPtr->customerid != cid)
		{
			previousPtr = currentPtr; /*walk to...*/
			currentPtr = currentPtr->nextPtr; /*...next node*/
		} // end while 

		/*currentPtr is not NULL*/
		if (currentPtr != NULL)
		{
			/*customer type is general*/
			if (currentPtr->loanstatus == "General")
			{
				cout << "Enter Loan Type. ( B for Business and E for Education )\n" << endl;
				cin >> loan_choice;
				while ((loan_choice != 'b') && (loan_choice != 'e')) /*validation check for loan type*/
				{
					cout << "Please enter Loan Type again" << endl;
					cin >> loan_choice;
				}//end while

				if (loan_choice == 'b' || loan_choice == 'B')
				{
					loantype = bu;
					cout << bu << " Loan " << endl;
				}//end if
				else if (loan_choice == 'e' || loan_choice == 'E')
				{
					loantype = ed;
					cout << ed << " Loan " << endl;
				}//end else if

				cout << endl;

				cout << "Enter Loan Amount " << endl;
				cin >> loanamount;

				cout << endl;

				cout << "Enter Loan Duration (in months) " << endl;
				cin >> loanduration;


				cout << endl;

				currentPtr->loanstatus = stat_p;
				currentPtr->loanamount = loanamount;
				currentPtr->loanduration = loanduration;
				currentPtr->loantype = loantype;

				newPtr = new LoanDetails; /*creating new node*/

				/*queue not empty*/
				if (newPtr != NULL)
				{
					/*passing values from currentPtr to newPtr*/
					newPtr->name = currentPtr->name;
					newPtr->address = currentPtr->address;
					newPtr->age = currentPtr->age;
					newPtr->gender = currentPtr->gender;
					newPtr->customerid = currentPtr->customerid;
					newPtr->customernic = currentPtr->customernic;
					newPtr->loanamount = currentPtr->loanamount;
					newPtr->loanduration = currentPtr->loanduration;
					newPtr->loanstatus = currentPtr->loanstatus;
					newPtr->loantype = currentPtr->loantype;

					newPtr->nextPtr = NULL;

					if (*headPtr == NULL)
					{
						*headPtr = newPtr;
					}//end if
					else
					{
						(*tailPtr)->nextPtr = newPtr;
					}//end else
					*tailPtr = newPtr;

				}//end if

				else
				{
					cout << "No memory available!" << endl;
					returntoMenu();
				}//end else
				cout << "Loan was applied successfully.\n\n\n\n\n" << endl;
			}  // end if

			else
			{
				cout << " Customer " << customerid << " has already obtained a loan" << endl;
				returntoMenu();
			}//end else

		} // end if

		else
		{
			cout << " Customer not found." << endl;
			returntoMenu();
		}//end else
	} // end else 

} /*end apply loan function*/


void displayqueue(LoanDetailsPtr currentPtr)
{
	/*if the list is empty*/
	if (currentPtr == NULL)
	{
		cout << "List is empty !\n\n" << endl;
	}

	/*if the list is not empty*/
	else
	{
		/*prints the customer details*/
		cout << "______________________________________\n" << endl;
		cout << "\nCustomer Name :-------    " << currentPtr->name << "\n" << endl;
		cout << "Customer ID :-------      " << currentPtr->customerid << "\n" << endl;
		cout << "Customer Address :------  " << currentPtr->address << "\n" << endl;
		cout << "Customer Age :-------     " << currentPtr->age << "\n" << endl;
		cout << "Customer Gender :-------  " << currentPtr->gender << "\n" << endl;
		cout << "Customer NIC :-------     " << currentPtr->customernic << "\n" << endl;
		cout << "Customer status :-------  " << currentPtr->loanstatus << "\n" << endl;
		cout << "\n______________________________________" << endl;

	} // end else

} /*end displayqueue function*/

//option 7
void approveRejectQueue(LoanDetailsPtr *headPtr, LoanDetailsPtr *tailPtr, ApproveRejectPtr *topPtr)
{
	LoanDetailsPtr holdPtr;
	string status;
	char stat;
	string a = "Approved";
	string r = "Rejected";

	displayqueue(*headPtr); /*to print customer details*/

	if (*headPtr != NULL)
	{
		cout << " Enter (A)  to Approve   or  (R) to Reject  Loan. " << endl;
		cin >> stat;

		while ((stat != 'a') && (stat != 'r'))  /*validation check for input*/
		{
			cout << " Please enter a valid  character A or R " << endl;

			cout << "  Loan Status ( A or R )" << endl;
			cin >> stat;
		}//end while

		cout << "Customer Loan ";

		if (stat == 'a' || stat == 'A')
		{
			cout << "Approved " << endl;
			status = a;
		}//end if
		else if (stat == 'r' || stat == 'R')
		{
			cout << "Rejected " << endl;
			status = r;
		}//end else if
		cout << endl << endl;

		(*headPtr)->loanstatus = status;

		/*creates new node*/
		ApproveRejectPtr newPtr;
		newPtr = new approvereject;

		/* copies the customer details to the stack node*/
		if (newPtr != NULL)
		{
			/*passing values from queue to stack*/
			newPtr->customerid = (*headPtr)->customerid;
			newPtr->name = (*headPtr)->name;
			newPtr->address = (*headPtr)->address;
			newPtr->age = (*headPtr)->age;
			newPtr->gender = (*headPtr)->gender;
			newPtr->customernic = (*headPtr)->customernic;
			newPtr->loanamount = (*headPtr)->loanamount;
			newPtr->loanduration = (*headPtr)->loanduration;
			newPtr->loanstatus = (*headPtr)->loanstatus;
			newPtr->loantype = (*headPtr)->loantype;

			newPtr->nextPtr = *topPtr;
			*topPtr = newPtr;

			holdPtr = *headPtr;
			(*headPtr) = (*headPtr)->nextPtr;

			if (*headPtr == NULL)
			{
				*tailPtr = NULL;
			}//end if
			delete(holdPtr); /*deletes the node in holdPtr*/

		} //end if

		else
		{
			cout << " No space available in stack " << endl;
		}//end else

	} // end if 
	returntoMenu();
}/*end approverejectQueue function*/


void printloanstack(ApproveRejectPtr currentPtr)
{
	/*stack is empty*/
	if (currentPtr == NULL)
	{
		cout << "List is Empty.\n" << endl;
	}

	/*stack is not empty*/
	else
	{
		/*currentPtr is not empty*/
		while (currentPtr != NULL)
		{
			cout << "______________________________________\n\n" << endl;
			cout << "Customer ID :-------    " << currentPtr->customerid << "\n" << endl;
			cout << "Customer Name :-------    " << currentPtr->name << "\n" << endl;
			cout << "Customer Loan Status :-------    " << currentPtr->loanstatus << "\n" << endl;
			cout << "Customer Loan Amount :-------    " << currentPtr->loanamount << "\n" << endl;
			cout << "Customer Loan Type :-------    " << currentPtr->loantype << "\n" << endl;
			cout << "\n______________________________________" << endl;
			currentPtr = currentPtr->nextPtr;

		} // end while 

	} // end else

}/*end printloanstack function*/

//option 8
void UpdateMainStat(ApproveRejectPtr *topPtr, CustomerDetailsPtr *startPtr)
{
	CustomerDetailsPtr previousPtr;
	CustomerDetailsPtr currentPtr;
	ApproveRejectPtr holdPtr;
	int x; /*user input*/

	/*prints the customer details in the stack*/
	printloanstack(*topPtr);

	/*stack is not empty*/
	if (*topPtr != NULL)
	{

		cout << " Press 2 to continue or 1 go back to the menu" << endl;
		cin >> x;

		/*according to customer choice*/
		switch (x)
		{
		case 1:
			mainmenu(); /*displays the main menu*/
			break;

		case 2:

			/*to find the customer from the cid in top node in the stack */
			if ((*topPtr)->customerid == (*startPtr)->customerid)
			{
				/*updates loan status in the mainlist*/
				(*startPtr)->loanstatus = (*topPtr)->loanstatus;

				/*temporary holder*/
				holdPtr = *topPtr;
				*topPtr = (*topPtr)->nextPtr;/*assigns the stack's topPtr to the next node*/
				delete(holdPtr);

			}//end if

			else
			{
				previousPtr = *startPtr;
				currentPtr = (*startPtr)->nextPtr;

				/* loop to find the correct location in the list */
				while (currentPtr != NULL && currentPtr->customerid != (*topPtr)->customerid)
				{
					previousPtr = currentPtr; /*walk to...*/
					currentPtr = currentPtr->nextPtr; /*...next node*/
				} // end while

				if (currentPtr != NULL)
				{
					currentPtr->loanstatus = (*topPtr)->loanstatus;
					holdPtr = *topPtr;
					*topPtr = (*topPtr)->nextPtr;
					delete(holdPtr);

					printloanstack(*topPtr);

				} // end if

				/*customer not found*/
				else
				{
					cout << "Customer ID not found" << endl;
					returntoMenu();
				}

			} // end else

			cout << " Succesfully Updated Main List" << endl;
			break;

		} // end switch


	}
	returntoMenu();
}/*end UpdateMainStat function*/

//option 9
void ViewApprovedCustomers(CustomerDetailsPtr currentPtr)
{

	string approve = "Approved";
	string reject = "Rejected";

	/*list is empty*/
	if (currentPtr == NULL)
	{
		cout << "List is empty." << endl;
	}//end if

	/*list is not empty*/
	else
	{
		cout << "      Customer approved list is  -     " << endl << endl;

		/*if customer is in currentPtr*/
		while (currentPtr != NULL)
		{
			cout << "__________________________________________________ " << endl << endl;
			cout << "\nCustomer Name  :  " << currentPtr->name << endl;
			cout << "Customer ID    :  " << currentPtr->customerid << endl;
			cout << "Loan Amount    :  " << currentPtr->loanamount << endl;
			cout << "Loan status   :  " << currentPtr->loanstatus << endl;
			cout << "__________________________________________________ " << endl << endl;

			currentPtr = currentPtr->nextPtr;

			cout << endl;

		} // end while

	} // end else

	returntoMenu();

}/*end ViewApproveCustomers function*/


//option 10
void ViewPendingCustomers(CustomerDetailsPtr currentPtr)
{

	string loanstatus = "Pending";

	/*if list is empty*/
	if (currentPtr == NULL)
	{
		cout << "List is empty." << endl;
	}//end if

	else /*list is not empty*/
	{
		cout << "      Customer pending list is  -     " << endl << endl;

		/*if customer is in currentPtr*/
		while (currentPtr != NULL)
		{
			/**/
			if (currentPtr->loanstatus == "Pending")
			{
				cout << "__________________________________________________ " << endl << endl;
				cout << "\nCustomer Name  :  " << currentPtr->name << endl;
				cout << "Customer ID    :  " << currentPtr->customerid << endl;
				cout << "Loan Amount    :  " << currentPtr->loanamount << endl;
				cout << "__________________________________________________ " << endl << endl;

			}//end if

			currentPtr = currentPtr->nextPtr;

			cout << endl;

		} // end while

	} // end else

	returntoMenu();
}/*end ViewPendingCustomers function*/


//option 11
void ViewRejectedCustomers(CustomerDetailsPtr currentPtr)
{

	string loanstatus = "Rejected";

	/*list is empty*/
	if (currentPtr == NULL)
	{
		cout << "List is empty." << endl;
	}//end if

	else
	{
		cout << "      Customer rejected list is  -     " << endl << endl;

		/*currentPtr is not empty*/
		while (currentPtr != NULL)
		{
			if (currentPtr->loanstatus == "Rejected")
			{
				cout << "__________________________________________________ " << endl << endl;
				cout << "\nCustomer Name  :  " << currentPtr->name << endl;
				cout << "Customer ID    :  " << currentPtr->customerid << endl;
				cout << "Loan Amount    :  " << currentPtr->loanamount << endl;
				cout << "__________________________________________________ " << endl << endl;

			}//end if

			currentPtr = currentPtr->nextPtr;

			cout << endl;

		} // end while

	} // end else

	returntoMenu();
}/*end ViewRejectedCustomers function*/



int main()
{
	welcome();
	mainmenu();

	getchar();
	return 0;
} // end main