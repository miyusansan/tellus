#include <cmath>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
using namespace std;
double calculate_inverseerfc_small(double ber);
double calculate_throughput(double cnr);

//衛星環境に合わせてパラメータを調整する必要がある
//パラメータ:最後cnrを何乗するか、berの係数(論文では2)
int main() {
  double ber =  2*pow(10,-5);//2*P
  double cnr = 0;//sqrt(CNR)
  int N = 1000;
  double c[N];
  for(int k=0;k<N;k++){
    if(k==0) c[0] = 1;
    else c[k] = 0;
  }
  
  for(int k=0;k<N;k++){
    for(int m=0;m<k;m++){
      c[k] = c[k] + (c[m]*c[k-1-m])/((m+1)*(2*m+1));
    }
    cnr = cnr + c[k]*pow(sqrt(M_PI)*(1-ber)/2,2*k+1)/(2*k+1);
  }
  cout << "cnr1: " << cnr*cnr << endl;

  cnr = calculate_inverseerfc_small(ber);
  cout << "cnr2: " << cnr*cnr << endl;

  double throughput = calculate_throughput(cnr*cnr);
  cout << "BER: " << ber << "   throughput: " << throughput << endl;
  return 0;
}
//前提：f(x)+g(x)=1 , g^-1(x)がわかっている
//y=g(x)=>g^-1(y)=x , z=f(x)=>f^-1(z)=x , y+z=1
//x=f^-1(z)=g^-1(y)=g^-1(1-z) => f^-1(x)=g^-1(1-x)
//cnr<2くらいまでは精度が良い
//それより大きくなると精度が悪くなるので、BERの値に応じて近似式を使い分ける
//   x=0付近では以下のlogを使った方法を使う

double calculate_inverseerfc_small(double ber)
{
    double cnr = 0;
    cnr = sqrt( (log(2/M_PI)-2*log(ber)-log(log(2)-log(M_PI)-2*log(ber)))/2 );

    return cnr;
}

//TO DO : CN比からスループットを求める
// C=Wlog_2(1+CNR)
// Wは周波数帯域幅->UWBは数MHz～数百MHz
double calculate_throughput(double cnr)
{
  double W = pow(10,7);
  return W*log2(1+cnr);
}
