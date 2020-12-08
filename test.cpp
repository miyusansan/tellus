#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
int main(){

  /*スケジュールの読み込み*/
  int repro_schedule,counter;
  string funcname;
  int reproid;
  vector< vector<string> > fname(64);
  vector< vector<int> > reproID(64);
  ifstream ifs_schedule("schedule.txt");
  string s;
  while( getline(ifs_schedule, s, ';') ){
//  while(ifs_schedule >> counter >> funcname >> reproid){
    counter = s;
    funcname = s;
    reproid = s;
    fname[counter].push_back(funcname);
    reproID[counter].push_back(reproid);
  }
  ifs_schedule.close();

  printf("ERR No.1:実行された関数がスケジュールにない\n");
  printf("ERR No.2:スケジュールされた関数が実行されていない\n");

  /*テストログの読み込み*/
  ifstream ifs_log("testlog.txt");
  string line;
  int countNum_log = -1;
  int repro_log = 0;
  while(getline(ifs_log,line)){
    stringstream linestream(line);
    vector<string> str;
    string s;
    while(getline(linestream,s,' ') ){
      str.push_back(s);
    }
      string str1;
    if(str[0].length()>3) str1 = str[0].substr(str[0].length()-3);
    string str2 = str[0].substr(0,1);

    if(str1 == "cas"){/*カウントとIDの読み取り*/
      /*前回のERR No.2の判断(初めの行以外)*/
      if(countNum_log != -1){
        for(int i=0;i<fname[countNum_log].size();i++){
          if(fname[countNum_log][i]!="0"){
            printf("ERR No.2 : %s\n",fname[countNum_log][i].c_str());
          }
        }
      }

      printf("%s\n",str[0].c_str());
      countNum_log = atoi(str[1].c_str());
      repro_log = atoi(str[2].c_str());

    } else if(str2 == ">"){/*実行関数読み取り*/
      int flg = 0;
      for(int i=0;i<fname[countNum_log].size();i++){
	if(str[1] == fname[countNum_log][i] && repro_log != reproID[countNum_log][i]){
	  flg = 1;
	  fname[countNum_log][i] = "0";
	}
      }
      if(flg==0){
	printf("ERR No.1 : %s\n",str[1].c_str());
        for(int i=0;i<fname[countNum_log].size();i++){
          if(str[1] == fname[countNum_log][i]){//再プロID                       
            fname[countNum_log][i] = "0";
          }
        }
      }
    }
  }//while                                                                      
  ifs_log.close();
  return 0;
}

/*
スケジュールtxt化用のVBA
Sub makeScheduleTxt()

Dim f() As Variant
ReDim f(70, 64)
Dim id() As Variant
ReDim id(70, 64)

Dim i As Long
Dim j As Long
For i = 0 To 69
    For j = 0 To 63
        If Worksheets("Sheet1").Cells(i, j) = "●" Then
	    f(i, j) = Worksheets("Sheet1").Cells(i, 3)
	    id(i, j) = Worksheets("Sheet1").Cells(i, 1)
	Else
	    f(i, j) = 0
	    id(i, j) = 0
	End If
    Next
Next
Open "./schedule.txt" For Output As #1
For j = 0 To 63
    For i = 0 To 69
        If f(i, j) <> 0 Then
	    Print #1, j & " " & f(i, j) & " " & id(i, j)
	End If
    Next
Next

Close #1

End Sub


*/
