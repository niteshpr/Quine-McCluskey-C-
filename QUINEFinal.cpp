#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long int
#define mp(x,y) make_pair(x,y)
#define pb(m) push_back(m)


class quinMC
{
public:

ll VARI;

  quinMC(ll a)
  {
   VARI=a;
  }


//function to get the boolean term letters
vector<string> getletters()
{
   vector<string> v;
   string letters[]={"A","B","C","D","E","F","G","H","I","J","K","L"};
   rep(i,0,this->VARI)
    v.pb(letters[i]);
   return v;
}

/*function to convert decimal to binary*/
string decToBin(ll n)
{
   if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}


//function to pad zeros to the binary equivalent of digits.

string pad(string bin)
{
   ll max=VARI-bin.length();
   rep(i,0,max)
       bin="0"+bin;
   return bin;
}


//function to check if two terms differ by just one bit
bool isGreyCode(string a,string b)
{
   ll flag=0;
   rep(i,0,a.size())
   {
       if(a[i]!=b[i])
        flag++;
   }
   return (flag==1);
}


//function to replace complement terms with '-'
int setbit(string s)
{
  int n=0;
  rep(i,0,s.size())
  {
    if(s.at(i)=='1')
      {
        n++;
      }
  }
  return n;
}
string replace_complements(string a,string b)
{
   string temp="";
   rep(i,0,a.size())
   if(a[i]!=b[i])
       temp=temp+"-";
   else
       temp=temp+a[i];

   return temp;
}

//function to check if string b exists in vector a
bool in_vector(vector<string> a,string b)
{
   rep(i,0,a.size())
     if(a[i].compare(b)==0)
      return true;
    return false;
}

//function to reduce minterms
vector<string> reduce(vector<string> minterms)
{

      vector<string> newminterms;

      int max=minterms.size();
      int checked[max]={0};
      rep(i,0,max)
      {
          rep(j,i,max)
          {
               //If a grey code pair is found, replace the differing bits with don't cares.
               if(isGreyCode(minterms[i],minterms[j]))
               {
                  checked[i]=1;
                  checked[j]=1;
                  if(!in_vector(newminterms,replace_complements(minterms[i],minterms[j])))
                     newminterms.push_back(replace_complements(minterms[i],minterms[j]));
               }
          }
      }

      //appending all reduced terms to a new vector
      rep(i,0,max)
      {
          //cout<<checked[i]<<endl;
          if(checked[i]!=1 && ! in_vector(newminterms,minterms[i]))
           newminterms.push_back(minterms[i]);
      }

       return newminterms;
}


//Converting the boolean minterm into the variables
// Eg: 011- becomes a'bc
string getValue(string a)
{
   string temp="";
   vector<string> vars=this->getletters();

   rep(i,0,a.size())
   {
     if(a[i]!='-')
     {
        if(a[i]=='0')
         temp=temp+vars[i]+"\'";
        else
         temp=temp+vars[i];
     }
   }
   return temp;
}
int bin2d(string s)
{
  int l=s.size();
  int n=0,x=0;
for(int i=l-1;i>=0;i--)
  {
    n=n+((s[i]-'0')<<(x));
    x++;
  }
  return n;
}


//function to check if 2 vectors are equal
bool VectorsEqual(vector<string> a,vector<string> b)
{
   if(a.size()!=b.size())
      return false;

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
   rep(i,0,a.size())
    {
        if(a[i]!=b[i])
        return false;
    }
    return true;
}

};

//Main function
int main ()
{
   char check='y';
   while(check=='y')
   {
      int no;
      cout<<endl<<"Enter the number of variables:"<<endl;
      cin>>no;
      if(no > 10 || no < 1)
      {
          cout << "Invalid number of variables (1-8)" << endl;
          continue;
      }
      quinMC q(no);

      string temp="";
      cout<<"Enter the minterms(RANGE=0-"<<pow(2,no)-1<<") separated by comma(,) and followed by ')' :"<<endl;
      cout<<"F(";
      vector<string> sr=q.getletters();
      rep(i,0,no-1) cout<<sr[i]<<",";
      cout<<sr[no-1];
      cout<<") = Σ (";
      cin>>temp;
      cout<<"\n\n*********************************************************\n\n";


      vector<string> minterms;
      vector<string> gr;

      rep(i,0,temp.size()-1){
        string s;
          while(temp.at(i)!=',' && i<temp.size()-1)
            s+=temp.at(i++);

         int t=atoi(s.data());
         minterms.push_back(q.pad(q.decToBin(t)));
      }


      sort(minterms.begin(),minterms.end());
      map<int,vector<pair<int,string>>> m;

      rep(i,0,minterms.size())
      {
        m[q.setbit(minterms[i])].pb(mp(q.bin2d(minterms[i]),minterms[i]));
      }


      cout<<"\nGROUPING ON BASIS OF SET BITS :\n----------------------------------------------\n\n";
      for(auto i : m)
      {
            cout<<"------------------\n";
          rep(j,0,i.second.size())
            {
                        cout<<i.second[j].first<<"\t"<<i.second[j].second<<"\n";
            }
            cout<<"------------------\n";
      }

      cout<<"\n\n\n*********************\nON REDUCING :\n";
      do
      {
         minterms=q.reduce(minterms);
         sort(minterms.begin(),minterms.end());

         cout<<"\n******************\n";
         for (int i=0; i<minterms.size(); i++)
              cout << minterms[i]<<endl;
              cout <<endl;
        cout<<"******************\n";

      }while((!q.VectorsEqual(minterms,q.reduce(minterms))) and (printf("FURTHER REDUCTION : \n")));


      int i;
      cout << "\n\nThe reduced boolean expression in SOP form:\n--------------------------------------------------" << endl;
      for (i=0;i<minterms.size()-1; i++)
          cout <<q.getValue(minterms[i])<<"+";
      cout<<q.getValue(minterms[i])<<endl;

      cout<<"---------------------------------------------------\n";
      cout<<"Would you like to enter another expression? (y/n)"<<endl;
      cin>>check;
   }
   cout<<endl<<"---END--"<<endl<<"Created by Nitesh"<<endl;
}
