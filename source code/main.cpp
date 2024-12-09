
#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>


using namespace std;


int upper_power_of_two(const unsigned long long n) {
    unsigned long long i=0;
    while( !( pow(2, i) <n && n<=pow(2, i+1) ) ) i++;
    return i+1 ;
}

map<string, string> automat[2];
int priority;
int length;

#include "stavovatabulka.h"
#include "karnafove_vypis.h"
#include "karnafove_generacia.h"
#include "espresso.h"

map<string, string> modify_map_values(const map<string, string> &mp , int numb, char type)   //type J alebo K
{
    map<string, string> ans;

    for( const auto &i : mp) {
        if(type=='J') {
            ans[i.first] = i.second[numb-1] ;
            if(i.first[numb] == '1')
            ans[i.first] = "-";
        }
        else {
            ans[i.first] = '-';
            if(i.first[numb] == '1')
                ans[i.first] = reversebit(i.second[numb-1] );
        }
    }

    return ans;
}

void karnaughove(const string &vstup) {

    int l_stav=upper_power_of_two(vstup.size()+1);
    cout<<"\n\nKARNAUGHOVE MAPY";

    cout<<"\n";
    for(int i=0; i< l_stav; i++)
        cout<<"D"<<i+1<<", ";
    cout<<"\n";

    karnaughova_basic(vstup, automat[priority]);
    for(int i = 1 ; i<=l_stav; i++) {
        cout<<"\nJ"<<i<<"\n";
        karnaughova_basic(vstup, modify_map_values(automat[priority], i, 'J'));
        cout<<"\nK"<<i<<"\n";
        karnaughova_basic(vstup, modify_map_values(automat[priority], i, 'k'));
    }
}


int main() {


    cout<<"Typ automatu: Moore[0] / Mealy[1]  ->";
    cin>> priority;

    cout<<" \n Zadaj postupnost pre automat -> ";
    string vstup;
    cin>>vstup;

    cout<<"\n";
    analyzuj(vstup, "moore");
    cout<<"\n\n Chces karnaughove mapy? (1/0)->";
    bool karnaf;
    cin>>karnaf;
    if(karnaf)
    karnaughove(vstup);

    cout << (" \n Espresso vstupny subor? (1/0) -> ");
    bool zapis;
    cin>>zapis;

    if(zapis) {
        espresso_converter(vstup, true, false);
    }
    cout<<" \n Espresso vystupny subor?  (1/0) -> ";
    cin>>zapis;
    if(zapis) {
        espresso_converter(vstup, false, true);
    }

    automat[0].clear();
    automat[1].clear();

    return 0;
}