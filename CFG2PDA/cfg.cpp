#include <bits/stdc++.h>
using namespace std;

string delta(1,235);
string aps(1,238);
void getInput(vector <string> &s , set<string> &terminals )
{
    string line;
    ifstream fin;
    fin.open("input/input1.txt");
    while (fin)
    {
        getline(fin, line);
        if(fin)
        {
            s.push_back(line);

            for (int j = 0; j < line.length() ; ++j)
            {
                if( line[j] >= 97 && line[j] <= 122 )
                {
                    string ss(1,line[j]);
                    terminals.insert(ss);
                }
            }
        }

    }
    fin.close();
}
void cfg_to_pda(string s)
{
    vector <string> tokens;
    stringstream check1(s);
    string intermediate;
    while(getline(check1, intermediate, ':'))
    {
        tokens.push_back(intermediate);
    }
    vector<string> production;

    stringstream check2(tokens[1]);
    while(getline(check2 , intermediate , '|'))
    {
        production.push_back(intermediate);
    }
    string ans = delta + "(q," + aps + "," + tokens[0] + ") -> {";
    for (int i = 0; i < production.size() ; ++i)
    {
        string ss = "(q," + production[i] + ")";
        ans = ans + ss;
        if( i+1 < production.size() )
        {
            ans = ans + ",";
        }
    }
    ans = ans + "}";
    cout << ans << endl;
}
void cfg_to_pda_terminals( set <string> &terminals )
{
    set <string> :: iterator it;
    for (it = terminals.begin(); it != terminals.end(); ++it)
    {
        string ans = delta + "(q," + *it + "," + *it + ") -> {(q," + aps + ")}" ;
        cout << ans << endl;
    }
}

int main()
{

    vector <string> s;
    set <string> terminals;

    getInput(s,terminals);

    cout << "________________________CFG________________________" <<endl;
    for (int i = 0; i < s.size(); ++i)
    {
        cout << s[i] << endl;
    }
    cout << "___________________________________________________" <<endl<<endl;

    cout << "________________________PDA________________________" << endl;
    for (int i = 0; i < s.size(); ++i)
    {
        cfg_to_pda(s[i]);
    }
    cfg_to_pda_terminals(terminals);
    cout << "___________________________________________________" << endl;
    return 0;
}
