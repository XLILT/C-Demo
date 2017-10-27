#include <Common/Email.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
	Email *g_email = Email::Instance();
	
	SendEmailArgs args;
	strncpy(args.uname, "xiaolongma002@126.com", sizeof(args.uname));
	strncpy(args.upass, "1967528m", sizeof(args.upass));
	strncpy(args.from, "xiaolongma002@126.com", sizeof(args.from));
	strncpy(args.to, "563107157@qq.com", sizeof(args.to));
	strncpy(args.subject, "subject", sizeof(args.subject));
	strncpy(args.body, "body", sizeof(args.body));						
	strncpy(args.hostname, "Smtp.126.com", sizeof(args.hostname));
	args.port = 25;
	
	int ret = g_email->sendmail(args);
	if (ret != 0)
	{
		printf("err,%d\n", ret);
		//TL_FAST_LOG("log/send_alarm_err.log", tlstDay, "send email to %s unsuccessfully.", it->email);							
	};
	
	return 0;
}