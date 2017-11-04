#include "header.h"

int main()
{
	string msg, key, message_filename;
        cout << "Enter filename message:" << endl;
        cin >> message_filename;
        const char * name_file = message_filename.c_str();
        msg = SetMsg(name_file);
        cout << "Enter filename keys:" << endl;
        cin >> message_filename;
        name_file = message_filename.c_str();
        key = SetKeys(name_file);
	cout << "Enter the Plain Text Message" << endl;
	cout << msg;
	cout << "\nEnter the Key" << endl;
	cout << key;
	hill h(msg, key);
	cout << endl;
	cout << "\nEncrypted message is : \n";
	h.Encrypt();
	cout << endl;
        h.Dechiper();
	return 0;
}