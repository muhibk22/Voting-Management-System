#include "na.h"
#include "pa.h"
#include "voters.h"

void pronvincialConstituency(const int maxPaRecords, pa *paCandidates, int currentPaIndex, const int maxVoterRecords, voter *voters, int currentVoterIndex);
void displayProvinceDetails(const string &province, int currentPaIndex, pa *paCandidates, int currentVoterIndex, voter *voters);
void nationalConstituency(const int maxNaRecords, na *candidates, int currentNaIndex, const int maxVoterRecords, voter *voters, int currentVoterIndex);
void constituencyDetails();

void constituencyDetails()
{
    const int maxNaRecords = 100;
    na *naCandidates = new na[maxNaRecords];
    int currentNaIndex = 0;
    readNACandidateFile(naCandidates, currentNaIndex, maxNaRecords);

    const int maxPaRecords = 100;
    pa *paCandidates = new pa[maxPaRecords];
    int currentPaIndex = 0;
    readPACandidateFile(paCandidates, currentPaIndex, maxPaRecords);

    const int maxVoterRecords = 100;
    voter *voters = new voter[maxVoterRecords];
    int currentVoterIndex = 0;
    readVoterFile(voters, currentVoterIndex, maxVoterRecords);

    int option;
    while (true)
    {
        cout << "\n1. National Constituency \n2. Provincial Constituency \n3. Back" << endl;
        cout << "\nEnter your option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "\n-------------------------------------------------------------------------------------------------" << endl
                 << "\t\t\t\t      National Constituency\n-------------------------------------------------------------------------------------------------" << endl;
            nationalConstituency(maxNaRecords, naCandidates, currentNaIndex, maxVoterRecords, voters, currentVoterIndex);
            break;
        case 2:
            cout << "\n--------------------------------------------------------------------------" << endl
                 << "\t\t\t Provincial Constituency\n--------------------------------------------------------------------------" << endl;
            pronvincialConstituency(maxPaRecords, paCandidates, currentPaIndex, maxVoterRecords, voters, currentVoterIndex);
            break;
        case 3:
            return;
        default:
            cout << "Invalid Option!";
            break;
        }
    }
}

void pronvincialConstituency(const int maxPaRecords, pa *paCandidates, int currentPaIndex, const int maxVoterRecords, voter *voters, int currentVoterIndex)
{
    int option;
    cout << "\n1. Punjab \n2. Khyber Pakhtunkhwa \n3. Sindh \n4. Balochistan \n5. Back" << endl;
    cout << "\nEnter your option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        displayProvinceDetails("Punjab", currentPaIndex, paCandidates, currentVoterIndex, voters);
        break;
    case 2:
        displayProvinceDetails("KPK", currentPaIndex, paCandidates, currentVoterIndex, voters);
        break;
    case 3:
        displayProvinceDetails("Sindh", currentPaIndex, paCandidates, currentVoterIndex, voters);
        break;
    case 4:
        displayProvinceDetails("Balochistan", currentPaIndex, paCandidates, currentVoterIndex, voters);
        break;
    case 5:
        return;
    default:
        cout << "Invalid Option!";
        break;
    }
}

void displayProvinceDetails(const string &province, int currentPaIndex, pa *paCandidates, int currentVoterIndex, voter *voters)
{
    cout << "\n--------------------------------------------------------------------------" << endl
         << "\t\t    Provincial Assembly Constituency\n--------------------------------------------------------------------------" << endl;
    int provinceCandidateCount = 0;
    int provinceVoterCount = 0;

    for (int i = 0; i < currentPaIndex; i++)
    {
        if (paCandidates[i].province == province)
        {
            provinceCandidateCount++;
        }
    }

    for (int i = 0; i < currentVoterIndex; i++)
    {
        if (voters[i].province == province)
        {
            provinceVoterCount++;
        }
    }

    cout << "\nProvince: " << province << endl;
    cout << "Number of PA Candidates: " << provinceCandidateCount << endl;
    cout << "Number of Voters: " << provinceVoterCount << endl
         << endl;
}

void nationalConstituency(const int maxNaRecords, na *candidates, int currentNaIndex, const int maxVoterRecords, voter *voters, int currentVoterIndex)
{
    const int TotalConstituencies = 272;
    int constituencyVoters[TotalConstituencies] = {0};
    int constituencyCandidates[TotalConstituencies] = {0};
    for (int i = 0; i < TotalConstituencies; i++)
    {
        for (int j = 0; j < currentVoterIndex; j++)
        {
            if (i + 1 == voters[j].na)
            {
                constituencyVoters[i]++;
            }
        }
    }
    for (int i = 0; i < TotalConstituencies; i++)
    {
        for (int j = 0; j < currentNaIndex; j++)
        {
            if (i + 1 == candidates[j].naNumber)
            {
                constituencyCandidates[i]++;
            }
        }
    }
    cout << "-------------------------------------------------------------------------------------------------" << setw(40) << left << "\nCONSTITUENCY NUMBER" << setw(40) << left << " NUMBER OF CANDIDATES"
         << " NUMBER OF VOTERS" << endl
         << "-------------------------------------------------------------------------------------------------" << endl
         << endl;
    for (int i = 0; i < TotalConstituencies; i++)
    {
        cout << setw(40) << left << i + 1 << setw(40) << left << constituencyCandidates[i] << setw(20) << left << constituencyVoters[i] << endl;
    }
    cout << "\n\nTotal Candidates: " << currentNaIndex << "\nTotal Voters: " << currentVoterIndex << endl;
}