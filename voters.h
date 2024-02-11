#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct voter
{
    long long cnic;
    int blockCode;
    string name;
    int na;
    int pa;
    string pollingStation;
    string province;
};

void addVoter(voter *voters, int &currentIndex, int maxRecords);
void viewVoter(const voter *voters, int currentIndex);
void checkVoter(const voter *voters, int currentIndex);
void readVoterFile(voter *voters, int &currentIndex, int maxRecords);
void writeVoterFile(voter *voters, int currentIndex);

void voterRecord()
{
    const int maxRecords = 100;
    voter *voters = new voter[maxRecords];
    int currentIndex = 0;
    readVoterFile(voters, currentIndex, maxRecords);

    while (currentIndex < maxRecords)
    {
        cout << "\n1. Add Voter \n2. View Voters \n3. Search Voter \n4. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\t    ADD A NEW VOTER \n--------------------------------------------------------------------------" << endl;
            addVoter(voters, currentIndex, maxRecords);
            break;
        case 2:
            cout << "Voters Record: " << endl;
            viewVoter(voters, currentIndex);
            break;
        case 3:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tSEARCH VOTER \n--------------------------------------------------------------------------" << endl;
            checkVoter(voters, currentIndex);
            break;
        case 4:
            cout << "\nGoing Back To Menu" << endl;
            writeVoterFile(voters, currentIndex);
            return;
        default:
            cout << "Invalid Option!\n";
        }
    }
    writeVoterFile(voters, currentIndex);
}

void addVoter(voter *voters, int &currentIndex, int maxRecords)
{
    if (currentIndex < maxRecords)
    {
        cout << "Enter CNIC: ";
        cin >> voters[currentIndex].cnic;

        cout << "Enter Block Code: ";
        cin >> voters[currentIndex].blockCode;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, voters[currentIndex].name);

        cout << "Enter NA: ";
        cin >> voters[currentIndex].na;

        cout << "Enter PA: ";
        cin >> voters[currentIndex].pa;

        cout << "Enter Polling Station: ";
        cin.ignore();
        getline(cin, voters[currentIndex].pollingStation);

        cout << "Enter Province: ";
        getline(cin, voters[currentIndex].province);

        currentIndex++;
    }
    else
    {
        cout << "Maximum Records Reached";
    }
}

void viewVoter(const voter *voters, int currentIndex)
{
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << setw(15) << left << "\nCNIC" << setw(15) << left << " Block Code" << setw(20) << left << " Name"
         << setw(10) << left << " NA" << setw(10) << left << " PA" << setw(25) << left << " Polling Station" << setw(15) << left << " Province" << endl
         << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < currentIndex; i++)
    {
        cout << setw(15) << left << voters[i].cnic << setw(15) << left << voters[i].blockCode << setw(20) << left << voters[i].name
             << setw(10) << left << voters[i].na << setw(10) << left << voters[i].pa << setw(25) << left << voters[i].pollingStation
             << setw(15) << left << voters[i].province << endl;
    }

    cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void checkVoter(const voter *voters, int currentIndex)
{
    long long cnicCheck;
    cout << "Enter the CNIC of the Voter you want to check: " << endl;
    cin >> cnicCheck;
    bool exists = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (cnicCheck == voters[i].cnic)
        {
            exists = true;
            break;
        }
    }
    if (exists)
    {
        cout << "Voter with CNIC: " << cnicCheck << " exists in record: \n"
             << endl;
        cout << setw(15) << left << voters[i].cnic << setw(15) << left << voters[i].blockCode << setw(20) << left << voters[i].name
             << setw(10) << left << voters[i].na << setw(10) << left << voters[i].pa << setw(25) << left << voters[i].pollingStation
             << setw(15) << left << voters[i].province << "\n"
             << endl;
    }
    else
    {
        cout << "Voter with CNIC: " << cnicCheck << " does not exist in record.\n"
             << endl;
    }
}

void readVoterFile(voter *voters, int &currentIndex, int maxRecords)
{
    ifstream fin;
    fin.open("Voters.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File. Please create file 'Voters.txt' and try again. ");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    while (!fin.eof())
    {
        fin >> voters[currentIndex].cnic >> voters[currentIndex].blockCode;
        fin.ignore();
        getline(fin, voters[currentIndex].name);
        fin >> voters[currentIndex].na >> voters[currentIndex].pa;
        fin.ignore();
        getline(fin, voters[currentIndex].pollingStation);
        getline(fin, voters[currentIndex].province);

        if (!fin.eof())
        {
            currentIndex++;
        }
    }
    fin.close();
}

void writeVoterFile(voter *voters, int currentIndex)
{
    ofstream fout;
    fout.open("Voters.txt");
    try
    {
        if (fout.fail())
            throw runtime_error("Error creating file 'Voters.txt'");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    for (int i = 0; i < currentIndex; i++)
    {
        fout << voters[i].cnic << " " << voters[i].blockCode << " " << voters[i].name << "\n"
             << voters[i].na << " " << voters[i].pa << " " << voters[i].pollingStation << "\n"
             << voters[i].province << endl<<endl;
    }
    fout.close();
}