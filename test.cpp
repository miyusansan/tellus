#include <cmath>
#include <iostream>
#include <limits>
#include <time.h>
using namespace std;
double calculate_inverseerfc_big(double ber);
double calculate_inverseerfc_small(double ber);
double calculate_throughput(double cnr);

//衛星環境に合わせてパラメータを調整する必要がある
//パラメータ:最後cnrを何乗するか、berの係数(論文では2)
int main(int argc, char* argv[]) {

  clock_t start = clock();
  double ber =  2*pow(10,-1*atoi(argv[1]));//2*P
  double cnr = 0;
  if(ber < 1 && ber>0.5)
<<<<<<< HEAD:spacecraftWirelessInterCommunication/calculateErfInv.cpp
  {
    cnr = calculate_inverseerfc_big(ber);
  }
  else if (0 < ber && ber <= 0.5)
  {
    cnr = calculate_inverseerfc_small(ber);
  }
=======
    {
      cnr = calculate_inverseerfc_big(ber);
    }
  else if (0 < ber && ber <= 0.5)
    {
      cnr = calculate_inverseerfc_small(ber);
    }
>>>>>>> origin/master:spaceWirelessInterComm/calculateErfcInv.cpp
  cout << "cnr: " << cnr*cnr << endl;

  double throughput = calculate_throughput(cnr*cnr);
  cout << "BER: " << ber << "   throughput: " << throughput << endl;

  clock_t end = clock();
  cout << (double)(end-start)/CLOCKS_PER_SEC*1000.0 << " [ms] " << endl;
  return 0;
}

double calculate_inverseerfc_big(double ber)
{
  int N = 100;
  double c[N];
  double cnr = 0;
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

  return cnr;
}
//前提：f(x)+g(x)=1 , g^-1(x)がわかっている
//y=g(x)=>g^-1(y)=x , z=f(x)=>f^-1(z)=x , y+z=1
//x=f^-1(z)=g^-1(y)=g^-1(1-z) => f^-1(x)=g^-1(1-x)
//cnr<2くらいまでは精度が良い
//それより大きくなると精度が悪くなるので、BERの値に応じて近似式を使い分ける
//   x=0付近では以下のlogを使った方法を使う
// https://pdfs.semanticscholar.org/7ded/4d4d5e7cf5de00bfff38e8710c2a79cf5210.pdf?_ga=2.207917074.1894478943.1602209379-1472185907.1595507135

/*論文の方法*/
double calculate_inverseerfc_small(double ber)
{
<<<<<<< HEAD:spacecraftWirelessInterCommunication/calculateErfInv.cpp
    double cnr = 0;
    ber = -log(sqrt(M_PI)*ber);
    cnr = ber-log(ber)/2+(log(ber)/4-1/2)/ber;
    cnr = sqrt(cnr);
    return cnr;
=======
  double cnr = 0;
  ber = -log(sqrt(M_PI)*ber);
  cnr = ber-log(ber)/2+(log(ber)/4-1/2)/ber;
  cnr = sqrt(cnr);
  return cnr;
>>>>>>> origin/master:spaceWirelessInterComm/calculateErfcInv.cpp
}

//CN比から伝送速度を求める
// C=Wlog_2(1+CNR)
// Wは周波数帯域幅->UWBは数MHz～数百MHz
double calculate_throughput(double cnr)
{
  double W = pow(10,7);
  return W*log2(1+cnr);
}
