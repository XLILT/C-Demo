#include "stdafx.h"
#include <CommonBase/md5.h>

int main()
{
	char s_sp[4][128];
	char s_key[64];
	const char *key = "1336fb0dd29c517b4206fa5ceb4347f8";
    const char *tkey = "12345";
	
	sprintf(s_sp[0], "%s%s%s", "1423123830", "dOu2YuchUn3tIan1", "3B6A8BEA65C194EFA325CA76E689C85D");
	sprintf(s_sp[1], "%s%s%s", "1423123830", "SlAoZhAnGKao216Yu", "3B6A8BEA65C194EFA325CA76E689C85D");
	sprintf(s_sp[2], "%s%s", "1423123830", "dOu2YuchUn3tIan1");
	sprintf(s_sp[3], "%s%s", "1423123830", "SlAoZhAnGKao216Yu");

	for(int i = 0; i < 4; i++)
	{
		//get_MD5_str(s_sp[i], strlen(s_sp[i]), s_key);
		get_MD5_str(tkey, strlen(tkey), s_key);
		printf("%s\n", s_key);
		if(!stricmp(s_key, key))
		{
			printf("get\n");
		}
		else
		{
			printf("do not get\n");
		}		
	}

	return 0;
}

