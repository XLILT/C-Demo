import os

env = Environment()
#env = Environment(CXX = 'clang++')
env.Replace(CXX='clang++')
#env.Replace(CXX='c++')

MYSQL_INC = '/usr/include/mysql'
MYSQL_LIB = '/usr/lib64/mysql'

cppflags = ['-g', '-Wall', '-O0']
cpppath = ['.', os.getenv('STT_INC'), os.getenv('STT_INC') + '/SttMongoDB', os.getenv('BOOST_INC'), MYSQL_INC]
libs = ['netmsg', 'Common', 'MsgClientLib', 'ServerBase', 'SttMongoDB',
        'CommonBase', 'MySqlDB', 'Jsoncpp', 'textlog', 'mysqlclient', 'mongoclient',
        'boost_thread', 'boost_chrono', 'boost_system', 'pthread', 'boost_regex',
        'rt', 'lua']
libpath = ['.', os.getenv('STT_LIB'), os.getenv('BOOST_LIB'), MYSQL_LIB]

env.ParseFlags('-g -Wall -O0')

srcs = Glob('*.cpp')

#env.Program('main', srcs, CPPPATH=cpppath, LIBPATH=libpath, LIBS=libs)
env.Program('main', srcs, CPPFLAGS=cppflags, CPPPATH=cpppath, LIBPATH=libpath, LIBS=libs)
env.Alias('install',
		[
			env.Install('/tmp', 'main')
		]
	)

