//
// Created by nikol on 12/4/2024.
//

#ifndef ESPRESSO_H
#define ESPRESSO_H

char reversebit(char vstup) {
    if(vstup=='0') return '1';
    else return '0';
}

void espresso_converter(const string &vstup, bool vypis, bool vystup ) {
    int l_stav = upper_power_of_two(vstup.size()+1);
    string jednotky="";
    int k=l_stav;
    while(k--)jednotky+="1";
    ofstream output ("vstup.txt");
    output<<".i "<<l_stav+1<<"\n";
    output<<".o "<<2*l_stav+1<<"\n";
    output<<".ilb X";
    for(int i=1; i<=l_stav; i++)
        output<<" z"<<i;
    output<<"\n";
    output<<".ob";
    for(int i=1; i<=l_stav; i++)
        output<<" J"<<i<<" K"<<i;
    output<<" Y\n.type fr\n.p "<<2*(vstup.size()+1)<<"\n";

    for(char c= '0'; c<='1'; c++ ) {
        for(int i=0; i<vstup.size()+1; i++) {
            string stav=to_binary(i);
            output<<c<<stav;
            output<<" ";
            string memory=next_stav(vstup, usek(vstup,0,i)+c);
            for(int j=0; j<l_stav; j++) {
                output<< ( (stav[j]=='1') ?  '-' : memory[j]) << ( (stav[j]=='0') ?  '-' : reversebit(memory[j]));
            }
            output<<((stav==jednotky)? "1" : "0");
            output<<" \n";
        }
    }


    output<<".e";
    output.close();
    if(vypis){
        ifstream input("vstup.txt");
        string input_string;
        cout<<"\n\nESPRESSO VSTUP";
        cout<<"\n\n";
        while (getline(input, input_string))
            cout<<input_string<<"\n";
    }
    if(vystup) {
        cout<<"\n\n";
        system("run_espresso.bat");
    }

}

#endif //ESPRESSO_H
