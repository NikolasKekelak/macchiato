

#ifndef KARNAFOVE_GENERACIA_H
#define KARNAFOVE_GENERACIA_H


void opakuj(const  int length ,const string name){
     for(int i=0; i<length ; i ++ ){
        cout<< name[i%name.size()];
     }
}

vector<bool> expand(vector<bool> domain){
    vector<bool> ans;
    for(auto i : domain)
        ans.push_back(i);
    reverse(domain.begin(), domain.end());
    for(auto i : domain)
        ans.push_back(i);
    return ans;
}

class STAVOVA{
    public:
      char os; //x alebo y
      string name; // Pomenovanie
      vector<bool> domain; // posobisko premennej
      int ocislenie;

      STAVOVA(const string &p_name , const vector<bool> &p_domain){
          name=p_name;
          domain=p_domain;
      }

      char get_os(){
          return os;
      }
      void new_domain() {
           domain=expand(domain);
      }
      void vypis_x(int i){ //vodorovne
            if(domain[i]) cout<<setw(3)<<name;
            else cout<<"   ";
      }

      void vypis_y(int length){ //zvislo
           for(int i = 0 ; i< domain.size() ; i++ )
             {
                cout<<"   ";
                if(domain[i]) opakuj(length, name+"_");
                    else
                opakuj(length, " ");
             }
           cout<<"\n";
      }

};

vector<bool> create_domain(int size)
{
    vector<bool> domain;
    for(int i=0; i<size/2; i++ )
        domain.push_back(false);
    for(int i=0; i<size/2; i++ )
        domain.push_back(true);
    return domain;
}

string find_stav( const string &finding , const vector<STAVOVA> &stavove_y, const vector<STAVOVA> &stavove_x, int x, int y ){
      for(auto i : stavove_y ){
          if(i.name==finding)
            return (i.domain[y])? "1" : "0" ;
      }
      for(auto i : stavove_x ){
        if(i.name==finding)
            return (i.domain[x])? "1" : "0";
      }
}

string current(vector<STAVOVA> stavove_y, vector<STAVOVA> stavove_x, int x, int y){
    string ans="";
    reverse(stavove_y.begin(), stavove_y.end());
    reverse(stavove_x.begin(), stavove_x.end());
    int size = (stavove_y.size()+stavove_x.size())-1;
    ans+=find_stav("X",stavove_y, stavove_x,x,y) ;
    for(int i = 1; i<=size; i++)
        ans+=find_stav("Z"+to_string(i),stavove_y, stavove_x,x,y) ;
    return ans;
}

void karnaughova_basic(const string &vstup, map<string , string> mp){

     int pocet_premmenych = upper_power_of_two(vstup.size()+1)+1;

     int name_it=0;
     vector<string> names;
     for(int i=1; i<=pocet_premmenych-1;i++)
         names.push_back("Z" + to_string(i) );

     names.emplace_back("X");
     vector<STAVOVA> stavove_y;
     vector<STAVOVA> stavove_x;

     STAVOVA starter(names[name_it++], {0,1} );
     stavove_x.push_back(starter);

     int x=2;
     int y=1;

     if(pocet_premmenych>=2) {
         y*=2;
         for(auto &i : stavove_y )
             i.new_domain();
         STAVOVA add(names[name_it++], create_domain(y));
         stavove_y.push_back(add);
     }
     if(pocet_premmenych>=3) {
         y*=2;
         for(auto &i : stavove_y )
             i.new_domain();
         STAVOVA add(names[name_it++], create_domain(y));
         stavove_y.push_back(add);
     }


   for(int i = 4; i<=pocet_premmenych ; i++) {
       if(i%2 == 1) {
           y*=2;
           for(auto &k : stavove_y )
               k.new_domain();
           STAVOVA add(names[name_it++], create_domain(y));
           stavove_y.push_back(add);
       }
       else
       {
           x*=2;
           for(auto &l : stavove_x )
               l.new_domain();
           STAVOVA add(names[name_it++], create_domain(x));
           stavove_x.push_back(add);
       }
   }

    reverse(stavove_y.begin(), stavove_y.end());
    reverse(stavove_x.begin(), stavove_x.end());

    for(auto i : stavove_y) {
        opakuj(2*(stavove_x.size()+1), " ");
        i.vypis_y(pocet_premmenych- 1);
    }


   for(int i =0 ; i < x; i++ ) {
       for(auto k : stavove_x) {
           k.vypis_x(i);
       }
       for(int j=0; j<y ; j++) {
           cout<<" | ";
           string mem="";
           string now = current(stavove_y,stavove_x,i,j);
           if(mp.find(now)!= mp.end())
           cout<<setw(pocet_premmenych-1)<<mp[now];
                else
           cout<<setw(pocet_premmenych-1)<<"-";


       }
       cout<<" |\n";
   }

}

#endif //KARNAFOVE_GENERACIA_H
