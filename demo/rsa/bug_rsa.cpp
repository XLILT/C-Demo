#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#include<string>
#include <sstream>

#define PRIVATEFILE "test.key"
#define PUBLICFILE "test_pub.key"
#define PUBLICKEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCdj4vPdDnZmlyeTCtv4TzzowZVNhxFIwm2GInvM1n5jumPtfGWjVCdEFrzaNUnK2EmNdZ8Z6Pn2vPuT44T6BM8Eltd9TlQCHGuJ2vdw/EpKaABCqtn8mfWk+NhAEWzatcjTW1A4rPNEYpVos/Z5wVKy1mnVyWXruTmcXwORCdkywIDAQAB"
#define PRIVATEKEY "MIICXAIBAAKBgQCdj4vPdDnZmlyeTCtv4TzzowZVNhxFIwm2GInvM1n5jumPtfGWjVCdEFrzaNUnK2EmNdZ8Z6Pn2vPuT44T6BM8Eltd9TlQCHGuJ2vdw/EpKaABCqtn8mfWk+NhAEWzatcjTW1A4rPNEYpVos/Z5wVKy1mnVyWXruTmcXwORCdkywIDAQABAoGAeP5dt+6h6hee3jTR+nV2EAZ1+4O1C+aPM5X+foDprDnx49ktb5aPfD2uClPLs+udC/G2Bwyzkn3SaoQPL/w8n+VBjverKxEqGYT1OEFlRZcGkjCKWjDOQFKnzsT3z20uF6aEmkpsO/bB8GTQc4WfnvU7vlQg4ff2j7aQFg5HJ9kCQQDPL8APcyAmTgglAC6cl8pgDSv7LXfe8dsQrUhG/1M58eYW3tk/y5qpLp5bDwHjX0ovq+o4cn3KCBcNZc3GsUMnAkEAwq6qRwq/U9jj719Ff8d+NjMuJNaUoD0xi1bZDy/W6lb/6jVNL2pIdWvmseoI0jHLAoyXOsB6kCPrUQXarq9HvQJBAIOdMcSeva2XpFTc6L9RLZ4Wv/mvyJY3zZGqgl+Xkqcco62jox6DmJwgoTf3MJvfzKC79O4mzQGqYfqA0VeHA8ECQG7Wgptvwv45vYvK8gaNzY2OFfdjM7sHG+34xBuhYPqKDamKLyePmzE+/VjNpbgGIU6SPId2jlECIjc+3gIWSQECQGIO7ydVYy5ggk4g0v4iAYz0OwNFj3c2S2RBoS9S0W2ZZSlqg78yDkH7T7V4slNODmCzkfSDANsEL9WTF2JYtko="
#define ENCRYPT_FILE "mywords.en"
#define BUFFSIZE 1024

using namespace std;

extern RSA *formatPublicRSAKey(string str_key);
extern RSA *formatPrivateRSAKey(string str_key);

char* my_encrypt_file(char *str,char *path_key);//加密
char* my_decrypt_file(char *str,char *path_key);//解密

char* my_encrypt(char *str,char *key);//加密
char* my_decrypt(char *str,char *key);//解密


static void hexdump(FILE *f, const char *title, const unsigned char *s, int len)
{  
//#define HEXDUMPTYPE 1;

#ifdef HEXDUMPTYPE
	
	int n = 0;
	fprintf(f, "%s", title);
	
	for (n = 0; n < len; ++n) 
	{		
        fprintf(f, "%02x", s[n]);  
    }  	
#else
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
#endif
} 

#if 0

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

#endif

int main(void)
{
#if 0
	FILE *file = NULL;
	if((file=fopen(ENCRYPT_FILE, "r"))==NULL)
	{
		perror("open encrypt file error");
		return NULL;    
	}

	char tmp[1024] = {0};
	int cnt = fread(tmp, 1, sizeof(tmp), file);
	if(0 != cnt)
	{
		//printf("after read %d from file:%s\n", cnt, tmp);
		hexdump(stdout, "== read from file ==: ", (unsigned char *)tmp, cnt);
		printf("\n");
		
		char *tmp_dec = my_decrypt(tmp, (char *)OPENSSLKEY);
		if(NULL != tmp_dec)
		{
			printf("after decrypt:%s\n", tmp_dec);
			free(tmp_dec);
			tmp_dec = NULL;
		}
	}	
		
	if(NULL != file)
	{
		fclose(file);
		file = NULL;
	}
#endif	

	char *ptr_en, *ptr_de;
	ptr_en = my_encrypt((char *)string("When I fall in love with your, I have knew how to do if you do not love me.").c_str(), (char *)PUBLICKEY);
	//printf("after encrypt:%s\n",ptr_en);
	hexdump(stdout, "== after encrypt ==: ", (unsigned char *)ptr_en, strlen(ptr_en));
	printf("\n");
	
	ptr_de=my_decrypt(ptr_en, (char *)PRIVATEKEY);
	printf("after decrypt:%s\n", ptr_de);
	
	if(ptr_en!=NULL)
	{
		free(ptr_en);
	}   
	
	if(ptr_de!=NULL)
	{
		free(ptr_de);
	}   
	
	return 0;
}

char *my_encrypt_file(char *str,char *path_key)
{
	char *p_en;
	RSA *p_rsa;
	FILE *file;
	int flen,rsa_len;
	if((file=fopen(path_key,"r"))==NULL)
	{
		perror("open key file error");
		return NULL;    
	}   
	
	p_rsa = RSA_new();
	if(PEM_read_RSA_PUBKEY(file, &p_rsa, NULL, NULL) == NULL)
	//if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL)
	{		
		ERR_print_errors_fp(stdout);
		return NULL;
	}   

	flen = strlen(str);
	rsa_len = RSA_size(p_rsa);
	p_en=(char *)malloc(rsa_len + 1);
	memset(p_en, 0, rsa_len+1);
		
	int ret = 0;
	if((ret = RSA_public_encrypt(flen, (unsigned char *)str, (unsigned char*)p_en, p_rsa, RSA_PKCS1_PADDING/* RSA_NO_PADDING  RSA_PKCS1_PADDING */)) < 0)
	{		
		return NULL;
	}
	
	hexdump(stdout, "== p_len ==: ", (const unsigned char *)p_en, ret);
	
	RSA_free(p_rsa);
	fclose(file);
	CRYPTO_cleanup_all_ex_data(); 
	return p_en;
}

char *my_decrypt_file(char *str,char *path_key)
{
	char *p_de;
	RSA *p_rsa;
	FILE *file;
	int rsa_len;
	if((file=fopen(path_key,"r"))==NULL)
	{
		perror("open key file error");
		return NULL;
	}
	
	p_rsa = RSA_new();
	if(PEM_read_RSAPrivateKey(file, &p_rsa, NULL, NULL) == NULL)
	//if((p_rsa=PEM_read_RSAPrivateKey(file,NULL,NULL,NULL))==NULL)
	{
		ERR_print_errors_fp(stdout);
		return NULL;
	}
	
	rsa_len = RSA_size(p_rsa);
	p_de=(char *)malloc(rsa_len+1);
	memset(p_de,0,rsa_len+1);
	
	if(RSA_private_decrypt(strlen(str), (unsigned char *)str, (unsigned char*)p_de, p_rsa, RSA_PKCS1_PADDING/* RSA_NO_PADDING  RSA_PKCS1_PADDING */) < 0)
	{
		printf("here null\n");
		return NULL;
	}
	
	RSA_free(p_rsa);
	fclose(file);
	CRYPTO_cleanup_all_ex_data(); 
	return p_de;
}

char *my_encrypt(char *str,char *key)
{
	char *p_en;
	RSA *p_rsa;
	int flen,rsa_len;	 
	
	p_rsa = formatPublicRSAKey(std::string(key));
	if(NULL == p_rsa)
	//if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL)
	{		
		ERR_print_errors_fp(stdout);
		return NULL;
	}   

	flen = strlen(str);
	rsa_len = RSA_size(p_rsa);
	p_en=(char *)malloc(rsa_len + 1);
	memset(p_en, 0, rsa_len+1);
		
	int ret = 0;
	if((ret = RSA_public_encrypt(flen, (unsigned char *)str, (unsigned char*)p_en, p_rsa, RSA_PKCS1_PADDING/* RSA_NO_PADDING  RSA_PKCS1_PADDING */)) < 0)
	{		
		return NULL;
	}
	
	hexdump(stdout, "== p_len ==: ", (const unsigned char *)p_en, ret);
	
	RSA_free(p_rsa);
	CRYPTO_cleanup_all_ex_data(); 
	return p_en;
}

char *my_decrypt(char *str,char *key)
{
	char *p_de;
	RSA *p_rsa;
	int rsa_len;
	
	p_rsa = formatPrivateRSAKey(std::string(key));
	if(p_rsa == NULL)
	//if((p_rsa=PEM_read_RSAPrivateKey(file,NULL,NULL,NULL))==NULL)
	{
		ERR_print_errors_fp(stdout);
		return NULL;
	}
	
	rsa_len = RSA_size(p_rsa);
	p_de=(char *)malloc(rsa_len+1);
	memset(p_de,0,rsa_len+1);
	
	if(RSA_private_decrypt(strlen(str), (unsigned char *)str, (unsigned char*)p_de, p_rsa, RSA_PKCS1_PADDING/* RSA_NO_PADDING  RSA_PKCS1_PADDING */) < 0)
	{
		return NULL;
	}
	
	RSA_free(p_rsa);
	CRYPTO_cleanup_all_ex_data(); 
	return p_de;
}
