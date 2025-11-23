#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<int> Row;

int main()
{

    int n = 5, m = 3; // 5 processes, 3 resources

    vector<Row> allocation(n, Row(m));
    vector<Row> maxm(n, Row(m));
    vector<Row> need(n, Row(m));
    Row available(m);

    ifstream file("input.txt");
    if (!file.is_open())
    {
        cerr << "Cannot open input.txt\n";
        return 1;
    }

    // Read Available
    for (int j = 0; j < m; j++)
        file >> available[j];

    // Read Allocation
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            file >> allocation[i][j];

    // Read Max
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            file >> maxm[i][j];

    // Compute Need
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - allocation[i][j];

    vector<bool> finish(n, false);
    vector<int> safe_seq;
    vector<int> work = available;

    // Here it is Banker's Algorithm
    for (int count = 0; count < n; count++)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool ok = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    safe_seq.push_back(i);
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    // Output for  Available
    cout << "Available: ";
    for (int j = 0; j < m; j++)
        cout << available[j] << " ";
    cout << "\n";

    // Check weather it is safe
    bool safe = true;
    for (int i = 0; i < n; i++)
        if (!finish[i])
            safe = false;

    if (safe)
    {
        cout << "System is SAFE.\nSafe Sequence: ";
        for (int i = 0; i < safe_seq.size(); i++)
        {
            cout << "P" << safe_seq[i];
            if (i + 1 < safe_seq.size())
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "System is NOT safe.\n";
    }

    return 0;
}
