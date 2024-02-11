#include "constituency.h"

int main()
{
    int option;
    while (true)
    {
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tVOTING MANAGEMENT SYSTEM\n--------------------------------------------------------------------------" << endl;
        cout << "1. Voters Record \n2. Candidates Record \n3. Constituency Details \n4. Exit \n"
             << endl;
        cout << "\nEnter your option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "\n--------------------------------------------------------------------------" << endl
                 << "\t\t\t      Voters Record\n--------------------------------------------------------------------------" << endl;
            voterRecord();
            break;
        case 2:
            cout << "\n--------------------------------------------------------------------------" << endl
                 << "\t\t\t    Candidates Record\n--------------------------------------------------------------------------" << endl;
            cout << "\n1. National Assembly Candidates \n2. Provincial Assembly Candidates \n3. Back" << endl;
            cout << "\nEnter your option: ";
            cin >> option;
            switch (option)
            {
            case 1:
                cout << "\n--------------------------------------------------------------------------" << endl
                     << "\t\t\tNational Assembly Candidates\n--------------------------------------------------------------------------" << endl;
                naCandidateRecord();
                break;
            case 2:
                cout << "\n--------------------------------------------------------------------------" << endl
                     << "\t\t\tProvincial Assembly Candidates\n--------------------------------------------------------------------------" << endl;
                paCandidateRecord();
                break;

            case 3:
                main();
                break;

            default:
                cout << "Invalid Option!";
                break;
            }
            break;
        case 3:
            cout << "\n--------------------------------------------------------------------------" << endl
                 << "\t\t\tConstituency Details\n--------------------------------------------------------------------------" << endl;
                 constituencyDetails();
            break;
        case 4:
            cout << "Program Terminated!";
            exit(0);
        default:
            cout << "Invalid Option!";
            break;
        }
    }
    return 0;
}