//Database Program for Lopez Airlines
//Developers (Project manager) Taher Nurbhai, Abid Gafoor, Joe Hindley, Rehman Qureshi, Ibrahim Ullah

#include <stdio.h>//contains all functions used in this program
#include <stdlib.h>//contains all functions used in this program
#include <string.h>//contain all functions used in this program
#define MAX_AIRPORTS 100//assigns a value of 100 to the variable MAX_AIRPORTS
#define MAX_PLANES 200//assigns a value of 200 to the variable MAX_PLANES
#define MAX_FLIGHTS 1000//assigns a value of 1000 to the variable MAX_FLIGHTS
#define MAX_FLIGHTPATHS 200//assigns a value of 200 to the variable MAX_FLIGHTPATHS
#define MAX_PASSENGERS 1000//assigns a value of 1000 to the variable MAX_PASSENGERS
#define AIRPORTS_FILE "airports.txt"//AIRPORTS_FILE means it is airports.txt
#define PLANES_FILE "planes.txt"//PLANES_FILE means it is planes.txt
#define FLIGHTS_FILE "flights.txt"//FLIGHTS_FILE means it is flights.txt
#define FLIGHTPATHS_FILE "flightpaths.txt"//FLIGHTPATHS_FILE means it is flightpaths.txt
#define PASSENGERS_FILE "passengers.txt"//PASSENGERS_FILE means it is passengers.txt


/* The functions are initialised at the beginning
because some functions need to all upon other functions
Hence, it stops the program from crashing*/

void creating_files();//this function creates all the text files in the folder where the program is present
void read_files();//this function reads all the text files in the folder where the program is present
void print_files();//this prints all the respective parts of the code into the files so we know what each tab stands for

void administrator();/*This function contains the code for the database Administrator
In this function, it calls upon the functions
AddFlight, ViewFlights, EditingFlight, AddFlightPath, AddAirport, AddPlane and structs that are specified below*/
void agent();/*This function contains the code for the Ticket Agent
In this function, it calls upon the functions
SearchFlight, ViewSeating, AddPassenger and structs that are specified below*/
void manager();/*This function contains the code for the Manager
In this function, it calls upon the functions
SearchFlight, ViewSeating, AddPassenger and structs that are specified below*/

void AddFlight();/*This function contains the code for adding new flights onto the database
In this function, it calls upon the functions
ViewFlightPaths, ViewPlanes, ViewFlight and structs that are specified below*/
void AddFlightPath();/*This function contains the code for adding new flight paths onto the database
In this function, it calls upon the functions
ViewAirports, ViewFlightPath and structs that are specified below*/
void AddAirport();/*This function contains the code for adding new airports onto the database
In this function, it calls upon the functions
ViewAirports, ViewAirport and structs that are specified below*/
void AddPlane();/*This function contains the code for adding new planes onto the database
In this function, it calls upon the functions
ViewPlane and structs that are specified below*/
void AddPassenger();/*This function contains the code for adding new passengers onto the database
In this function, it calls upon the functions
ViewPassenger and structs that are specified below*/

void ViewFlight();//This function views one particular flight from the database
void ViewFlights();//This function views all the flights using the ViewFlights function
void ViewAirport();//This function views one particular Airport from the database
void ViewAirports();////This function views all the flights using the ViewAirport function
void ViewPlane();//This function views one particular plane from the database
void ViewPlanes();////This function views all the flights using the ViewPlane function
void ViewFlightPath();//This function views one particular flight path from the database
void ViewFlightPaths();////This function views all the flights using the ViewFlightPath function
void ViewSeating();//This function views the place on the flight the passenger booked or reserved
void ViewPassenger();//This function views one particular passenger from the database

void EditingFlight();/*This function edits the flight path, plane, time, date and price of a particular flight in the database
In this function, it calls upon the functions
ViewFlight, ViewFlightPaths, ViewPlanes and structs that are specified below*/
void SearchFlight();/*This function searches a flight depending on the airport and date of a particular flight in the database
In this function, it calls upon the functions
ViewAirports, ViewFlight and structs that are specified below*/

char* DisplayTime();//This function when printing out in the command window separates the day, month and year from the date.
char* DisplayDate();//This function when printing out in the command window separates the hour and minutes from the date.
char* PlaneType();//This function displays the type of the plane P62 or P124
char SeatType();//This prints reserved or booked on the flight view

FILE *fp;//All the files are being opened here

/*This Structure hold the information of each seat and the passenger that occupies the seat.
The seat status is defined by 0-empty, 1-reserved, 2-booked.*/
struct seating
{
	int passengerID;//Passenger that occupies the seat
	int seat_status;//0 empty, 1 reserved, 2 booked
	char *reservation_expiry_date;//expiry date for the reservation(3 days from the date of purchase)
};

/*This structure holds the information of each flight that the airline has upcoming.
It contains the flight Path, Plane ID, Date, Time, price and each seat information of the flight.*/
struct flight
{
	int flightpathID;//ID is a number so int is used for the flight path as it is being selected  from a list
	int planeID;//ID is a number so int is used for the plane as it is being selected from a list
	char *time;//time is a string so char is used and pointer * is used to copy the characters that are in the date address
	char *date;//time is a string so char is used and pointer * is used to copy the characters that are in the time address
	float price;//price is in terms of decimals so float is used here
	struct seating **Seats;//Here the flight struct is pointing towards the seating struct and assigning it Seats
};

// This structure contains the list of airports the airlines serves
struct airport
{
    char name[50];//Name of the airport is given a max of 51 characters
};

// This structure contain the list of Flight Paths the airline does.
struct flightpath
{
    char flightpath_name[50];//Name of the flight path is given the a max of 51 characters
	int departure_airportID;//ID is a number so int is used for the departure airport as it is being selected from a list
	int arrival_airportID;//ID is a number so int is used for the arrival airport as it is being selected from a list
};

// This structure contain the list of passengers on the flights.
struct passenger
{
	char firstname[40];//The first name for the passenger is given a max of 41 characters
	char secondname[40];//The Second name for the passenger is given a max of 41 characters
	char DOB[5];//The Date of Birth for the passenger is given a max of 6 characters
};

// This is the main function where the files are read and the information is stored into arrays.
// Then the user chooses what section of the program they want to enter. Either data admin, ticket agent,
// or manager.

int main()//This is the main function that joins all the functions together and creates the perfect code
{
    struct airport *Airports[MAX_AIRPORTS];//struct airport is defined here with it pointed to Airports which is defined by how many bytes MAX_AIRPORTS defined by
    int airportsNum = 0;//initialises the integer airportsNum with a value of 0
    int *Planes[MAX_PLANES];//0 = P62, 1 = P124 //struct Planes is defined here with it pointed to Planes which is defined by how many bytes MAX_PLANES defined by
    int planesNum = 0;//initialises the integer planesNum with a value of 0
    struct flight *Flights[MAX_FLIGHTS];//struct flight is defined here with it pointed to Flights which is defined by how many bytes MAX_FLIGHTS defined by
    int flightsNum = 0;//initialises the integer flightsNum with a value of 0
    struct flightpath *Flightpaths[MAX_FLIGHTPATHS];//struct flightpath is defined here with it pointed to FlightPaths which is defined by how many bytes MAX_FLIGHTPATHS defined by
    int flightpathsNum = 0;//initialises the integer flightpathsNum with a value of 0
    struct passenger *Passengers[MAX_PASSENGERS];//struct passenger is defined here with it pointed to Passengers which is defined by how many bytes MAX_PASSENGERS defined by
    int passengersNum = 0;//initialises the integer passengersNum with a value of 0
    char open_files;

    printf("\n\t\t\t****Lopez Airlines****\n");
    printf("Are the files to store the database already created?\n");
    printf("Y-Yes\nN-No\n");
    scanf(" %c", &open_files);
    fflush(stdin);
    open_files = toupper(open_files);
    if(open_files == 'N')
	{
    	creating_files();
	}

    read_files(Airports, &airportsNum, Planes, &planesNum, Flights, &flightsNum, Flightpaths, &flightpathsNum, Passengers, &passengersNum);//read files in the read file function

    char Operation; //declaring a character called Operation
    system("cls");
    do//Loop that first does what's shown below and then looks at the condition in the while function
    {
        printf("\n\t\t\t****Lopez Airlines****\n");
        printf("\nPlease select an operation:\n'D' for Database Administrator\n'T' for Ticket Agent\n'M' for Manager\n'E' for Exit\n");
        scanf("%c", &Operation);//Input for operation
        Operation = toupper(Operation);//Function to change small letters to capitals all the time
        fflush(stdin);//stops buffering
        system("cls");//Clears the command window for the next stage
        printf("\n\t\t\t****Lopez Airlines****\n");

        while(Operation != 'D' && Operation != 'T' && Operation != 'M' && Operation != 'E')//If D, T, M or E is not chosen
        {
            //Repeats the steps
            printf("\nInvalid Letter! Please try again");
            printf("\nPlease select operation:\n'D' for database administrator\n'T' for ticket Agent\n'M' for Manager\n'E' for Exit\n");
            scanf("%c", &Operation);
            Operation = toupper(Operation);
            fflush(stdin);//clears buffer
            system("cls");
            printf("\n\t\t\t****Lopez Airlines****\n");
        }

        switch(Operation)//If D, T, M or E is selected
        {
            case 'D' :
                administrator(Airports, &airportsNum, Planes, &planesNum, Flights, &flightsNum, Flightpaths, &flightpathsNum);//calls upon administrator function
                break;
            case 'T' :
                agent(Airports, &airportsNum, Planes, &planesNum, Flights, &flightsNum, Flightpaths, &flightpathsNum, Passengers, &passengersNum);//calls upon agent function
                break;
            case 'M' :
                manager(Planes, &planesNum, Flights, &flightsNum, Flightpaths, Airports);//calls upon manager function
                break;
            case 'E' : //Exits the program
                break;
            default:
                break;
        }
    }
    while (Operation != 'E');//The condition if its not equal to E which can never be the case

    print_files(Airports, &airportsNum, Planes, &planesNum, Flights, &flightsNum, Flightpaths, &flightpathsNum, Passengers, &passengersNum);//prints the files and the texts inside them

    return 0;//Returns a value
}

//This function creates the files for the database to be stored in.
void creating_files()
{
	fp = fopen(AIRPORTS_FILE, "w");
	fprintf(fp, "%i\n", 0);
	fclose(fp);

	fp=fopen(PLANES_FILE, "w");
	fprintf(fp, "%i\n", 0);
	fclose(fp);

	fp=fopen(FLIGHTS_FILE, "w");
	fprintf(fp, "%i\n", 0);
	fclose(fp);

	fp=fopen(FLIGHTPATHS_FILE, "w");
	fprintf(fp, "%i\n", 0);
	fclose(fp);

	fp=fopen(PASSENGERS_FILE, "w");
	fprintf(fp, "%i\n", 0);
	fclose(fp);

}

/*This function reads the files that contain information and
then assign it to the relevant structures arrays.*/
void read_files(struct airport **Airports, int *airportsNum, int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int *flightpathsNum, struct passenger **Passengers, int *passengersNum)
{
    int c;//declares an int called c
    if((fp=fopen(AIRPORTS_FILE, "rb")))//Reads the airport file and then transfers all the information from the file to the airport structure.
    {
      fscanf(fp, "%i\n", airportsNum);//Read the number at the top of the file, this tell the program the number of airports there are.
      c=0; //initialises the int c with the value of 0
      while((!feof(fp))&&(c<*airportsNum))//the function reads until end of file and if c value is less than the number at the top of the file
        {
            Airports[c] = malloc(sizeof(struct airport));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            fscanf(fp, "%s\n", Airports[c]->name);//reads whats in the file
            //printf("%s\n", Airports[c]->name);//Debugging
          c++;//increments until c is equal to what number is at the top of the file
                  }
      fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",AIRPORTS_FILE);	// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(PLANES_FILE, "rb")))// Reads the planes file and then transfers all the information from the file to the planes structure.
    {
      fscanf(fp, "%i\n", planesNum);// Read the number at the top of the file, this tell the program the number of planes there are.
      c=0;//initialises the int c with the value of 0
      while((!feof(fp))&&(c<*planesNum))//the function reads until end of file and if c value is less than the number at the top of the file
        {
            Planes[c] = malloc(sizeof(int));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            fscanf(fp, "%i\n", &Planes[c]);//reads what's in the file
            //printf("%i\n", Planes[c]);//Debugging
          c++;//increments until c is equal to what number is at the top of the file
        }
      fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",PLANES_FILE); // Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(FLIGHTS_FILE, "rb")))// Reads the flights file and then transfers all the information from the file to the flights structure.
    {
      fscanf(fp, "%i\n", flightsNum);// Read the number at the top of the file, this tell the program the number of flights there are.
      c=0;//initialises the int c with the value of 0
      int x;//declares an int called x
      int y;//declares an int called y
      while((!feof(fp))&&(c<*flightsNum))//the function reads until end of file and if c value is less than the number at the top of the file
        {
            Flights[c] = malloc(sizeof(struct flight));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            Flights[c]->date = malloc(sizeof(char)*6);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            Flights[c]->time = malloc(sizeof(char)*4);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            Flights[c]->Seats = (struct seating **)malloc(sizeof(struct seating *) * 12);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            fscanf(fp, "%i\t%i\t%s\t%s\t%f", &Flights[c]->flightpathID, &Flights[c]->planeID, Flights[c]->date, Flights[c]->time, &Flights[c]->price);//reads what's in the file
           // printf("%i\t%i\t%s\t%s\t%f", Flights[c]->flightpathID, Flights[c]->planeID, Flights[c]->date, Flights[c]->time, Flights[c]->price);//Debugging
            for (x=0; x<12; x++)//for loop where x starts with 0 and increments until it reaches 0
            {
                Flights[c]->Seats[x] = (struct seating *)malloc(sizeof(struct seating) * 4);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
                for (y=0; y<4; y++)//for loop where y starts with 0 and increments until it reaches 0
                {
                    Flights[c]->Seats[x][y].reservation_expiry_date = malloc(sizeof(char)*6);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
                    fscanf(fp, "\t%i\t%i\t%s", &Flights[c]->Seats[x][y].passengerID, &Flights[c]->Seats[x][y].seat_status, Flights[c]->Seats[x][y].reservation_expiry_date);
                    //printf("\t%i\t%i\t%s", Flights[c]->Seats[x][y].passengerID, Flights[c]->Seats[x][y].seat_status, Flights[c]->Seats[x][y].reservation_expiry_date);//Debugging
                }
            }
            fscanf(fp, "\n");//looks for a new line in the file
            //printf("\n");//Debugging
            c++;//increments until c is equal to what number is at the top of the file
        }
      fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",FLIGHTS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(FLIGHTPATHS_FILE, "rb"))) // Reads the flight path file and then transfers all the information from the file to the flight path structure.
    {
      fscanf(fp, "%i\n", flightpathsNum);// Read the number at the top of the file, this tell the program the number of flight path there are.
      c=0;//initialises the int c with the value of 0
      while((!feof(fp))&&(c<*flightpathsNum))//the function reads until end of file and if c value is less than the number at the top of the file
        {
            Flightpaths[c] = malloc(sizeof(struct flightpath));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            fscanf(fp, "%s\t%i\t%i\n", Flightpaths[c]->flightpath_name, &Flightpaths[c]->departure_airportID, &Flightpaths[c]->arrival_airportID);//reads what's in the file
            //printf("%s\t%i\t%i\n", Flightpaths[c]->flightpath_name, Flightpaths[c]->departure_airportID, Flightpaths[c]->arrival_airportID);//Debugging
            c++;//increments until c is equal to what number is at the top of the file
        }
      fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",FLIGHTPATHS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(PASSENGERS_FILE, "rb")))// Reads the passenger file and then transfers all the information from the file to the passenger structure.
    {
      fscanf(fp, "%i\n", passengersNum);// Read the number at the top of the file, this tell the program the number of passenger there are.
      c=0;//initialises the int c with the value of 0
      while((!feof(fp))&&(c<*passengersNum))//the function reads until end of file and if c value is less than the number at the top of the file
        {
            Passengers[c] = malloc(sizeof(struct passenger));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            fscanf(fp, "%s\t%s\t%s\n", Passengers[c]->firstname, Passengers[c]->secondname, Passengers[c]->DOB);//reads what's in the file
            //printf("%s\t%s\t%s\n", Passengers[c]->firstname, Passengers[c]->secondname, Passengers[c]->DOB);//debugging
            c++;//increments until c is equal to what number is at the top of the file
        }
      fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",PASSENGERS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }
}

// This function prints the structures into there respective files.
void print_files(struct airport **Airports, int *airportsNum, int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int *flightpathsNum, struct passenger **Passengers, int *passengersNum)
{
    //printf("Printing\n");
    int c;
    if((fp=fopen(AIRPORTS_FILE, "w")))// Writes the airport structure array into the airport file.
    {
        //printf("%i\n", *airportsNum);
        fprintf(fp, "%i\n", *airportsNum);// Prints the number of airports are going to be saved into the file.
        for(c=0; c<*airportsNum; c++)
        {
            //printf("%s\n", Airports[c]->name);//debugging
            fprintf(fp, "%s\n", Airports[c]->name);// Prints airport names in file
        }
        fclose(fp);//closes file
    }
    else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",AIRPORTS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(PLANES_FILE, "w")))// Writes the planes structure array into the planes file.
    {
        //printf("%i\n", *planesNum);//debugging
        fprintf(fp, "%i\n", *planesNum);// Prints the number of planes are going to be saved into the file.
        for(c=0; c<*planesNum; c++)
        {
            //printf("%i\n", Planes[c]);//debugging
            fprintf(fp, "%i\n", Planes[c]);// Prints planes names in file
        }
        fclose(fp);//closes file
    }
    else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",PLANES_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(FLIGHTS_FILE, "w")))// Writes the flights structure array into the flights file.
    {
        int x;
        int y;
        //printf("%i\n", *flightsNum);//debugging
        fprintf(fp, "%i\n", *flightsNum);// Prints the number of flights are going to be saved into the file.
        for(c=0; c<*flightsNum; c++)
        {
            //printf("%i\t%i\t%s\t%s\t%f\n", Flights[c]->flightpathID, Flights[c]->planeID, Flights[c]->date, Flights[c]->time, Flights[c]->price);//debugging
            fprintf(fp, "%i\t%i\t%s\t%s\t%f", Flights[c]->flightpathID, Flights[c]->planeID, Flights[c]->date, Flights[c]->time, Flights[c]->price);
            for (x=0; x<12; x++)
            {
                for (y=0; y<4; y++)
                {
                    //printf("\t%i\t%i\t%s", Flights[c]->Seats[x][y].passengerID, Flights[c]->Seats[x][y].seat_status, Flights[c]->Seats[x][y].reservation_expiry_date);//debugging
                    fprintf(fp, "\t%i\t%i\t%s", Flights[c]->Seats[x][y].passengerID, Flights[c]->Seats[x][y].seat_status, Flights[c]->Seats[x][y].reservation_expiry_date);
                }
            }
            fprintf(fp, "\n");//prints a new line in the file
        }
        fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",FLIGHTS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(FLIGHTPATHS_FILE, "w")))// Writes the flight paths structure array into the flight paths file.
    {
        int x;//creates an integer int x
        int y;//creates an integer int y
        //printf("%i\n", *flightpathsNum);//debugging
        fprintf(fp, "%i\n", *flightpathsNum);// Prints the number of flight paths are going to be saved into the file.
        for(c=0; c<*flightpathsNum; c++)
        {	// Prints flight paths into file
            //printf("%s\t%i\t%i\n", Flightpaths[c]->flightpath_name, Flightpaths[c]->departure_airportID, Flightpaths[c]->arrival_airportID);//debugging
            fprintf(fp, "%s\t%i\t%i\n", Flightpaths[c]->flightpath_name, Flightpaths[c]->departure_airportID, Flightpaths[c]->arrival_airportID);
        }
        fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",FLIGHTPATHS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

    if((fp=fopen(PASSENGERS_FILE, "w")))// Writes the passengers structure array into the passengers file.
    {
        int x;
        int y;
        //printf("%i\n", *passengersNum);//debugging
        fprintf(fp, "%i\n", *passengersNum);// Prints the number of passengers are going to be saved into the file.
        for(c=0; c<*passengersNum; c++)
        {	// Prints passenger information into file
            //printf("%s\t%s\t%s\n", Passengers[c]->firstname, Passengers[c]->secondname, Passengers[c]->DOB);//debugging
            fprintf(fp, "%s\t%s\t%s\n", Passengers[c]->firstname, Passengers[c]->secondname, Passengers[c]->DOB);
        }
        fclose(fp);//closes file
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",PASSENGERS_FILE);// Exit program if file doesn't open.
      exit(-1);
    }

}

// This function is the database administrator part of the program.
// In this function the database admin can add new flights, view current flights,
// edit flights, add new flight paths, add new airports and add new planes.
void administrator(struct airport **Airports, int *airportsNum, int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int *flightpathsNum)
{
	char NORE;

	do
	{
	printf("\nWhat do you want to do?\n");// Asks the administrator what they want to do.
	printf("\n1 - Create new flight \n2 - View flights \n3 - Edit existing flight (View flights first to get the flight ID) \n4 - Add new flight path \n5 - Add new airport \n6 - Add new plane\n7 - Exit\n");
	scanf("%c", &NORE);//Inputs the number by the user
	fflush(stdin);//clears buffer

		switch(NORE)// Depending on the previous input the switch statements starts the relevant function.
		{
			case '1' :
				AddFlight(Airports, airportsNum, Planes, planesNum, Flights, flightsNum, Flightpaths, flightpathsNum); //calls upon AddFlight function
				break;
			case '2' :
			    ViewFlights(Airports, Planes, Flights, flightsNum, Flightpaths);//calls upon ViewFlights function
				break;
			case '3' :
			    EditingFlight(Airports, airportsNum, Planes, planesNum, Flights, flightsNum, Flightpaths, flightpathsNum);//calls upon EditingFlight function
				break;
            case '4' :
				AddFlightPath(Airports, airportsNum, Flightpaths, flightpathsNum);//calls upon AddFlightPath function
				break;
            case '5' :
				AddAirport(Airports, airportsNum);//calls upon AddAirport function
				break;
            case '6' :
				AddPlane(Planes, planesNum);//calls upon AddPlane function
				break;
            case '7' :
                break;
			default :
			    system("cls");//clears screen in the programe
				printf("\nInvalid Letter! Please try again\n");
		}
	}while(NORE != '7');

}

/* This function is the travel agent's section in the program.
In this function the travel agent can search for specific
depending on either the departure airport, arrival airport
or the date. The travel agent can also view the seat arrangements
on the flights and book a seat.
When booking a seat the passengers information is in-putted.*/
void agent(struct airport **Airports, int *airportsNum, int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int *flightpathsNum, struct passenger **Passengers, int *passengersNum)
{
    int choice;//declares an int choice
    int flightID;//declares an int flightID
    int x, y, c;//declares 3 ints x, y, c
    int BorR;//declares an BorR choice
    char reservationExpiry[10];//declares a string reservationExpiry which has a max of 10 characters
    char first;//declares a character first
    char second;//declares a character second

	do
	{
        printf("\nWhat do you want to search by?\n");// Ask the ticket agent how they want to search for the flight
        printf("\n1 - Departure airport \n2 - Arrival airport \n3 - Date \n4 - Exit\n");
        scanf("%i", &choice);//user inputs the relevant number
        fflush(stdin);//clears buffer
        if (choice != 4)//if its 4 it exits the programme
        {
            SearchFlight(Airports, airportsNum, Planes, Flights, flightsNum, Flightpaths, choice);// Passes data to search flight function, and displays availble flights.

            printf("\nChoose which flight you want\n"); // Asks ticket agent to choose from displayed flights.
            scanf("%i", &flightID);//user inputs the relevant number
            fflush(stdin);//clears buffer
            flightID -= 1;

            ViewSeating(Flights, Planes, flightID);// Passes data to view seating function, and displays availble seats.

            printf("\nWhich seat do you want to book?");// Asks ticket agent to choose from displayed seats.
            printf("\nPlease enter your x co-ordinate:\n");
            scanf("%i", &x);// Inputs x and y coordinates of desired seats.
            fflush(stdin);//clears buffer
            x--;//decrements

            printf("\nPlease enter your y co-ordinate:\n");
            scanf("%i", &y);
            fflush(stdin);//clears buffer
            y--;//decrements

            printf("Do you want to:\n1: Reserve a seat (reservations last 3 days) \n2: Book a ticket\n");
            scanf("%i", &BorR);	// Asks ticket agents whether they want to reserve or book the saet.
            fflush(stdin);//clears buffer

            if (BorR == 1)// If they have chosen reservation they have to input a date.
            {
                printf("\nPlease enter the date 3 days from now in terms of ddmmyy:\n");
                printf("dd stands for the day - example 01, 02, 03...,31.\n");
                printf("mm stands for the month - example 01, 02, 03...,12.\n");
                printf("yy stands for the year - example 01, 02, 03...\n");
                scanf("%6s", &reservationExpiry);//inputs the date
                fflush(stdin);//clears buffer
            }

            printf("\nPlease enter the initials of the customer to search. Type 0 for a new passenger for first and second initial\n");// Program asks the ticket to input the intials of the passenger.
            printf("First initial:");
            scanf("%c", &first);//inputs first name
            first = toupper(first);//changes every single letter that is inputted to a capital
            fflush(stdin);//clears buffer
            printf("Second initial:");
            scanf("%c", &second);//inputs second name
            second = toupper(second);//changes every single letter that is inputted to a capital
            fflush(stdin);//clears buffer

            printf("\n");//prints a line
            for (c=0; c<*passengersNum; c++)// Searches passengers and displays all the passengers with those initails.
            {
                if (Passengers[c]->firstname[0] == first && Passengers[c]->secondname[0] == second)//if the initials are found then displays the passsengers
                {
                    ViewPassenger(Passengers, c);
                }
            }
            printf("Which passenger? Type 0 to add a new passenger\n");	// Asks the ticket agent to choose the correct passenger
            scanf("%i", &c);	                                        // or to add a passenger
            fflush(stdin);//clears buffer
            c--;

            if (c == -1)//when C becomes less than 0
            {
                AddPassenger(Passengers, passengersNum);//Calls upon the function AddPassenger
                c = (*passengersNum)-1;
            }

            if (BorR == 1)// Saves reservation date.
            {
                strcpy(Flights[flightID]->Seats[y][x].reservation_expiry_date, reservationExpiry);//adds the relevant letter to the grid
            }
            Flights[flightID]->Seats[y][x].seat_status = BorR;
            Flights[flightID]->Seats[y][x].passengerID = c;

            ViewSeating(Flights, Planes, flightID);
        }
	}while(choice != 4);

}

/*This function is the manager part of the program.
The manager is able to retrieve statistics about the company.
He can retrieve the number of planes of a certain type in the fleet or the total passengers
in certain flights and finally the revenue the company has been making*/
void manager(int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, struct airport **Airports)
{
    int P62 = 0;//initialises int P62 to 0
    int P124 = 0;//initialises int P124 to 0
    int c, x, y, seatsFilled;//declares characters c, x, y, seatsFilled
    float revenueTotal = 0;//initialises float revenueTotal to 0
    system("cls");
	printf("\n\t\t\t****Lopez Airlines****\n");


	for (c=0; c<*planesNum; c++)
    {
        if (Planes[c] == 0)//only if Planes = 0 as P62 is 0
        {
            P62 ++;//increments
        }
        else
        {
            P124 ++;//increments
        }
    }

    printf("\nThere are %i P62 planes in our fleet.\n", P62);
    printf("There are %i P124 planes in our fleet.\n", P124);

    for (c=0; c<*flightsNum; c++)
    {
        seatsFilled = 0;//reinitialises to 0
        for (x=0; x<12; x++)
        {
            for (y=0; y<4; y++)
            {
                if (Flights[c]->Seats[x][y].seat_status == 2)
                {
                    seatsFilled++;
                }
            }
        }

        printf("\nFlight ID: %i\nDate: %s\nTime: %s\nFlight path: %s to %s\nCost: %.2f\nSeats occupied: %i\nRevenue Generated: %.2f\n", c+1, DisplayDate(Flights[c]->date), DisplayTime(Flights[c]->time), Airports[Flightpaths[Flights[c]->flightpathID]->departure_airportID]->name, Airports[Flightpaths[Flights[c]->flightpathID]->arrival_airportID]->name, Flights[c]->price, seatsFilled, Flights[c]->price * seatsFilled);
        revenueTotal += Flights[c]->price * seatsFilled;//adds the revenue total on itself so a final revenue total can be reached
    }
    printf("\nRevenue total for all flights is %.2f\n", revenueTotal);//prints out the total revenue to 2 dp
}

// This function allows the database admin to add new flights
void AddFlight(struct airport **Airports, int *airportsNum, int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int *flightpathsNum)
{
    char date_input[10];//declares a string date_input with a max of 10 characters
    char time_input[10];//declares a string time_input with a max of 10 characters
    int flightpathID_input;//declares an int flightpathID_input;
    int planeID_input;//declares an int planeID_input
    float price_input;//declares an int price_input

    system("cls");//clears the screen
	printf("\n\t\t\t****Lopez Airlines****\n");

    printf("\nHere are the available flight paths:\n");	// shows avaiblible flight paths
    ViewFlightPaths(Airports, airportsNum, Flightpaths, flightpathsNum);
    printf("\nChoose a flight path\n");	// Asks administrator to choose a flight path
    scanf("%i", &flightpathID_input);//inputs the relevant ID
    fflush(stdin);//clears buffer
    flightpathID_input -= 1;


    printf("\nHere are the available planes:\n");// Shows availible planes
    ViewPlanes(Planes, planesNum);
    printf("\nChoose a plane\n");// Asks administrator to choose a plane
    scanf("%i", &planeID_input);
    fflush(stdin);//clears buffer
    planeID_input -= 1;


    printf("\nPlease type in the price of the flight:\n");// Asks administrator to choose a price for the flight
	scanf("%f", &price_input);
	fflush(stdin);//clears buffer


    printf("\nPlease type in the date of the flight in terms of ddmmyy:\n");// Asks the administrator to input the date of the flight
	printf("dd stands for the day - example 01, 02, 03...,31.\n");
	printf("mm stands for the month - example 01, 02, 03...,12.\n");
	printf("yy stands for the year - example 01, 02, 03...\n");
	scanf("%6s", &date_input);//inputs the date
	fflush(stdin);//clears buffer


	printf("\nPlease type in the time of the flight in terms of hhmm:\n");// Asks the administrator to input the time of the flight
	printf("hh stands for the hours - example 01, 02, 03...,24.\n");
	printf("mm stands for the minutes - example 01, 02, 03...,59.\n");
	scanf("%4s", &time_input);
	fflush(stdin);//clears buffer

    //everything is being saved onto the strcuture
    int x, y;
	Flights[*flightsNum] = malloc(sizeof(struct flight));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    Flights[*flightsNum]->date = malloc(sizeof(char)*6);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    Flights[*flightsNum]->time = malloc(sizeof(char)*4);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    strcpy(Flights[*flightsNum]->date, date_input);	//strcpy copies the text in that address and gives it a value that the user inputs
    strcpy(Flights[*flightsNum]->time, time_input);//strcpy copies the text in that address and gives it a value that the user inputs
    Flights[*flightsNum]->flightpathID = flightpathID_input;//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    Flights[*flightsNum]->planeID = planeID_input;//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    Flights[*flightsNum]->price = price_input;//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    Flights[*flightsNum]->Seats = (struct seating **)malloc(sizeof(struct seating *) * 12);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    for (x=0; x<12; x++)// seat information being saved into the seat structure
    {
        Flights[*flightsNum]->Seats[x] = (struct seating *)malloc(sizeof(struct seating) * 4);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
        for (y=0; y<4; y++)
        {
            Flights[*flightsNum]->Seats[x][y].reservation_expiry_date = malloc(sizeof(char)*6);//memory size is reserved and is pointed to the address of the first byte of the block that is returned
            Flights[*flightsNum]->Seats[x][y].passengerID = 0;//initialises to 0
            Flights[*flightsNum]->Seats[x][y].seat_status = 0;//initialises to 0
            strcpy(Flights[*flightsNum]->Seats[x][y].reservation_expiry_date, "000000");//gives value of 000000
        }
    }

    system("cls");//clears screen
    ViewFlight(Airports, Planes, Flights, Flightpaths, *flightsNum);// View the flight information
    (*flightsNum)++;//increments pointer
}

// This function allows the database admin to add new flight paths.
void AddFlightPath(struct airport **Airports, int *airportsNum, struct flightpath **Flightpaths, int *flightpathsNum)
{
    char flightPathName_input[50];//declares a string called flightPathName_input that has a max characters of 51
    int departureAirportID_input;//declares an int departureAirportID_input
    int arrivalAirportID_input;//declares an int arrivalAirportID_input

    system("cls");//clears screen
    printf("\n\t\t\t****Lopez Airlines****\n");

    printf("\nHere are the available flight paths:\n");	// shows avaiblible flight paths
    ViewFlightPaths(Airports, airportsNum, Flightpaths, flightpathsNum);//calls upon function ViewFlightPaths

    printf("\nEnter a name for your new flight path e.g Heathrow2Dubai:");
    scanf("%50s", &flightPathName_input); //inputs flight path name
    fflush(stdin);//clears buffer

    printf("\nHere are the available airports:\n");
    ViewAirports(Airports, airportsNum);//calls upon function ViewAirports

    printf("\nChoose your departure airport:\n");
    scanf("%i", &departureAirportID_input);//inputs departure Airport number
    fflush(stdin);//clears buffer
    departureAirportID_input -= 1;

    printf("\nChoose your arrival airport:\n");
    scanf("%i", &arrivalAirportID_input);//inputs Arrival Airport number
    fflush(stdin);//clears buffer
    arrivalAirportID_input -= 1;

    Flightpaths[*flightpathsNum] = malloc(sizeof(struct flightpath));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    strcpy(Flightpaths[*flightpathsNum]->flightpath_name, flightPathName_input);//strinf copy and asssigning value
    Flightpaths[*flightpathsNum]->departure_airportID = departureAirportID_input;//assigning value
    Flightpaths[*flightpathsNum]->arrival_airportID = arrivalAirportID_input;//assigning value

    ViewFlightPath(Airports, Flightpaths, *flightpathsNum);//calls upon function ViewFlightPath
    (*flightpathsNum) ++;
}

// This function allows the database admin to add new airports.
void AddAirport(struct airport **Airports, int *airportsNum)
{
    char airportName_input[50];//declares a string with a max of 51 characters

    system("cls");//clears screen
    printf("\n\t\t\t****Lopez Airlines****\n");

    printf("\nHere are the available airports:\n");
    ViewAirports(Airports, airportsNum);//calls upon function ViewAirports

    printf("\nEnter a name for your new airport:");
    scanf("%50s", &airportName_input);//inputs Airport Name
    fflush(stdin);//clears buffer

    Airports[*airportsNum] = malloc(sizeof(struct airport));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    strcpy(Airports[*airportsNum]->name, airportName_input);//string copy assigning value

    ViewAirport(Airports, *airportsNum);//calls upon function ViewAirport
    (*airportsNum) ++;//increments pointer
}

// This function allows the database admin to add new planes.
void AddPlane(int **Planes, int *planesNum)
{
    int planeType_input;//declares an int planeType_input

    system("cls");//clears screen
    printf("\n\t\t\t****Lopez Airlines****\n");

    printf("\nHere are the current planes:\n");
    ViewPlanes(Planes, planesNum);//calls upon function ViewPlanes

    printf("\nWhich type of plane are you adding?:\n1: P62 \n2: P124\n");
    scanf("%i", &planeType_input);//inputs the ID
    fflush(stdin);//clears buffer
    planeType_input -= 1;
    Planes[*planesNum] = malloc(sizeof(int));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
    Planes[*planesNum] = planeType_input;//assigning value

    ViewPlane(Planes, *planesNum);//calls upon function ViewPlane
    (*planesNum) ++;
}

/*This function is used for adding passengers information to certain flights.
The DOB, First name and last name is asked and then saved to the passenger structure.*/
void AddPassenger(struct passenger **Passengers, int *passengersNum)
{
    char DOB_input[5];//declares a string with max of 6 characters
    char secondname_input[40];//declares a string with max of 41 characters
    char firstname_input[40];//declares a string with max of 41 characters

    system("cls");
    printf("\n\t\t\t****Lopez Airlines****\n");

    printf("\n|New Passenger|\n");	//Input First name of passenger
    printf("\nEnter the first name of your passenger:");
    scanf("%50s", &firstname_input);//inputs first name
    fflush(stdin);//clears buffer

    printf("\nEnter the surname of your passenger:");//Input Surname of passenger
    scanf("%50s", &secondname_input);//inputs second name
    fflush(stdin);//clears buffer

    printf("\nEnter the date of birth of your passenger in terms of ddmmyy:");// Input DOB of passenger
    printf("\ndd stands for the day - example 01, 02, 03...,31.\n");
    printf("mm stands for the month - example 01, 02, 03...,12.\n");
    printf("yy stands for the year - example 01, 02, 03...\n");
    scanf("%6s", &DOB_input);//inputs date of birth
    fflush(stdin);//clears buffer


    Passengers[*passengersNum] = malloc(sizeof(struct passenger));// Saves this information into the passenger structure////memory size is reserved and is pointed to the address of the first byte of the block that is returned
    strcpy(Passengers[*passengersNum]->firstname, firstname_input);//string copy assigning value
    strcpy(Passengers[*passengersNum]->secondname, secondname_input);//string copy assigning value
    strcpy(Passengers[*passengersNum]->DOB, DOB_input);//string copy assigning value

    ViewPassenger(Passengers, *passengersNum);//calls upon function ViewPassenger
    (*passengersNum) ++;//increments
}

// This function allows the database admin to view flights in conjunction with another function.
void ViewFlight(struct airport **Airports, int **Planes, struct flight *Flights[], struct flightpath **Flightpaths, int input)
{
    printf("\nFlight ID: %i\nDate: %s\nTime: %s\nFlight path: %s to %s\nPlane ID: %i(%s)\nCost: %.2f\n", input+1, DisplayDate(Flights[input]->date), DisplayTime(Flights[input]->time), Airports[Flightpaths[Flights[input]->flightpathID]->departure_airportID]->name, Airports[Flightpaths[Flights[input]->flightpathID]->arrival_airportID]->name, Flights[input]->planeID+1, PlaneType(Planes[Flights[input]->planeID]), Flights[input]->price);
}

// This function allows the database admin to view flights in conjunction with another function.
void ViewFlights(struct airport **Airports, int **Planes, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths)
{
    system("cls");//clears screen
	printf("\n\t\t\t****Lopez Airlines****\n");
	printf("\nAll flights in the database:\n");
	int c;
	for (c=0; c<*flightsNum; c++)//if condition works increments and view flights
    {
        ViewFlight(Airports, Planes, Flights, Flightpaths, c);//cals upon the function viewFlight
    }
}

// This function allows the database admin to view airports in conjunction with another function.
void ViewAirport(struct airport **Airports, int input)
{
    printf("%i: %s\n", input+1, Airports[input]->name);//prints the releavant airport
}

// This function allows the database admin to view airports in conjunction with another function.
void ViewAirports(struct airport **Airports, int *airportsNum)
{
    int c;//declares an int c
    printf("\n");
	for (c=0; c<*airportsNum; c++)//if condition works increments and view airports
    {
        ViewAirport(Airports, c);
    }
}

// This function allows the database admin to view planes in conjunction with another function.
void ViewPlane(int **Planes, int input)
{
    printf("%i: type %s\n", input+1, PlaneType(Planes[input]));//prints 1 particular plane
}

// This function allows the database admin to view planes in conjunction with another function.
void ViewPlanes(int **Planes, int *planesNum)
{
    int c; //declares an int c
    printf("\n");
    for (c=0; c<*planesNum; c++)//if condition works increments and view planes
    {
        ViewPlane(Planes, c);
    }
}

// This function allows the database admin to view flight paths in conjunction with another function.
void ViewFlightPath(struct airport **Airports, struct flightpath **Flightpaths, int input)
{
    printf("%i: %s - %s to %s\n", input+1, Flightpaths[input]->flightpath_name, Airports[Flightpaths[input]->departure_airportID]->name, Airports[Flightpaths[input]->arrival_airportID]->name);
}

// This function allows the database admin to view flight paths in conjunction with another function.
void ViewFlightPaths(struct airport **Airports, int *airportsNum, struct flightpath **Flightpaths, int *flightpathsNum)
{
    int c;//declares an int c
    printf("\n");
    for (c=0; c<*flightpathsNum; c++)//if condition works increments and view flight paths
    {
        ViewFlightPath(Airports, Flightpaths, c);
    }
}

/*This function is used by the ticket agent when booking a seat.
By showing a grid of the seat layout for the flight and
displaying the occupied seat.*/
void ViewSeating(struct flight *Flights[], int **Planes, int input) //the function that is used to display the grid
{
    if (Planes[Flights[input]->planeID] == 0) // This displays the seating arrangments for the p62 plane, displays each seat status.
    {

            printf("\n");
            printf("     1   2   \n");
            printf("   |---|---|\n");
            printf("  1| %c | %c |\n", SeatType(Flights[input]->Seats[0][0].seat_status), SeatType(Flights[input]->Seats[0][1].seat_status));
            printf("   |---|---|\n");
            printf("  2| %c | %c |\n", SeatType(Flights[input]->Seats[1][0].seat_status), SeatType(Flights[input]->Seats[1][1].seat_status));
            printf("   |---|---|\n");
            printf("  3| %c | %c |\n", SeatType(Flights[input]->Seats[2][0].seat_status), SeatType(Flights[input]->Seats[2][1].seat_status));
            printf("   |---|---|\n");
            printf("  4| %c | %c |\n", SeatType(Flights[input]->Seats[3][0].seat_status), SeatType(Flights[input]->Seats[3][1].seat_status));
            printf("   |---|---|\n");
            printf("  5| %c | %c |\n", SeatType(Flights[input]->Seats[4][0].seat_status), SeatType(Flights[input]->Seats[4][1].seat_status));
            printf("   |---|---|\n");
            printf("  6| %c | %c |\n", SeatType(Flights[input]->Seats[5][0].seat_status), SeatType(Flights[input]->Seats[5][1].seat_status));
            printf("   |---|---|\n");
            printf("\n");
    }
    else
    {
        printf("\n");// This displays the seating arrangments for the p124 plane, displays each seat status.
        printf("     1   2   3   4 \n");
        printf("   |---|---|---|---|\n");
        printf("  1| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[0][0].seat_status), SeatType(Flights[input]->Seats[0][1].seat_status), SeatType(Flights[input]->Seats[0][2].seat_status), SeatType(Flights[input]->Seats[0][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  2| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[1][0].seat_status), SeatType(Flights[input]->Seats[1][1].seat_status), SeatType(Flights[input]->Seats[1][2].seat_status), SeatType(Flights[input]->Seats[1][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  3| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[2][0].seat_status), SeatType(Flights[input]->Seats[2][1].seat_status), SeatType(Flights[input]->Seats[2][2].seat_status), SeatType(Flights[input]->Seats[2][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  4| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[3][0].seat_status), SeatType(Flights[input]->Seats[3][1].seat_status), SeatType(Flights[input]->Seats[3][2].seat_status), SeatType(Flights[input]->Seats[3][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  5| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[4][0].seat_status), SeatType(Flights[input]->Seats[4][1].seat_status), SeatType(Flights[input]->Seats[4][2].seat_status), SeatType(Flights[input]->Seats[4][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  6| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[5][0].seat_status), SeatType(Flights[input]->Seats[5][1].seat_status), SeatType(Flights[input]->Seats[5][2].seat_status), SeatType(Flights[input]->Seats[5][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  7| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[6][0].seat_status), SeatType(Flights[input]->Seats[6][1].seat_status), SeatType(Flights[input]->Seats[6][2].seat_status), SeatType(Flights[input]->Seats[6][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  8| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[7][0].seat_status), SeatType(Flights[input]->Seats[7][1].seat_status), SeatType(Flights[input]->Seats[7][2].seat_status), SeatType(Flights[input]->Seats[7][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("  9| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[8][0].seat_status), SeatType(Flights[input]->Seats[8][1].seat_status), SeatType(Flights[input]->Seats[8][2].seat_status), SeatType(Flights[input]->Seats[8][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf(" 10| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[9][0].seat_status), SeatType(Flights[input]->Seats[9][1].seat_status), SeatType(Flights[input]->Seats[9][2].seat_status), SeatType(Flights[input]->Seats[9][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf(" 11| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[10][0].seat_status), SeatType(Flights[input]->Seats[10][1].seat_status), SeatType(Flights[input]->Seats[10][2].seat_status), SeatType(Flights[input]->Seats[10][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf(" 12| %c | %c | %c | %c |\n", SeatType(Flights[input]->Seats[11][0].seat_status), SeatType(Flights[input]->Seats[11][1].seat_status), SeatType(Flights[input]->Seats[11][2].seat_status), SeatType(Flights[input]->Seats[11][3].seat_status));
        printf("   |---|---|---|---|\n");
        printf("\n");
    }
}

//function to view one particular passenger
void ViewPassenger(struct passenger **Passengers, int input)
{
    printf("%i: %s %s - DOB: %s\n", input+1, Passengers[input]->firstname, Passengers[input]->secondname, DisplayDate(Passengers[input]->DOB));//prints out the particular passenger
}

// This function allows the database admin to edit current flights.
void EditingFlight(struct airport **Airports, int *airportsNum, int **Planes, int *planesNum, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int *flightpathsNum)
{
    char NORE;//declares a character NORE
    int flightID_input;//declares an int flightID_input
    char date_input[10];//declares an string date_input with a max character 10
    char time_input[10];//declares an string time_input with a max character 10
    int flightpathID_input;//declares an int flightpathID_input
    int planeID_input;//declares an int planeID_input
    float price_input;//declares an float price_input

    system("cls");
    printf("\n\t\t\t****Lopez Airlines****\n");
	printf("\nEnter the flight ID of the flight you wish to edit\n");// Asks the administrator to input the ID flight they want to edit
    scanf("%i", &flightID_input);
    fflush(stdin);//clears buffer
    flightID_input -= 1;

    do
	{
        system("cls");
        printf("\n\t\t\t****Lopez Airlines****\n");
        ViewFlight(Airports, Planes, Flights, Flightpaths, flightID_input);//calls upon the function view flights
        printf("\nWhat do you want to edit?\n");
        printf("\n1 - Flight path\n2 - Plane \n3 - Time \n4 - Date \n5 - Price \n6 - Exit\n");
        scanf("%c", &NORE);//inputs the relevant Number
        fflush(stdin);//clears buffer

		switch(NORE)
		{
			case '1' :
				printf("\nHere are the available flight paths:\n");
                ViewFlightPaths(Airports, airportsNum, Flightpaths, flightpathsNum);//calls upon the function ViewFlightPaths
                printf("\nChoose a flight path\n");
                scanf("%i", &flightpathID_input);//inputs the relevant number
                fflush(stdin);//clears buffer
                flightpathID_input -= 1;

				Flights[flightID_input]->flightpathID = flightpathID_input;//gives the Flight ID value onto the struct
				break;


			case '2' :
			    printf("\nHere are the available planes:\n");
                ViewPlanes(Planes, planesNum);//calls upon the function View Planes
                printf("\nChoose a plane\n");
                scanf("%i", &planeID_input);
                fflush(stdin);//clears buffer
                planeID_input -= 1;

				Flights[flightID_input]->planeID = planeID_input;//gives the Plane ID value onto the struct
				break;


			case '3' :
			    printf("\nPlease type in the time of the flight in terms of hhmm:\n");
                printf("hh stands for the hours - example 01, 02, 03...,24.\n");
                printf("mm stands for the minutes - example 01, 02, 03...,59.\n");
                scanf("%4s", &time_input);
                fflush(stdin);//clears buffer

                strcpy(Flights[flightID_input]->time, time_input);//gives the time value onto the struct
				break;


            case '4' :
				printf("\nPlease type in the date of the flight in terms of ddmmyy:\n");
                printf("dd stands for the day - example 01, 02, 03...,31.\n");
                printf("mm stands for the month - example 01, 02, 03...,12.\n");
                printf("yy stands for the year - example 01, 02, 03...\n");
                scanf("%6s", &date_input);//inputs the date
                fflush(stdin);//clears buffer

                strcpy(Flights[flightID_input]->date, date_input);//gives the date value onto the struct
				break;


            case '5' :
                printf("\nPlease type in the price of the flight:\n");
                scanf("%f", &price_input);//inputs tbe value for price
                fflush(stdin);//clears buffer

				Flights[flightID_input]->price = price_input;//gives the flight value onto the struct
				break;

            case '6' :
                break;
			default :
			    system("cls");//clears screen
				printf("\nInvalid Letter! Please try again\n");
		}
	}while(NORE != '6');//if condition is not equal to 6

}

/*This function is used by the ticket agent to search for flights.
By inputting a departure or arrival airport or date the program
can cross reference the available flights and displays the ones
are in the search criteria.*/

void SearchFlight(struct airport **Airports, int *airportsNum, int **Planes, struct flight *Flights[], int *flightsNum, struct flightpath **Flightpaths, int searchType)
{
    int c;//declares an int c
    int airportChoice;//declares an int airportchoice
    char date[10];//declares a string date with a max of 11 characters
    system("cls");//clears screen
	printf("\n\t\t\t****Lopez Airlines****\n");

    switch(searchType)// Switch statement using search type from ticket agent function
    {
        case 1:
        case 2:
            printf("\nHere are the available airports:\n");
            ViewAirports(Airports, airportsNum);//uses function ViewAirports and views the current airports
            printf("\nChoose an airport:\n");
            scanf("%i", &airportChoice);//inputs the number for airport wanted
            fflush(stdin);//clears buffer
            airportChoice -= 1;
            break;

        case 3://search by date
            printf("\nPlease type in the date you wish to search by in terms of ddmmyy:\n");
            printf("dd stands for the day - example 01, 02, 03...,31.\n");	// Asks for date to serach by.
            printf("mm stands for the month - example 01, 02, 03...,12.\n");
            printf("yy stands for the year - example 01, 02, 03...\n");
            scanf("%6s", &date);//inputs the date
            fflush(stdin);//clears buffer
            break;
        default:
            break;
    }

    system("cls");
	printf("\n\t\t\t****Lopez Airlines****\n");
	printf("\nHere are the flights matching your search:\n");

    switch(searchType) // Displays flights depending on chosen search method.
    {
        case 1:
            for (c=0; c<*flightsNum; c++)// Displays flights with same deaprture airports.
            {
                if (Flightpaths[Flights[c]->flightpathID]->departure_airportID == airportChoice)//if the function goes according to the condition
                {
                    ViewFlight(Airports, Planes, Flights, Flightpaths, c);//calls upon function ViewFlight
                }
            }
            break;


        case 2:
            for (c=0; c<*flightsNum; c++)// Displays flights with same arrival airports.
            {
                if (Flightpaths[Flights[c]->flightpathID]->arrival_airportID == airportChoice)//if the function goes according to the condition
                {
                    ViewFlight(Airports, Planes, Flights, Flightpaths, c);//calls upon function ViewFlight
                }
            }
            break;


        case 3:
            for (c=0; c<*flightsNum; c++)// Displays flights with same deaprture date.
            {
                if (strcmp(Flights[c]->date, date) == 0)//string compare
                {
                    ViewFlight(Airports, Planes, Flights, Flightpaths, c);//calls upon function ViewFlight
                }
            }
            break;

        default :
        // If chosen wrong method then will show an error message.
            system("cls");//clears screen
            printf("\nInvalid search type, try starting again!\n");
    }
}

// This function displays the time of the flight when viewing the flight details
char* DisplayTime(char* input)
{
    char *out;// Passes the time inputted from another function.
    out = malloc(6 * sizeof(char));	// This takes a set of number that was inputted in the program as the
    out[0] = input[0];// time, and then returns it properly set out as the time.
    out[1] = input[1];
    strcpy(&out[2], ":");//gives the colon to separate hours and minutes
    out[3] = input[2];
    out[4] = input[3];
    out[5] = '\0';
    return out;//returns the answers
}

// This function displays the date of the flight when viewing the flight details.
char* DisplayDate(char* input)
{
    char *out;// Passes the date inputted from another function.
    out = malloc(9 * sizeof(char));	// This takes a set of number that was inputted in the program as the
    out[0] = input[0];// date, and then returns it properly set out as the date.
    out[1] = input[1];
    strcpy(&out[2], "/");//gives the slash between the day and month
    out[3] = input[2];
    out[4] = input[3];
    strcpy(&out[5], "/");//gives the slash between the month and year
    out[6] = input[4];
    out[7] = input[5];
    out[8] = '\0';//end of string
    return out;//returns the answers
}

// This function displays the plane type of the flight in the view flights function
char* PlaneType(int* input)
{
    char *out;// Passes the selected plane inputted from another function.
    if (input == 0)// This takes the choice and properly sets it out as the it
    {			   // should be.
        out = malloc(4 * sizeof(char));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
        strcpy(&out[0], "P");
        strcpy(&out[1], "6");// This sets it out for the p62 plane
        strcpy(&out[2], "2");
        out[3] = '\0';//End of string
    }
    else
    {
        out = malloc(5 * sizeof(char));//memory size is reserved and is pointed to the address of the first byte of the block that is returned
        strcpy(&out[0], "P");
        strcpy(&out[1], "1");// This sets it out for the p124 plane
        strcpy(&out[2], "2");
        strcpy(&out[3], "4");
        out[4] = '\0';//End of string
    }
    return out;//returns answers
}

// This function is used to return the chosen seat type
char SeatType(int input)
{
    switch(input)
    {
        case 0:
            return ' ';//space if not
            break;
        case 1:
            return 'R';//If reserved R shows up
            break;
        case 2:
            return 'B';//if booked B shows up
            break;
        default:
            return ' ';//space if not
            break;
    }
}
