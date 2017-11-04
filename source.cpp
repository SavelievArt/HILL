#include "header.h"
//получение буквы по номеру из алфавита
char hill::Get_Char(int num)
{
    return hill::alph[num];
}

int hill::Key_Size(string key)
{
    return ceil(sqrt(key.length()));
}
//дополнение сообщеия
string hill::Extend_Msg(string msg)
{
    while (msg.length() % size_ != 0)
	msg += '.';
    return msg;
}
//получение номера символа по букве
int hill::Get_Num(char symbol)
{
    for (int i = 0; i < alph.length(); i++)
    {
        if (symbol == alph[i])
            return i;
    }
    return 0;
}
//перевод из букв в цифры
int **hill::To_Number(string str, int rows, int col)
{
    int **mas = new int*[rows];
    for (int i = 0; i < rows; i++)
	mas[i] = new int[col];
    int counter = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
	{
            if (counter >= str.length())
		mas[i][j] = 1;
            else
		mas[i][j] = Get_Num(str[counter]);
            counter++;
	}
    }
    return mas;
}

void hill::Print(int **mas, int rows, int col)
{
    for (int i = 0; i < rows; i++)
    {
	for (int j = 0; j < col; j++)
            cout << mas[i][j] << " ";
	cout << endl;
    }
}
 
//функция печати матрицы
void hill::Print(int **mas, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << mas[i][j] << " ";
        cout << endl; 
    }
}

void hill::Print_txt(int** matr, int rows, int col, const char* file)
{
    ofstream fout(file);
    int symbol = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < col; j++)
        {
            fout << Get_Char(matr[i][j]);
            symbol++;
        }
}

void hill::Print_txt(int** matr, int rows, int col)
{
    int symbol = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < col; j++)
        {
            cout << Get_Char(matr[i][j]);
            symbol++;
        }
    
}
//заполнение алфавита
string hill::Set_Alph()
{
    string str;
    for(int i = 0; i < 128; i++)
    {
        str += (char)i;
    }
    //str += (char)10;
    //str += (char)13;
    cout << "\nAlph :\n";
    cout << str << endl;
    return str;
}

hill::hill(string MyMessage, string MyKey)
{
    key_ = MyKey;
    size_ = Key_Size(key_);
    cout << "\nKey Matrix:" << endl;
    key = To_Number(key_, size_, size_);
    Print(key, size_, size_);
    cout << "\nExtended Message : ";
    msg = Extend_Msg(MyMessage);
    cout << msg << endl;
    rows = ceil(msg.length() / size_);
    vec = To_Number(msg, rows, size_);//перевод сообщения в численные вектора
    enc = new int[msg.size()];
}
//шифрование
void hill::Encrypt()
{
    int **res = new int*[rows];
    for (int i = 0; i < rows; i++)
	res[i] = new int[size_];
        
    for (int i = 0; i < rows; i++)
	for (int j = 0; j < size_; j++)
            res[i][j] = 0;
    
    //vector production
    
    for (int g = 0; g < rows; g++)
        for (int i = 0; i < size_; i++)
            for (int j = 0; j < size_; j++)
            {
                res[g][i] += key[i][j] * vec[g][j];
                res[g][i] = res[g][i] % alph.length();
            }
    
    Print(res, rows, size_);
    cout << "Encrypted message: ";
    Print_txt(res, rows, size_);
    Print_txt(res, rows, size_, "enc_msg.txt");
    Free_Mem(res, rows);
}

void hill::Dechiper()
{
    int det;
    int **matr = new int * [size_];
    int **obr_matr = new int * [size_];//обратная матрица ключа
    int **tobr_matr = new int * [size_];// транспонированная обратная матрица ключа
    for(int i = 0; i < size_; i++){
        matr[i] = new int[size_];
        obr_matr[i] = new int[size_];
        tobr_matr[i] = new int[size_];
    }
    for(int i = 0; i < size_; i++)
        for(int j = 0;j < size_; j++)
            matr[i][j] = key[i][j];
    cout << "\nKey matrix : " << endl;
    Print(matr, size_);
    cout << endl;
    det = Det(matr, size_);
    det = Inverse(Mod(det, hill::alph.length()), hill::alph.length());
    cout << "Определитель матрицы = " << det << endl;
    if(det){
        for(int i = 0; i < size_; i++){
            for(int j = 0; j < size_; j++){
                int m = size_ - 1;
                int **temp_matr = new int * [m];
                for(int k = 0; k < m; k++)
                    temp_matr[k] = new int[m];
                Get_matr(matr, size_, temp_matr, i, j);
                obr_matr[i][j] = pow(-1, i + j + 2) * Det(temp_matr, m) * det;
                obr_matr[i][j] = Mod(obr_matr[i][j], hill::alph.length());
                Free_Mem(temp_matr, m);
            }
        }   
    }
    else
        cout << "Т.к. определитель матрицы = 0,\nто матрица вырожденная и обратной не имеет!!!" << endl;
    //Транспонирование матрицы
    Transpose_Mtx(obr_matr, tobr_matr, size_);
    //Печать обратной матрицы после транспонирования
    Print(tobr_matr, size_);
    
    string enc_msg = SetMsg("enc_msg.txt");
    vec = To_Number(enc_msg, rows, size_);
    cout << "\nNumeric enc message :\n";
    Print(vec, rows, size_);

    cout << endl;
    
    int **res = new int*[rows];
    for (int i = 0; i < rows; i++)
	res[i] = new int[size_];
    for (int i = 0; i < rows; i++)
	for (int j = 0; j < size_; j++)
            res[i][j] = 0;
    
    //matrix vector production
    for (int g = 0; g < rows; g++)
        for (int i = 0; i < size_; i++)
            for (int j = 0; j < size_; j++)
            {
                res[g][i] += tobr_matr[i][j] * vec[g][j];
                res[g][i] = res[g][i] % alph.length();
            }
    
    cout << "Numeric message :\n";
    Print(res, rows, size_);
    cout << "\nEncrypted message:\n";
    Print_txt(res, rows, size_);
    Print_txt(res, rows, size_, "result.txt");
    Free_Mem(tobr_matr, size_);
    Free_Mem(matr, size_);
    Free_Mem(obr_matr, size_);
    Free_Mem(res, rows);
}

int hill::Mod(int n, int mod)
{
    if(n < 0)
        return (mod + (n%mod));
    else
        return n % mod;
}

void hill::Extended_Euclid(int a, int b, int *x, int *y, int *d)
/* вычисление a * *x + b * *y = gcd(a, b) = *d */
{
    int q, r, x1, x2, y1, y2;
    if (b == 0) 
    {
        *d = a, *x = 1, *y = 0;
        return;
    }
    x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0) 
    {
        q = a / b, r = a - q * b;
        *x = x2 - q * x1;
        *y = y2 - q * y1;
        a = b, b = r;
        x2 = x1, x1 = *x;
        y2 = y1, y1 = *y;
    }
    *d = a, *x = x2, *y = y2;
}

int hill::Inverse(int a, int n)
{
    int d, x, y;
    Extended_Euclid(a, n, &x, &y, &d);
    if (d == 1)
    {
        if(x > 0)
            return x;
        else
            return n + x;
    }
    return 0;
}

//Функция транспонирования матрицы
void hill::Transpose_Mtx(int **matr, int **tMatr, int n)
{
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++)
            tMatr[j][i] = matr[i][j];
}
//Функция освобождения памяти
void hill::Free_Mem(int **matr, int size_)
{
    for(int i = 0; i < size_; i++)
        delete [] matr[i];
    delete [] matr;
}

//функция вычеркивания строки и столбца
void hill::Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol)   
{
    int ki = 0; 
    for (int i = 0; i < n; i++){
        if(i != indRow){
            for (int j = 0, kj = 0; j < n; j++){
                if (j != indCol){
                    temp_matr[ki][kj] = matr[i][j];
                    kj++;
                }
            }
            ki++;       
        }
    }
}

//функция вычисления определителя матрицы
int hill::Det(int **matr, int n)  
{
    int temp = 0;   //временная переменная для хранения определителя
    int k = 1;      //степень
    if(n < 1){
        cout<<"Не верный размер матрицы!!!" << endl;
        return 0;
    }
    else if (n == 1)
        temp = matr[0][0];
    else if (n == 2)
        temp = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
    else{
        for(int i = 0; i < n; i++){
            int m = n - 1;
            int **temp_matr = new int * [m];
            for(int j = 0; j < m; j++)
                temp_matr[j] = new int [m];
            Get_matr(matr, n, temp_matr, 0, i);
            temp = temp + k * matr[0][i] * Det(temp_matr, m);
            k = -k;
            Free_Mem(temp_matr, m);
        }
    }
    return temp;
}

//reading and set key from the file
string SetKeys(const char* file)
{
    ifstream fin(file);
    string key;
    vector <string> keys;
    while(!fin.eof())
    {
        getline(fin, key);
        keys.push_back(key);
    }
    fin.close();
    srand(time(NULL));
    int index = rand() % keys.size();
    return keys[index];
}
// reading message from the file
string SetMsg(const char* file)
{
    ifstream fin(file, ios::in | ios::binary);
    string msg;
    while(!fin.fail())
    {
        int symbol = fin.get();
        if(symbol == EOF)
            break;
        msg += (char)symbol;
    }
    return msg;
}