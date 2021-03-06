/* file openssl.cpp */  

#include <stdio.h>  
#include <string.h>  
#include <openssl/aes.h>  
#include <openssl/rand.h> 
#include <iostream> 
#include <sstream>  
 
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
 
int main(int argc, char **argv)  
{  
        char   rkey[AES_BLOCK_SIZE + 1] = "0123456789abcdef";		//128bits key.
        AES_KEY         key;  	//Internal key.  
  
		//Testdata.  
        // [yasi] Make static content instead of random text  
        //char   plaintext[AES_BLOCK_SIZE] = "12345678901234";
		char   plaintext[AES_BLOCK_SIZE * 4] =  "需加密的字符this is a string will be AES_Encrypt";
          
        unsigned char   ciphertext[AES_BLOCK_SIZE * 4];  
        unsigned char   checktext[AES_BLOCK_SIZE * 4];  
  
        //Init vector.  
        char   iv[AES_BLOCK_SIZE + 1] = "fedcba9876543210"; 
        //Save vector.  
        char   saved_iv[AES_BLOCK_SIZE];  
  
        int nr_of_bits = 0;  
        int nr_of_bytes = 0;  
  
        //Zeror buffer.  
        memset(ciphertext, 0, sizeof ciphertext);  
        memset(checktext, 0, sizeof checktext);  
  
        //Generate random  
        //RAND_pseudo_bytes(rkey, sizeof rkey);  
        //RAND_pseudo_bytes(saved_iv, sizeof saved_iv);  
  
        cout<<"== rkey ==: "<<rkey<<endl;
        cout<<"== iv ==: "<<iv<<endl;
		cout<<"== plaintext ==: "<<plaintext<<endl;
  
        //Entrypt  
        memcpy(saved_iv, iv, AES_BLOCK_SIZE);  
        nr_of_bits = 8 * (sizeof(rkey) - 1);
        AES_set_encrypt_key((unsigned char *)rkey, nr_of_bits, &key);
		
        nr_of_bytes = sizeof(plaintext);		
        AES_cbc_encrypt((unsigned char *)plaintext, ciphertext, nr_of_bytes, &key, (unsigned char *)iv, AES_ENCRYPT);  
  
        hexdump(stdout, "== ciphertext ==: ", ciphertext, sizeof(ciphertext));  
        printf("\n");  
		
        // [yasi] iv is changed in encryption  
		//hexdump(stdout, "== iv changed ==: ", ciphertext, sizeof(ciphertext));
		//printf("\n");        
  
        //Decrypt  
        memcpy(iv, saved_iv, AES_BLOCK_SIZE);       // [yasi] without this line, decrypt will fail because iv is changed in encryption  
        AES_set_decrypt_key((unsigned char *)rkey, nr_of_bits, &key);
		
        nr_of_bytes = sizeof(ciphertext);  
		AES_cbc_encrypt(ciphertext, checktext, nr_of_bytes, &key, (unsigned char *)iv, AES_DECRYPT);  
        
		cout<<"== checktext1 ==: "<<(char *)checktext<<endl;		
        
		string cipher_hextext = "e8a9b785d5def5ae739528d9615df2958268d611e2ae431f1fd18f52a582f2d84a2353c358f5e8ab52d84eb89d22f9081f9ffb0e5ee6522cb7eb1091c68699d7";
		string cipher_text;
		
		hexload(cipher_hextext, cipher_text);
		
		memcpy(iv, saved_iv, AES_BLOCK_SIZE);       // [yasi] without this line, decrypt will fail because iv is changed in encryption  
		AES_set_decrypt_key((unsigned char *)rkey, nr_of_bits, &key);
		
		nr_of_bytes = strlen(cipher_text.c_str());  
		AES_cbc_encrypt((unsigned char *)(cipher_text.c_str()), checktext, nr_of_bytes, &key, (unsigned char *)iv, AES_DECRYPT);
		
		cout<<"== checktext2 ==: "<<checktext<<endl;
  
        return 0;  
}  