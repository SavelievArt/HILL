#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
using namespace std;

string SetKeys(const char* file);
string SetMsg(const char* file);

class hill
{
private:
        vector <string> keys;
        string msg, key_;
        string alph = Set_Alph();
	int *enc;
	int **key, **vec, **enc_msg;
	int size_;
	int rows;
        
	char Get_Char(int num);
	int Key_Size(string key);
	int Get_Num(char sym);
	int **To_Number(string str, int rows, int col);
        int Det(int **matr, int n);
        int Inverse(int a, int n);
        int Mod(int n, int mod);
        void Print(int **mas, int rows, int col);
        void Free_Mem(int **matr, int n);
        void Print(int **matr, int n);
        void Transpose_Mtx(int **matr, int **tMatr, int n);
        void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol);
        void Extended_Euclid(int a, int b, int *x, int *y, int *d);
        void Print_txt(int **matr, int rows, int col, const char *file);
        void Print_txt(int **matr, int rows, int col);
        string Extend_Msg(string msg);
        string Set_Alph();
public:
	hill(string a, string b);
	void Encrypt();
        void Dechiper();
};
