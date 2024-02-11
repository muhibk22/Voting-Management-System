#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct na
{
    long long cnic;
    int naNumber;
    string name;
    string party;
    string electoralSymbol;
};

void addNACandidate(na *candidates, int &currentIndex, int maxRecords);
void viewNACandidates(const na *candidates, int currentIndex);
void checkNACandidate(const na *candidates, int currentIndex);
void readNACandidateFile(na *candidates, int &currentIndex, int maxRecords);
void writeNACandidateFile(na *candidates, int currentIndex);

void naCandidateRecord()
{
    const int maxRecords = 100;
    na *candidates = new na[maxRecords];
    int currentIndex = 0;
    readNACandidateFile(candidates, currentIndex, maxRecords);

    while (currentIndex < maxRecords)
    {
        cout << "\n1. Add NA Candidate \n2. View NA Candidates \n3. Search NA Candidate \n4. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t  ADD A NEW NATIONAL ASSEMBLY CANDIDATE \n--------------------------------------------------------------------------" << endl;
            addNACandidate(candidates, currentIndex, maxRecords);
            break;
        case 2:
            cout << "\nNA Candidates Record: " << endl;
            viewNACandidates(candidates, currentIndex);
            break;
        case 3:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\tSEARCH NATIONAL ASSEMBLY CANDIDATE \n--------------------------------------------------------------------------" << endl;
            checkNACandidate(candidates, currentIndex);
            break;
        case 4:
            cout << "\nGoing Back To Menu" << endl;
            writeNACandidateFile(candidates, currentIndex);
            return;
        default:
            cout << "Invalid Option!\n";
        }
    }
    writeNACandidateFile(candidates, currentIndex);
}

void addNACandidate(na *candidates, int &currentIndex, int maxRecords)
{
    if (currentIndex < maxRecords)
    {
        cout << "Enter CNIC: ";
        cin >> candidates[currentIndex].cnic;

        cout << "Enter NA Number: ";
        cin >> candidates[currentIndex].naNumber;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, candidates[currentIndex].name);

        cout << "Enter Party: ";
        getline(cin, candidates[currentIndex].party);

        cout << "Enter Electoral Symbol: ";
        getline(cin, candidates[currentIndex].electoralSymbol);

        currentIndex++;
    }
    else
    {
        cout << "Maximum Records Reached";
    }
}

void viewNACandidates(const na *candidates, int currentIndex)
{
    cout << "------------------------------------------------------------------------------------------------------------------" << setw(15) << left << "\nCNIC" << setw(15) << left << " NA Number" << setw(20) << left << " Name"
         << setw(20) << left << " Party" << setw(25) << left << " Electoral Symbol" << endl
         << "------------------------------------------------------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < currentIndex; i++)
    {
        cout << setw(15) << left << candidates[i].cnic << setw(15) << left << candidates[i].naNumber << setw(20) << left << candidates[i].name
             << setw(20) << left << candidates[i].party << setw(25) << left << candidates[i].electoralSymbol << endl;
    }

    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
}

void checkNACandidate(const na *candidates, int currentIndex)
{
    int constituencyCheck;
    cout << "Enter the NA Constituency to view the candidates for it: " << endl;
    cin >> constituencyCheck;
    bool exists = false;
    bool printed = false;
    for (int i = 0; i < currentIndex; i++)
    {
        if (constituencyCheck == candidates[i].naNumber)
        {
            exists = true;
            if (!printed)
            {
                cout << "\nCandidates for Constitueny NA-" << constituencyCheck << ": \n"
                     << endl;
            }
            printed = true;
            cout << setw(15) << left << candidates[i].cnic << setw(15) << left << candidates[i].naNumber << setw(20) << left << candidates[i].name
                 << setw(20) << left << candidates[i].party << setw(25) << left << candidates[i].electoralSymbol << "\n"
                 << endl;
        }
    }
    if (!exists)
    {
        cout << "No candidates found for NA-" << constituencyCheck << " in record\n"
             << endl;
    }
}

void readNACandidateFile(na *candidates, int &currentIndex, int maxRecords)
{
    ifstream fin;
    fin.open("NACandidates.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File. Please create file 'NACandidates.txt' and try again. ");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    while (!fin.eof())
    {
        fin >> candidates[currentIndex].cnic >> candidates[currentIndex].naNumber;
        fin.ignore();
        getline(fin, candidates[currentIndex].name);
        getline(fin, candidates[currentIndex].party);
        getline(fin, candidates[currentIndex].electoralSymbol);

        if (!fin.eof())
        {
            currentIndex++;
        }
    }
    fin.close();
}

void writeNACandidateFile(na *candidates, int currentIndex)
{
    ofstream fout;
    fout.open("NACandidates.txt");
    try
    {
        if (fout.fail())
            throw runtime_error("Error creating file 'NACandidates.txt'");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    for (int i = 0; i < currentIndex; i++)
    {
        fout << candidates[i].cnic << " " << candidates[i].naNumber << " " << candidates[i].name << "\n"
             << candidates[i].party << "\n"
             << candidates[i].electoralSymbol << endl
             << endl;
    }
    fout.close();
}
