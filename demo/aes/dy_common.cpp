#include <string>
#include <iostream>
#include <sstream>  
#include <string.h>
#include <Common/Endecryption.h>

using namespace std;

static void hexdump(FILE *f, const char *title, const unsigned char *s, int len)
{  
	int n = 0;
	fprintf(f, "%s", title);
	
	for (n = 0; n < len; ++n) 
	{		
        fprintf(f, "%02x", s[n]);  
    }  	
	
	/*
    int n = 0;  	
    fprintf(f, "%s", title);  
	
    for (; n < len; ++n) 
	{  
        if ((n % 16) == 0) 
		{  
                fprintf(f, "\n%04x", n);  
        }  
		
        fprintf(f, " %02x", s[n]);  
    }  
  
    fprintf(f, "\n");  
	*/  
}

static void hexload(const string &hex_text, string &text)
{
	int i =0;
	while(true)  
    {  
        char c;  
        int x;  
        stringstream ss;  
        ss<<hex<<hex_text.substr(i, 2).c_str();  
        ss>>x;  
        c = (char)x;  
        text += c;  
        if(i >= (int)hex_text.length() - 2)
		{	
			break;  
		}
		
        i += 2;  
    }  	
}

int main(void)
{
	string key = "0123456789abcdef";
	//string iv = "fedcba9876543210";
	//string plaintext = "需加密的字符this is a string will be AES_Encrypt";
	string plaintext = "this is a string will be AES_Encrypt";
	//string plaintext = "0123456789123456";
	string ciphertext;
	string checktext;
	
	cout<<plaintext<<endl;
	int ret = AESCBCEndecrypt(plaintext, ciphertext, plaintext.length(), key, string("fedcba9876543210"), LOCAL_AES_ENCRYPT);
	cout<<ret<<", "<<ciphertext<<endl;
	
	hexdump(stdout, "== ciphertext ==: ", (const unsigned char*)ciphertext.c_str(), ret);
	printf("\n");
	
	ret = AESCBCEndecrypt(ciphertext, checktext, ret, key, string("fedcba9876543210"), LOCAL_AES_DECRYPT);
	cout<<ret<<", "<<checktext<<endl;

	string cipher_hextext = "e8a9b785d5def5ae739528d9615df2958268d611e2ae431f1fd18f52a582f2d84a2353c358f5e8ab52d84eb89d22f9081f9ffb0e5ee6522cb7eb1091c68699d7";
	string cipher_text;
		
	hexload(cipher_hextext, cipher_text);
	
	ret = AESCBCEndecrypt(cipher_text, checktext, strlen(cipher_text.c_str()), key, string("fedcba9876543210"), LOCAL_AES_DECRYPT);
	cout<<ret<<", "<<checktext<<endl;
	
	return 0;
}