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
			cout << "Добавяне на обменно бюро" << endl;

			cout << "Име на обменното бюро:";
			string name = "";
			cin.ignore();
			getline(cin, name);
			strcpy_s(officesArray[i].Name, name.c_str());

			cout << "Година на основаване на обменното бюро:";
			cin >> officesArray[i].FoundingYear;

			cout << "Регистрационен номер на обменното бюро:";
			cin >> officesArray[i].RegistrationNumber;

			cout << "Добавяне на обменна валута към бюрото" << endl;
			cout << "ISO:";
			cin >> officesArray[i].Currencies[0].ISO;
			cout << "Курс купува:";
			cin >> officesArray[i].Currencies[0].BuyRate;
			cout << "Курс продава:";
			cin >> officesArray[i].Currencies[0].SellRate;
			cout << "Максимална стойност за обмен:";
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
	cout << "Колко обменни бюра искате да добавите:";
	cin >> countOfNewOffices;

	for (int i = 0; i < countOfNewOffices; i++)
	{
		AddOffice(officesArray, officesCount);
		system("CLS");

		if (i != countOfNewOffices - 1)
		{
			char anwser;
			cout << "Искате ли да добавите друго обменно бюро?"
				<< endl << "Изберете y за потвърждение или друга буква за отказ." << endl;
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
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}

		cout << setw(10) << left << "Име: " << officesArray[i].Name << setw(10) << left << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
			<< setw(5) << left << " | Година на основаване: " << officesArray[i].FoundingYear << setw(2) << left << " | Брой валути: " << officesArray[i].AvailableCurrencies << endl;

		cout << "Обменни валути: " << endl;
		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			cout << setw(3) << left << "ISO: " << officesArray[i].Currencies[k].ISO << setw(7) << left << " | Курс купува: " << officesArray[i].Currencies[k].BuyRate << setw(7) << left << " | Курс продава: " << officesArray[i].Currencies[k].SellRate
				<< setw(5) << left << " | Максимална сума за обмен: " << officesArray[i].Currencies[k].MaxExchange << endl;
		}
		cout << endl;

		if (i != 0 && (i + 1) % 5 == 0)
		{
			char choice;
			cout << endl << "Въведете \"y\" за да видите следващата страница" << endl;
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
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}

		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].MaxExchange == minExchange)
			{
				cout << "Име: " << officesArray[i].Name << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
					<< " | Максимален сума за обмен: " << officesArray[i].Currencies[k].MaxExchange << " | ISO: " << officesArray[i].Currencies[k].ISO << endl;
			}
		}

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Въведете \"y\" за да видите следващата страница" << endl;
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
	cout << "Въведете начална година: ";
	cin >> startYear;
	cout << "Въведете крайна година: ";
	cin >> endYear;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}

		if (officesArray[i].FoundingYear >= startYear && officesArray[i].FoundingYear <= endYear)
		{
			cout << "Име: " << officesArray[i].Name << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
				<< " | Година на основаване: " << officesArray[i].FoundingYear << " | Брой валути: " << officesArray[i].AvailableCurrencies << endl;

			if (i % 5 == 0 && i != 0)
			{
				char choice;
				cout << endl << "Въведете \"y\" за да видите следващата страница" << endl;
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
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}


		cout << setw(10) << left << "Име: " << officesArray[i].Name << setw(10) << left << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
			<< setw(5) << left << " | Година на основаване: " << officesArray[i].FoundingYear << setw(2) << left << " | Брой валути: " << officesArray[i].AvailableCurrencies << endl;

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Въведете \"y\" за да видите следващата страница" << endl;
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
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}

		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].SellRate == lowestPrice)
			{
				cout << setw(10) << left << "Име: " << officesArray[i].Name << setw(10) << left << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
					<< setw(3) << left << " | ISO: " << officesArray[i].Currencies[k].ISO << setw(7) << left << " | Цена: " << officesArray[i].Currencies[k].SellRate << endl;
			}
		}
	}
}


//The function outputs all exchange offices in the array that have higher max exchange limits than the one provided one
//Accepts an array of type ExchangeOffice
void PrintOfficesByMax(ExchangeOffice officesArray[])
{
	float minExchange = 0;
	cout << "Въведете минимална наличност: ";
	cin >> minExchange;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (strcmp(EmptyString.c_str(), officesArray[i].Name) == 0)
		{
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}

		for (int k = 0; k < MAXCURRENCIES; k++)
		{
			if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0) break;
			if (officesArray[i].Currencies[k].MaxExchange > minExchange)
			{
				cout << setw(10) << left << "Име: " << officesArray[i].Name << setw(10) << left << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
					<< setw(3) << left << " | ISO: " << officesArray[i].Currencies[k].ISO << setw(7) << left << " | Максимален сума за обмен: " << officesArray[i].Currencies[k].MaxExchange << endl;
			}
		}

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Въведете \"y\" за да видите следващата страница" << endl;
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
			cout << endl << "Край на обменните бюра" << endl;
			system("pause");
			break;
		}

		if (officesArray[i].AvailableCurrencies < 6)
		{
			cout << setw(10) << left << "Име: " << officesArray[i].Name << setw(10) << left << " | Регистрационен номер: " << officesArray[i].RegistrationNumber
				<< setw(5) << left << " | Година на основаване: " << officesArray[i].FoundingYear << setw(2) << left << " | Брой валути: " << officesArray[i].AvailableCurrencies << endl;
		}

		if (i % 5 == 0 && i != 0)
		{
			char choice;
			cout << endl << "Въведете \"y\" за да видите следващата страница" << endl;
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
		cout << "\nИзберете действие" << endl;
		cout << "1. Извеждане на всички бюра" << endl;
		cout << "2. Извеждане на всички бюра с най-малка наличност за обмен" << endl;
		cout << "3. Извеждане на всички бюра по година на основаване" << endl;
		cout << "4. Извеждане на всички бюра с дата на основаване в определен интервал" << endl;
		cout << "5. Извеждане на бюра по цена на валута" << endl;
		cout << "6. Извеждане на бюра по наличност" << endl;
		cout << "7. Извеждане на бюра с по-малко от 6 валути" << endl;
		cout << "8. Изход" << endl;
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
			cout << "Връщане към началното меню? \n"
				"Изберете y за потвърждение или друга буква за отказ." << endl;
			cin >> choice;
			if (choice == 'y')
			{
				option = 0;

			}
			break;
		}
		default:
		{
			cout << "Невалиден избор" << endl;
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
	cout << "Въведете регистрационен номер: ";
	cin >> registrationNumber;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (officesArray[i].RegistrationNumber == 0)
		{
			cout << endl << "Няма намерено обменно бюро с този номер" << endl;
			system("pause");
			break;
		}
		else if (officesArray[i].RegistrationNumber == registrationNumber)
		{
			cout << "Редактиране на обменно бюро" << endl;

			cout << "Име на обменното бюро: " << officesArray[i].Name << endl;
			cout << "Ново име на обменното бюро: ";
			cin >> officesArray[i].Name;

			cout << "Регистрационен номер на обменното бюро: " << officesArray[i].RegistrationNumber << endl;
			cout << "Нов регистрационен номер на обменното бюро: ";
			cin >> officesArray[i].RegistrationNumber;

			cout << "Година на основаване на обменното бюро: " << officesArray[i].FoundingYear << endl;
			cout << "Новата година на основаване на обменното бюро : ";
			cin >> officesArray[i].FoundingYear;

			break;
		}
	}

	cout << endl << "Бюрото е редактирано!" << endl;
	system("pause");
}


//The function adds a new currency to an exsisting exchange offfice
//Accepts an array of type ExchangeOffice
void AddCurrencyToOffice(ExchangeOffice officesArray[])
{
	int registrationNumber = 0;
	cout << "Въведете регистрационен номер: ";
	cin >> registrationNumber;
	system("CLS");

	for (int i = 0; i < MAXOFFICES; i++)
	{
		if (officesArray[i].RegistrationNumber == 0)
		{
			cout << endl << "Няма намерено обменно бюро с този номер" << endl;
			system("pause");
			break;
		}
		else if (officesArray[i].RegistrationNumber == registrationNumber && officesArray[i].AvailableCurrencies >= MAXCURRENCIES)
		{
			cout << endl << "Обменното бюро вече има максималният брой валути" << endl;
			system("pause");
			break;
		}
		else if (officesArray[i].RegistrationNumber == registrationNumber)
		{
			for (int k = 0; k < MAXCURRENCIES; k++)
			{
				if (strcmp(EmptyString.c_str(), officesArray[i].Currencies[k].ISO) == 0)
				{
					cout << "Добавяне на обменна валута към бюрото" << endl;
					cout << "ISO:";
					cin >> officesArray[i].Currencies[k].ISO;
					cout << "Курс купува:";
					cin >> officesArray[i].Currencies[k].BuyRate;
					cout << "Курс продава:";
					cin >> officesArray[i].Currencies[k].SellRate;
					cout << "Максимална стойност за обмен:";
					cin >> officesArray[i].Currencies[k].MaxExchange;

					officesArray[i].AvailableCurrencies++;
					break;
				}
			}
			break;
		}
	}

	cout << endl << "Валутата е добавена!" << endl;
	system("pause");
}

//The fucntion exchanges the currency in a certaion exchange office
//Accepts an array of type ExchangeOffice
void ExchangeCurrency(ExchangeOffice officesArray[])
{
	int registrationNumber = 0;
	int tempISOIndex = 0;
	cout << "Въведете регистрационен номер: ";
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
					cout << "Налични валути в бюрото" << endl;
					cout << k + 1 << ". "
						<< "ISO: " << officesArray[i].Currencies[k].ISO << endl
						<< "Курс купува: " << officesArray[i].Currencies[k].BuyRate << endl
						<< "Курс продава: " << officesArray[i].Currencies[k].SellRate << endl
						<< "Максимална стойност за обмен: " << officesArray[i].Currencies[k].MaxExchange;

				}
			}

			cout << endl << "Въведете номера на валутата която искате да обмените: ";
			cin >> tempISOIndex;

			for (int k = 0; k < MAXCURRENCIES; k++)
			{
				if (tempISOIndex - 1 == k)
				{
					float sumToExchange = 0;
					cout << "Въведете суматата която искате да обмените: ";
					cin >> sumToExchange;

					if (sumToExchange > officesArray[i].Currencies[k].MaxExchange)
					{
						cout << "Сумата е по-висока от максималната за дадената валута" << endl;
						break;
					}
					else
					{
						string choice = "";
						system("CLS");
						cout << "Дължите " << sumToExchange * officesArray[i].Currencies[k].SellRate << endl
							<< "Обмен yes/no: ";
						cin >> choice;
						if (choice == "yes")
						{
							officesArray[i].Currencies[k].MaxExchange -= sumToExchange;
							cout << "Сумата е обменена" << endl;
							break;
						}
						else cout << "Връщане към менюто" << endl;
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

	cout << "Данните са записани" << endl;
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

	cout << "Данните са прочетени" << endl;
	system("pause");
}


int main()
{
	setlocale(LC_ALL, "BG");

	ExchangeOffice Offices[MAXOFFICES];
	int OfficesCount = 0;
	OfficeBinaryFileRead(Offices, OfficesCount);

	unsigned short option = 0;
	char choice = 'n';
	do {
		system("CLS");
		cout << "\nИзберете действие" << endl;
		cout << "1. Добавяне на обменно бюро" << endl;
		cout << "2. Добавяне на списък с обменни бюра" << endl;
		cout << "3. Добавяне на валута към обменно бюро" << endl;
		cout << "4. Редактиране на бюро" << endl;
		cout << "5. Меню за извеждане" << endl;
		cout << "6. Обмяна на валута" << endl;
		cout << "7. Изход" << endl;
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
			cout << "Наистина ли искате да напуснете програмата? \n"
				"Изберете y за потвърждение или друга буква за отказ." << endl;
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
			cout << "Невалиден избор" << endl;
			break;
		}
		}

	} while (choice != 'y');

	return 0;
}