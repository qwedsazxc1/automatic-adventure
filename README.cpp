#include<iostream>       //定積分計算機
#include<cmath>
using namespace std;
int main(){
int int_array_a[5]={};//分子陣列，記得改名字
int int_array_b[5]={};//分母陣列，記得改名字
int int_c,int_d;//積分上下限，記得改名字
cout<<"輸入順序，上限->下限->四次方分子->分母(若為整數則填1)"<<endl;
while(cin>>int_c>>int_d){
  for(int i=0;i<5;i++){
    cin>>int_array_a[i]>>int_array_b[i];
  }
  for(int i=0;i<5;i++){
    int_array_b[i]*(5-i);//求不定積分的分母
    
}
}
  return 0;
}
