#include <bits/stdc++.h>
using namespace std;

string delta(1,235);
string aps(1,238);

string makePDA( string state1 , string input , string topStack , string state2 , string newTopStack )
{
    string pda;
    pda = delta + "(" + state1 + "," + input + "," + topStack + ") -> {(" + state2 + "," + newTopStack + ")}";
    return pda;
}
void print(vector <string> &x , string what)
{
    cout << "_______________________________"+ what +"__________________________________" << endl;
    for (int i = 0; i < x.size(); ++i)
    {
        cout << x[i] << endl;
    }
    cout << "_____________________________________________________________________" << endl << endl;
}

void pda_to_cfg(string state1 , string input , string topStack , string state2 , string newTopStack , vector <string> &cfg , set<string> &states)
{
    set <string> :: iterator it1;
    set <string> :: iterator it2;

    if( newTopStack.length() == 2 )
    {
        for (it1 = states.begin(); it1 != states.end() ; ++it1)
        {
            for (it2 = states.begin(); it2 != states.end() ; ++it2)
            {
                cfg.push_back( "[ " + state1 + topStack + *it1 + " ]  ->  " + input + " [ " + state2 + newTopStack[0] + *it2 + " ] [ " + *it2 + newTopStack[1] + *it1 + " ] " );
            }
        }
    }
    else    // length is 1
    {
        for (it2 = states.begin(); it2 != states.end() ; ++it2)
        {
            string ss = "[ " + state1 + topStack + *it2 + " ]  ->  " + input;
            if( newTopStack.compare(aps) != 0 )
            {
                ss = ss + " [ " + state2 + newTopStack + *it2 + " ]" ;
            }
            cfg.push_back( ss );
        }
    }
}
void pda_to_cfg_states(vector <string> &cfg , set <string> &states)
{
    set <string> :: iterator it1;
    set <string> :: iterator it2;

    for (it1 = states.begin(); it1 != states.end() ; ++it1)
    {
        for (it2 = states.begin(); it2 != states.end() ; ++it2)
        {
            cfg.push_back( "[ " + *it1 + "Z" + *it2 + " ]  ->  " + aps );
        }
    }
}
void getInput(vector <string> &pda ,vector <string> &state1 ,vector <string> &input ,vector <string> &topStack ,vector <string> &state2 ,vector <string> &newTopStack , set<string> &states )
{
    string line;
    ifstream fin;
    fin.open("input/input1.txt");
    while (fin)
    {
        getline(fin, line);
        if( fin )
        {
            cout << line << endl;
            vector <string> tokens;
            stringstream check1(line);
            string intermediate;
            while(getline(check1, intermediate, ' '))
            {
                if( intermediate.compare("$") == 0 )
                {
                    tokens.push_back(aps);
                }
                else
                {
                    tokens.push_back(intermediate);
                }
            }

            state1.push_back(tokens[0]);
            input.push_back(tokens[1]);
            topStack.push_back(tokens[2]);
            state2.push_back(tokens[3]);
            newTopStack.push_back(tokens[4]);

            pda.push_back(makePDA(tokens[0],tokens[1],tokens[2],tokens[3],tokens[4]));

            states.insert(tokens[0]);
            states.insert(tokens[3]);
        }
    }
    fin.close();
}
void putOutput(vector <string> &cfg)
{
    ofstream fout;
    fout.open("output/output1.txt");
    for (int i = 0; i < cfg.size(); ++i)
    {
        fout << cfg[i] << endl;
    }
    fout.close();
}

int main()
{

    vector <string> cfg;
    vector <string> pda;
    vector <string> state1;
    vector <string> input;
    vector <string> topStack;
    vector <string> state2;
    vector <string> newTopStack;
    set <string> states;

    string structure = makePDA("state1" , "input" , "topStack" , "state2" , "newTopStack");
    cout << structure << endl;
    pda.push_back(structure);

    getInput(pda,state1,input,topStack,state2,newTopStack,states);
    print(pda,"PDA");
    for (int i = 0; i < input.size(); ++i)
    {
        pda_to_cfg(state1[i] , input[i] , topStack[i] , state2[i] , newTopStack[i] , cfg , states );
    }
    pda_to_cfg_states(cfg,states);

    print(cfg,"CFG");
    putOutput(cfg);

    return 0;
}
