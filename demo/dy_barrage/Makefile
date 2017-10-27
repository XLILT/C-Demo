CXXFLAGS=-g

bin = get_dy_barrage
objs = main.o dy_barrage_client.o data_def.o dy_codec.o

get_dy_barrage: $(objs)
	g++ -o $(bin) $(objs) -lpthread

.phony: clean

clean:
	rm $(objs) $(bin)
