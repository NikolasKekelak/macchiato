//
// Created by nikol on 12/4/2024.
//

#ifndef STAVOVATABULKA_H
#define STAVOVATABULKA_H


string usek();
string pointer_to_binary_function();
void analyzuj();
int next_stav();
int next_stav_mealy();


//sekne string s od indexu (start) po druhy index(end)
string usek(string s, int start, int end) {
    string ans;
    for(start; start<end; start++) ans+=s[start];
    return ans;
}
// int to binary_string
string to_binary(int num) {
    string ans="";
    while(num) {
        ans=(char)(num%2+'0')+ans;
        num/=2;
    }
    while(ans.size()!=length)
        ans='0'+ans;
    return ans;
}
//kebyze pridam co dostanem?
string next_stav(const string &main, const string &cast) {

    int max_zhoda=0;
    int zhoda=0;

    for(int i=1;i<= cast.size(); i++) {
        zhoda=0;
        string statics = usek(main, 0, i);
        string dynamic= usek(cast,cast.size()-i ,cast.size());
        if(statics==dynamic)
            zhoda=statics.size();

        max_zhoda=max(max_zhoda, zhoda);
    }

    return to_binary(max_zhoda);
}



//stavova tabulka , yes that easy
void analyzuj(const string &vstup , const string &type) {
    length= upper_power_of_two(vstup.size()+1);
    cout<<"TABULKA STAVOV:\n";

        for(int i=0; i<=vstup.size()-priority; i++) {
            cout<<to_binary(i)<<" | ";

            for(char c = '0'; c<='1'; c++) {
                int START = (priority? ((i==vstup.size()-1)? 1 : 0 ) : 0 ); // len pre zkratenie podmienok, neriesit, nemenit, funguje to

                cout<< next_stav(vstup, usek(vstup,START ,i)+c); // vypis stavu
                cout<<" | ";

                automat[priority][c+to_binary(i)]
                = next_stav(vstup, usek(vstup,START ,i)+c); // ulozi sa do mapy
            }
            cout<<"\""<<usek(vstup, 0 , i)<<"\"";
            cout<<"\n";
        }

    }
#endif //STAVOVATABULKA_H
