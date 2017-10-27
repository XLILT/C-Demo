-- print(#args)
-- print(string.format("%x %x", args[1], args[2]))

ret = stt_rpc(args[1], args[2], 51001, "query_mail_count", "uid@=21290/")
print(ret)

