#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_BAGGAGES = 10;

struct Baggage
{
    string ownerName;
    double weight;
    int numberOfSeats;
    string flight;
};

Baggage baggages[MAX_BAGGAGES];
int numbaggages = 0;

void AddBaggage()
{
    if (numbaggages < MAX_BAGGAGES)
    {
        Baggage newBaggage;
        cout << "Enter owner Name: ";
        cin >> newBaggage.ownerName;
        cout << "Enter luggage weight in kilograms: ";
        cin >> newBaggage.weight;
        cout << "Enter number of seats: ";
        cin >> newBaggage.numberOfSeats;
        cout << "Enter flight: ";
        cin >> newBaggage.flight;
        baggages[numbaggages++] = newBaggage;
        cout << "you have successfully added your Baggage. \n";
    }
    else
    {
        cout << "no more can be added. \n";
    }
}

void ModifyBaggage(string ownerName)
{
    for (int i = 0; i < numbaggages; ++i)
    {
        if (baggages[i].ownerName == ownerName)
        {
            cout << "Enter luggage weight in kilograms: ";
            cin >> baggages[i].weight;
            cout << "Enter number of seats: ";
            cin >> baggages[i].numberOfSeats;
            cout << "Enter flight: ";
            cin >> baggages[i].flight;
            cout << "you have successfully modify information about your Baggage. \n";
            return;
        }
    }
    cout << "luggage with owner name " << ownerName << " not here \n";
}

void DeleteBaggage(string ownerName)
{
    for (int i = 0; i < numbaggages; ++i)
    {
        if (baggages[i].ownerName == ownerName)
        {
            baggages[i] = baggages[numbaggages - 1];
            --numbaggages;
            cout << "Baggage with owner name " << ownerName << " deleted successfully.\n";
            return;
        }
    }
    cout << "Baggage with owner name " << ownerName << " not found.\n";
}

void ShowBaggages()
{
    for (int i = 0; i < numbaggages; ++i)
    {
        cout << endl;
        cout << "Owner Name: " << baggages[i].ownerName << endl;
        cout << "Weight: " << baggages[i].weight << "kg" << endl;
        cout << "Number of Seats: " << baggages[i].numberOfSeats << endl;
        cout << "Flight: " << baggages[i].flight << endl;
    }
}

bool CompareByOwnerName(const Baggage& a, const Baggage& b)
{
    return a.ownerName < b.ownerName;
}

void SortBaggageByAlphabet()
{
    sort(baggages, baggages + numbaggages, CompareByOwnerName);
}

void SaveBaggagesToFile()
{
    ofstream outFile("baggages.bin", ios::binary | ios::out);
    if (!outFile)
    {
        cout << "Unable to open file.\n";
        return;
    }
    outFile.write((char*)&numbaggages, sizeof(numbaggages));
    outFile.write((char*)baggages, numbaggages * sizeof(Baggage));
    outFile.close();
    cout << "Baggages saved to file successfully.\n";
}

void LoadBaggagesFromFile()
{
    ifstream inFile("baggages.bin", ios::binary | ios::in);
    if (!inFile)
    {
        cout << "Unable to open file or file does not exist.\n";
        return;
    }
    inFile.read((char*)&numbaggages, sizeof(numbaggages));
    inFile.read((char*)baggages, numbaggages * sizeof(Baggage));
    inFile.close();

    cout << "Baggages loaded from file successfully.\n";
}

int main()
{
    int choice;
    string ownerName;

    LoadBaggagesFromFile();

    do
    {
        cout << "\n Menu: \n"
            << "1. Show Baggages \n"
            << "2. Add Baggage \n"
            << "3. Delete Baggage \n"
            << "4. Modify information about Baggage \n"
            << "5. Sorting Baggage by alphabet(owners name) \n"
            << "6. Save to file \n"
            << "7. Exit \n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
        {
            ShowBaggages();
            break;
        }

        case 2:
        {
            AddBaggage();
            break;
        }

        case 3:
        {
            cout << "Enter owner name to delete: ";
            cin >> ownerName;
            DeleteBaggage(ownerName);
            break;
        }

        case 4:
        {
            cout << "Enter owners name to modify information about Baggage: ";
            cin >> ownerName;
            ModifyBaggage(ownerName);
            break;
        }
        case 5:
        {
            SortBaggageByAlphabet();
            cout << "the luggage was sorted \n";
            break;
        }
        case 6:
        {
            SaveBaggagesToFile();
            break;
        }
        case 7:
        {
            cout << "Exit -_-";
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        }
    } while (choice != 7);

    return 0;
}
