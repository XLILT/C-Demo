#include <string>
#include <iostream>
#include <Common/Endecryption.h>

#define PRIVATEFILE "test.key"
#define PUBLICFILE "test_pub.key"
#define PUBLICKEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCdj4vPdDnZmlyeTCtv4TzzowZVNhxFIwm2GInvM1n5jumPtfGWjVCdEFrzaNUnK2EmNdZ8Z6Pn2vPuT44T6BM8Eltd9TlQCHGuJ2vdw/EpKaABCqtn8mfWk+NhAEWzatcjTW1A4rPNEYpVos/Z5wVKy1mnVyWXruTmcXwORCdkywIDAQAB"
#define PRIVATEKEY "MIICXAIBAAKBgQCdj4vPdDnZmlyeTCtv4TzzowZVNhxFIwm2GInvM1n5jumPtfGWjVCdEFrzaNUnK2EmNdZ8Z6Pn2vPuT44T6BM8Eltd9TlQCHGuJ2vdw/EpKaABCqtn8mfWk+NhAEWzatcjTW1A4rPNEYpVos/Z5wVKy1mnVyWXruTmcXwORCdkywIDAQABAoGAeP5dt+6h6hee3jTR+nV2EAZ1+4O1C+aPM5X+foDprDnx49ktb5aPfD2uClPLs+udC/G2Bwyzkn3SaoQPL/w8n+VBjverKxEqGYT1OEFlRZcGkjCKWjDOQFKnzsT3z20uF6aEmkpsO/bB8GTQc4WfnvU7vlQg4ff2j7aQFg5HJ9kCQQDPL8APcyAmTgglAC6cl8pgDSv7LXfe8dsQrUhG/1M58eYW3tk/y5qpLp5bDwHjX0ovq+o4cn3KCBcNZc3GsUMnAkEAwq6qRwq/U9jj719Ff8d+NjMuJNaUoD0xi1bZDy/W6lb/6jVNL2pIdWvmseoI0jHLAoyXOsB6kCPrUQXarq9HvQJBAIOdMcSeva2XpFTc6L9RLZ4Wv/mvyJY3zZGqgl+Xkqcco62jox6DmJwgoTf3MJvfzKC79O4mzQGqYfqA0VeHA8ECQG7Wgptvwv45vYvK8gaNzY2OFfdjM7sHG+34xBuhYPqKDamKLyePmzE+/VjNpbgGIU6SPId2jlECIjc+3gIWSQECQGIO7ydVYy5ggk4g0v4iAYz0OwNFj3c2S2RBoS9S0W2ZZSlqg78yDkH7T7V4slNODmCzkfSDANsEL9WTF2JYtko="

using namespace std;

static void hexdump(FILE *f, const char *title, const unsigned char *s, int len)
{  
//#define HEXDUMPTYPE 

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

int main(void)
{
	string str_en_file;
	string str_de_file;
	int ret = RSAPubFileEncrypt(string(PUBLICFILE), string("I love dancing in the center of stage!"), string("I love dancing in the center of stage!").length(), str_en_file, RSA_PKCS1_PADDING);
	hexdump(stdout, "== after encrypt with file ==: ", (const unsigned char*)str_en_file.c_str(), str_en_file.length());
	printf("%d\n", ret);
	
	ret = RSAPriFileDecrypt(string(PRIVATEFILE), str_en_file, str_en_file.length(), str_de_file, RSA_PKCS1_PADDING);
	//ptr_de=my_decrypt(ptr_en, (char *)OPENSSLKEY);
	printf("after decrypt with file: %s\n", str_de_file.c_str());
	printf("%d\n", ret);
	
	ret = RSAPubEncrypt(string(PUBLICKEY), string("I love dancing in the center of stage!"), string("I love dancing in the center of stage!").length(), str_en_file, RSA_PKCS1_PADDING);
	hexdump(stdout, "== after encrypt with file ==: ", (const unsigned char*)str_en_file.c_str(), str_en_file.length());
	printf("%d\n", ret);
	
	ret = RSAPriDecrypt(string(PRIVATEKEY), str_en_file, str_en_file.length(), str_de_file, RSA_PKCS1_PADDING);
	//ptr_de=my_decrypt(ptr_en, (char *)OPENSSLKEY);
	printf("after decrypt with file: %s\n", str_de_file.c_str());
	printf("%d\n", ret);
	
	return 0;
}
