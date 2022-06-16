#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;


//Used constants
const int MAXOFFICES = 50;
const int MAXCURRENCIES = 10;
const string EmptyString = "";

struct Currency
{
	char ISO[3] = "";
	float BuyRate = 0;
	float SellRate = 0;
	float MaxExchange = 0;
};

struct ExchangeOffice
{
	char Name[20] = "";
	int FoundingYear = 0;
	int RegistrationNumber = 0;
	int AvailableCurrencies = 1;
	Currency Currencies[MAXCURRENCIES];
};


//Function adds exchange office to the array
//Accepts an array and the count of the offices
void AddOffice(ExchangeOffice officesArray[], int& officesCount)
{
	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << "Adding an exchange office" << endl;

			cout << "Exchange office name:";
			string name = "";
			cin.ignore();
			getline(cin, name);
			strcpy_s(officesArray[i].Name, name.c_str());

			cout << "Founding year of the exchange office:";
			cin >> officesArray[i].FoundingYear;

			cout << "Registration number of the exchange office:";
			cin >> officesArray[i].RegistrationNumber;

			cout << "Adding a currency to the exchange office" << endl;
			cout << "ISO:";
			cin >> officesArray[i].Currencies[0].ISO;
			cout << "Buying rate:";
			cin >> officesArray[i].Currencies[0].BuyRate;
			cout << "Selling rate:";
			cin >> officesArray[i].Currencies[0].SellRate;
			cout << "Available amount:";
			cin >> officesArray[i].Currencies[0].MaxExchange;

			officesCount += 1;
			break;
		}
	}
}

//The function adds multiple exchange offices to the array
//Accepts an array and the count of the offices
void AddListOfOffices(ExchangeOffice officesArray[], int& officesCount)
{
	int countOfNewOffices = 0;
	cout << "How many exchange offices do you want to add:";
	cin >> countOfNewOffices;

	for (int i = 0; i < countOfNewOffices; i++)
	{
		AddOffice(officesArray, officesCount);
		system("CLS");

		if (i != countOfNewOffices - 1)
		{
			char anwser;
			cout << "Would you like to add another exchange office?"
				<< endl << "Enter \"y\" for yes or another key for no." << endl;
			cin >> anwser;

			if (anwser != 'y') break;
			system("CLS");
		}
	}
}

//The function outputs all of the exchange offices in the array
//Accepts an array of type ExchangeOffice
void PrintOffices(ExchangeOffice officesArray[])
{
	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}

		cout << setw(10) << left << "Name: " << officesArray[i].Name << setw(10) << left << " | Registration number: " << officesArray[i].RegistrationNumber
			<< setw(5) << left << " | Year of founding: " << officesArray[i].FoundingYear << setw(2) << left << " | Number of currencies: " << officesArray[i].AvailableCurrencies << endl;

		cout << "Currencies: " << endl;
		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			cout << setw(3) << left << "ISO: " << officesArray[i].Currencies[k].ISO << setw(7) << left << " | Buying rate: " << officesArray[i].Currencies[k].BuyRate << setw(7) << left << " | Selling rate: " 
				<< officesArray[i].Currencies[k].SellRate << setw(5) << left << " | Available amount: " << officesArray[i].Currencies[k].MaxExchange << endl;
		}
		cout << endl;

		if (i != 0 && (i + 1) % 5 == 0)
		{
			char choice;
			cout << endl << "Enter \"y\" to see the next page or another key to exit" << endl;
			cin >> choice;
			if (choice == 'y')
			{
				system("CLS");
				continue;
			}
			else break;
		}
	}
}

//The function outputs the currency with the lowest exchange limit from all exchange offices and all other currencies(if there are any) with the same exchange limit
//Accepts an array of type ExchangeOffice
void PrintOfficesWithMinimal(ExchangeOffice officesArray[])
{
	float minExchange = officesArray[0].Currencies[0].MaxExchange;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0) break;
		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].MaxExchange < minExchange)
			{
				minExchange = officesArray[i].Currencies[k].MaxExchange;
			}
		}
	}

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}

		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].MaxExchange == minExchange)
			{
				cout << "Name: " << officesArray[i].Name << " | Registration number: " << officesArray[i].RegistrationNumber
					<< " | Available amount: " << officesArray[i].Currencies[k].MaxExchange << " | ISO: " << officesArray[i].Currencies[k].ISO << endl;
			}
		}

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Enter \"y\" to see the next page or another key to exit" << endl;
			cin >> choice;
			if (choice == 'y') continue;
			else break;
		}
	}
}

//The function outputs all exchange offices in the array that match the year of founding interval provided
//Accepts an array of type ExchangeOffice
void PrintOfficesWithFoundingYe(ExchangeOffice officesArray[])
{
	int startYear = 0;
	int endYear = 0;
	cout << "Year - From: ";
	cin >> startYear;
	cout << "Year - To: ";
	cin >> endYear;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}

		if (officesArray[i].FoundingYear >= startYear && officesArray[i].FoundingYear <= endYear)
		{
			cout << "Name: " << officesArray[i].Name << " | Registration number: " << officesArray[i].RegistrationNumber
				<< " | Year of founding: " << officesArray[i].FoundingYear << " | Number of currencies: " << officesArray[i].AvailableCurrencies << endl;

			if (i % 5 == 0 && i != 0)
			{
				char choice;
				cout << endl << "Enter \"y\" to see the next page or another key to exit" << endl;
				cin >> choice;
				if (choice == 'y') continue;
				else break;
			}
		}
	}
}

//The function outputs all exchange offfices in the array sorted by the year they were founded
//Accepts an array of type ExchangeOffice and the count of elements in the array
void PrintOfficesByYear(ExchangeOffice officesArray[], int* officesCount)
{
	for (int i = 0; i < *officesCount; i++)
	{
		for (int k = i + 1; k < *officesCount; k++)
		{
			if (officesArray[i].FoundingYear > officesArray[k].FoundingYear)
			{
				ExchangeOffice tmp = officesArray[i];
				officesArray[i] = officesArray[k];
				officesArray[k] = tmp;
			}
		}
	}

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}


		cout << setw(10) << left << "Name: " << officesArray[i].Name << setw(10) << left << " | Registration number: " << officesArray[i].RegistrationNumber
			<< setw(5) << left << " | Year of founding: " << officesArray[i].FoundingYear << setw(2) << left << " | Number of currencies: " << officesArray[i].AvailableCurrencies << endl;

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Enter \"y\" to see the next page or another key to exit" << endl;
			cin >> choice;
			if (choice == 'y') continue;
			else break;
		}
	}
}

//The fucntion outputs all exchange offices that have the lowest price for a certain currency
//Accepts an array of type ExchangeOffice
void PrintOfficesByPriceOfCurrency(ExchangeOffice officesArray[])
{
	char tempISO[3] = "";
	float lowestPrice = 999999999.0;
	cout << "Въведете ISO на валутата: ";
	cin >> tempISO;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0) break;
		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(tempISO, officesArray[i].Currencies[k].ISO) == 0) continue;
			if (officesArray[i].Currencies[k].SellRate < lowestPrice)
			{
				lowestPrice = officesArray[i].Currencies[k].SellRate;
			}
		}

		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}

		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].SellRate == lowestPrice)
			{
				cout << setw(10) << left << "Name: " << officesArray[i].Name << setw(10) << left << " | Registration number: " << officesArray[i].RegistrationNumber
					<< setw(3) << left << " | ISO: " << officesArray[i].Currencies[k].ISO << setw(7) << left << " | Selling rate: " << officesArray[i].Currencies[k].SellRate << endl;
			}
		}
	}
}


//The function outputs all exchange offices in the array that have higher max exchange limits than the one provided one
//Accepts an array of type ExchangeOffice
void PrintOfficesByMax(ExchangeOffice officesArray[])
{
	float minExchange = 0;
	cout << "Enter minimal availability: ";
	cin >> minExchange;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}

		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].MaxExchange > minExchange)
			{
				cout << setw(10) << left << "Name: " << officesArray[i].Name << setw(10) << left << " | Registration number: " << officesArray[i].RegistrationNumber
					<< setw(3) << left << " | ISO: " << officesArray[i].Currencies[k].ISO << setw(7) << left << " | Availability: " << officesArray[i].Currencies[k].MaxExchange << endl;
			}
		}

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Enter \"y\" to see the next page or another key to exit" << endl;
			cin >> choice;
			if (choice == 'y') continue;
			else break;
		}
	}
}

//The function outputs all exchange offices in the array that have less than six currencies.
//Accepts an arrray of type ExchangeOffice
void PrintOfficesWithLessThanSix(ExchangeOffice officesArray[])
{
	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "End of list" << endl;
			system("pause");
			break;
		}

		if (officesArray[i].AvailableCurrencies < 6)
		{
			cout << setw(10) << left << "Name: " << officesArray[i].Name << setw(10) << left << " | Registration number: " << officesArray[i].RegistrationNumber
				<< setw(5) << left << " | Year of founding: " << officesArray[i].FoundingYear << setw(2) << left << " | Number of currencies: " << officesArray[i].AvailableCurrencies << endl;
		}

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Enter \"y\" to see the next page or another key to exit" << endl;
			cin >> choice;
			if (choice == 'y') continue;
			else break;
		}
	}
}

//The function is used for a submenu for the function that output data
//Accepts an array of type ExchangeOffice and the count of elements in the array
void PrintOfficesMenu(ExchangeOffice officesArray[], int* officesCount)
{
	unsigned short option = 0;
	char choice = 'n';
	do {
		system("CLS");
		cout << "Print Menu" << endl;
		cout << "1. Print all exchange offices" << endl;
		cout << "2. Print all exchange offices with the lowest availability" << endl;
		cout << "3. Print all exchange offices by year of founding" << endl;
		cout << "4. Print exchange offices within a year interval" << endl;
		cout << "5. Print exchange offices with the cheapest currency" << endl;
		cout << "6. Print all exchange offices by availability" << endl;
		cout << "7. Print exchange offices with less than six currencies" << endl;
		cout << "8. Go back to the main menu" << endl;
		cin >> option;
		switch (option)
		{
		case 1:
		{
			system("CLS");
			PrintOffices(officesArray);
			break;
		}
		case 2:
		{
			system("CLS");
			PrintOfficesWithMinimal(officesArray);
			break;
		}
		case 3:
		{
			system("CLS");
			PrintOfficesByYear(officesArray, officesCount);
			break;
		}

		case 4:
		{
			system("CLS");
			PrintOfficesWithFoundingYe(officesArray);
			break;
		}

		case 5:
		{
			system("CLS");
			PrintOfficesByPriceOfCurrency(officesArray);
			break;
		}

		case 6:
		{
			system("CLS");
			PrintOfficesByMax(officesArray);
			break;
		}

		case 7:
		{
			system("CLS");
			PrintOfficesWithLessThanSix(officesArray);
			break;
		}

		case 8:
		{
			cout << "Are you sure you want to go back to the main menu? \n"
				 << "Enter \"y\" to go back or another key to stay" << endl;
			cin >> choice;
			if (choice == 'y')
			{
				option = 0;

			}
			break;
		}
		default:
		{
			cout << "Invalid input" << endl;
			break;
		}
		}

	} while (choice != 'y');
}


//The function allow editing the existing exhcange offices
//Accepts an array of type ExchangeOffice
void EditOffices(ExchangeOffice officesArray[])
{
	int registrationNumber = 0;
	cout << "Enter registration number: ";
	cin >> registrationNumber;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (officesArray[i].RegistrationNumber == 0)
		{
			cout << endl << "There is no exchange office with this registration number" << endl;
			system("pause");
			break;
		}
		else if (officesArray[i].RegistrationNumber == registrationNumber)
		{
			cout << "Editing an exchange office" << endl;

			cout << "Name: " << officesArray[i].Name << endl;
			cout << "New name: ";
			cin >> officesArray[i].Name;

			cout << "Registration number: " << officesArray[i].RegistrationNumber << endl;
			cout << "New Registration number: ";
			cin >> officesArray[i].RegistrationNumber;

			cout << "Year of founding: " << officesArray[i].FoundingYear << endl;
			cout << "New year of founding: ";
			cin >> officesArray[i].FoundingYear;

			break;
		}
	}

	cout << endl << "Successful edit!" << endl;
	system("pause");
}


//The function adds a new currency to an exsisting exchange offfice
//Accepts an array of type ExchangeOffice
void AddCurrencyToOffice(ExchangeOffice officesArray[])
{
	int registrationNumber = 0;
	cout << "Enter registration number of the exchange office: ";
	cin >> registrationNumber;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (officesArray[i].RegistrationNumber == 0)
		{
			cout << endl << "There is no exchange office with this registration number!" << endl;
			system("pause");
			break;
		}
		else if (officesArray[i].RegistrationNumber == registrationNumber && officesArray[i].AvailableCurrencies >= MAXCURRENCIES)
		{
			cout << endl << "The exchange office already has the maximum amount of currencies" << endl;
			system("pause");
			break;
		}
		else if (officesArray[i].RegistrationNumber == registrationNumber)
		{
			for (int k = 0; k < MAXCURRENCIES; k++)
			{
				if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0)
				{
					cout << "Adding a currency" << endl;
					cout << "ISO:";
					cin >> officesArray[i].Currencies[k].ISO;
					cout << "Buying rate:";
					cin >> officesArray[i].Currencies[k].BuyRate;
					cout << "Selling rate:";
					cin >> officesArray[i].Currencies[k].SellRate;
					cout << "Available amount:";
					cin >> officesArray[i].Currencies[k].MaxExchange;

					officesArray[i].AvailableCurrencies++;
					break;
				}
			}
			break;
		}
	}

	cout << endl << "The currency was added!" << endl;
	system("pause");
}

//The fucntion exchanges the currency in a certaion exchange office
//Accepts an array of type ExchangeOffice
void ExchangeCurrency(ExchangeOffice officesArray[])
{
	int registrationNumber = 0;
	int tempISOIndex = 0;
	cout << "Enter registration number of the exchange office: ";
	cin >> registrationNumber;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (officesArray[i].RegistrationNumber == 0) break;
		else if (officesArray[i].RegistrationNumber == registrationNumber)
		{
			for (int k = 0; k < MAXCURRENCIES; k++)
			{
				if (officesArray[i].Currencies[k].MaxExchange != 0)
				{
					cout << "Currencies in the exchange office" << endl;
					cout << k + 1 << ". "
						<< "ISO: " << officesArray[i].Currencies[k].ISO << endl
						<< "Buying rate: " << officesArray[i].Currencies[k].BuyRate << endl
						<< "Selling rate: " << officesArray[i].Currencies[k].SellRate << endl
						<< "Available amount: " << officesArray[i].Currencies[k].MaxExchange;

				}
			}

			cout << endl << "Enter the number of the currency you want to exchange: ";
			cin >> tempISOIndex;

			for (int k = 0; k < MAXCURRENCIES; k++)
			{
				if (tempISOIndex - 1 == k)
				{
					float sumToExchange = 0;
					cout << "Enter the amount you want to exchange: ";
					cin >> sumToExchange;

					if (sumToExchange > officesArray[i].Currencies[k].MaxExchange)
					{
						cout << "The amount is higher than the available currency" << endl;
						break;
					}
					else
					{
						string choice = "";
						system("CLS");
						cout << "You owe " << sumToExchange * officesArray[i].Currencies[k].SellRate << endl
							<< "Exchange y/n: ";
						cin >> choice;
						if (choice == "yes")
						{
							officesArray[i].Currencies[k].MaxExchange -= sumToExchange;
							cout << "The amount has been exchanged" << endl;
							break;
						}
						else cout << "Going back to the menu" << endl;
					}

				}
			}
		}
	}
	system("pause");
}

//The function saves the data in the array to a file
//Accepts an array of type ExchangeOffice and the count of the elements in the array
void OfficeBinaryFileSave(ExchangeOffice officesArray[], int* officesCount)
{
	fstream file;
	file.open("ExchangeOffices.bin", ios::binary | ios::out);

	file.write((char*)&officesArray, *officesCount * sizeof(ExchangeOffice));

	cout << "The data has been saved" << endl;
	file.close();
	system("pause");
}

//The function reads the data from the file and fills out the array
//Accepts an array of type ExchangeOffice and the count of the elements in the array
void OfficeBinaryFileRead(ExchangeOffice officesArray[], int& officesCount)
{
	fstream file;
	file.open("ExchangeOffices.bin", ios::binary | ios::in);
	file.seekg(0L, ios::end);
	long pos = (long)file.tellg();
	file.close();
	officesCount = pos / (sizeof(ExchangeOffice));

	file.open("ExchangeOffices.bin", ios::binary | ios::in);
	file.read((char*)&officesArray, officesCount * (sizeof(ExchangeOffice)));
	file.close();

	cout << "The data has been loaded" << endl;
	system("pause");
}


int main()
{
	ExchangeOffice Offices[MAXOFFICES];
	int OfficesCount = 0;
	OfficeBinaryFileRead(Offices, OfficesCount);

	unsigned short option = 0;
	char choice = 'n';
	do {
		system("CLS");
		cout << "Main menu" << endl;
		cout << "1. Add an exchange office" << endl;
		cout << "2. Add multiple exchange offices" << endl;
		cout << "3. Add currency to an exchange office" << endl;
		cout << "4. Edit an exchange office" << endl;
		cout << "5. Print menu" << endl;
		cout << "6. Exchange currency" << endl;
		cout << "7. Exit" << endl;
		cin >> option;
		switch (option)
		{
		case 1:
		{
			system("CLS");
			AddOffice(Offices, OfficesCount);
			break;
		}
		case 2:
		{
			system("CLS");
			AddListOfOffices(Offices, OfficesCount);
			break;
		}
		case 3:
		{
			system("CLS");
			AddCurrencyToOffice(Offices);
			break;
		}
		case 4:
		{
			system("CLS");
			EditOffices(Offices);
			break;
		}
		case 5:
		{
			system("CLS");
			PrintOfficesMenu(Offices, &OfficesCount);
			break;
		}
		case 6:
		{
			system("CLS");
			ExchangeCurrency(Offices);
			break;
		}
		case 7:
		{
			cout << "Are you sure you want to exit the application? \n"
				"Enter \"y\" to exit or another key to stay." << endl;
			cin >> choice;
			if (choice == 'y')
			{
				option = 0;
				OfficeBinaryFileSave(Offices, &OfficesCount);
			}
			break;
		}
		default:
		{
			cout << "Invalid input" << endl;
			break;
		}
		}

	} while (choice != 'y');

	return 0;
}