#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct pa
{
    long long cnic;
    int paNumber;
    string province;
    string name;
    string party;
    string electoralSymbol;
};

void addPACandidate(pa *candidates, int &currentIndex, int maxRecords);
void viewPACandidates(const pa *candidates, int currentIndex);
void checkPACandidate(const pa *candidates, int currentIndex);
void readPACandidateFile(pa *candidates, int &currentIndex, int maxRecords);
void writePACandidateFile(pa *candidates, int currentIndex);

void paCandidateRecord()
{
    const int maxRecords = 100;
    pa *candidates = new pa[maxRecords];
    int currentIndex = 0;
    readPACandidateFile(candidates, currentIndex, maxRecords);

    while (currentIndex < maxRecords)
    {
        cout << "\n1. Add PA Candidate \n2. View PA Candidates \n3. Search PA Candidate \n4. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\t    ADD A NEW PROVINCIAL ASSEMBLY CANDIDATE \n--------------------------------------------------------------------------" << endl;
            addPACandidate(candidates, currentIndex, maxRecords);
            break;
        case 2:
            cout << "Provincial Assembly Candidates Record: " << endl;
            viewPACandidates(candidates, currentIndex);
            break;
        case 3:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tSEARCH PROVINCIAL ASSEMBLY CANDIDATE \n--------------------------------------------------------------------------" << endl;
            checkPACandidate(candidates, currentIndex);
            break;
        case 4:
            cout << "\nGoing Back To Menu" << endl;
            writePACandidateFile(candidates, currentIndex);
            return;
        default:
            cout << "Invalid Option!\n";
        }
    }
    writePACandidateFile(candidates, currentIndex);
}

void addPACandidate(pa *candidates, int &currentIndex, int maxRecords)
{
    if (currentIndex < maxRecords)
    {
        cout << "Enter CNIC: ";
        cin >> candidates[currentIndex].cnic;

        cout << "Enter PA Number: ";
        cin >> candidates[currentIndex].paNumber;

        cout << "Enter Province: ";
        cin.ignore();
        getline(cin, candidates[currentIndex].province);

        cout << "Enter Name: ";
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

void viewPACandidates(const pa *candidates, int currentIndex)
{
    cout << "------------------------------------------------------------------------------------------------------------------" << setw(15) << left << "\nCNIC" << setw(15) << left << " PA Number" << setw(20) << left << " Province"
         << setw(20) << left << " Name" << setw(20) << left << " Party" << setw(25) << left << " Electoral Symbol" << endl
         << "------------------------------------------------------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < currentIndex; i++)
    {
        cout << setw(15) << left << candidates[i].cnic << setw(15) << left << candidates[i].paNumber << setw(20) << left << candidates[i].province
             << setw(20) << left << candidates[i].name << setw(20) << left << candidates[i].party << setw(25) << left << candidates[i].electoralSymbol << endl;
    }

    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
}

void checkPACandidate(const pa *candidates, int currentIndex)
{
    int constituencyCheck;
    cout << "Enter the PA Constituency to view the candidates for it: " << endl;
    cin >> constituencyCheck;
    bool exists = false;
    bool printed = false;
    for (int i = 0; i < currentIndex; i++)
    {
        if (constituencyCheck == candidates[i].paNumber)
        {
            exists = true;
            if (!printed)
            {
                cout << "\nCandidates for Constitueny PA-" << constituencyCheck << ": \n"
                     << endl;
            }
            printed = true;
            cout << setw(15) << left << candidates[i].cnic << setw(15) << left << candidates[i].paNumber << setw(20) << left << candidates[i].name
                 << setw(20) << left << candidates[i].party << setw(25) << left << candidates[i].electoralSymbol << "\n"
                 << endl;
        }
    }
    if (!exists)
    {
        cout << "No candidates found for PA-" << constituencyCheck << " in record\n"
             << endl;
    }
}

void readPACandidateFile(pa *candidates, int &currentIndex, int maxRecords)
{
    ifstream fin;
    fin.open("PACandidates.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File 'PACandidates.txt'. ");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    while (!fin.eof())
    {
        fin >> candidates[currentIndex].cnic >> candidates[currentIndex].paNumber;
        fin.ignore();
        getline(fin, candidates[currentIndex].province);
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

void writePACandidateFile(pa *candidates, int currentIndex)
{
    ofstream fout;
    fout.open("PACandidates.txt");
    try
    {
        if (fout.fail())
            throw runtime_error("Error opening/ creating file 'PACandidates.txt'");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    for (int i = 0; i < currentIndex; i++)
    {
        fout << candidates[i].cnic << " " << candidates[i].paNumber << " " << candidates[i].province << "\n"
             << candidates[i].name << "\n"
             << candidates[i].party << "\n"
             << candidates[i].electoralSymbol << endl
             << endl;
    }
    fout.close();
}
