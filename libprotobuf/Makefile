CPPFLAGS = -g -fPIC -I. -I/usr/local/include -std=c++11
LDFLAGS = -L/usr/local/lib/ -L. -Wl,-rpath-link=/usr/local/lib -Wl,-rpath -Wl,.
CC = /usr/local/external-toolchain/gcc-linaro-5.3.1-arm/bin/arm-linux-gnueabi-c++

all: libjson2pb.so test_json

clean:
	-rm -f *.o *.so *.a libjson2pb.so.* test

test_json: test_json.o test.pb.o libjson2pb.so -lprotobuf
test_json.o: test.pb.h
	$(CC) -c test_json.cc $(CPPFLAGS) $(LDFLAGS) -lprotobuf
test.pb.o: test.pb.h
	$(CC) -c test.pb.cc $(CPPFLAGS) $(LDFLAGS) -lprotobuf

json2pb.o: bin2ascii.h
	$(CC) -c $(LDFLAGS) $(CPPFLAGS) json2pb.cc -lprotobuf

libjson2pb.so: json2pb.o
	$(CC) $(LDFLAGS) -o $@ $^ -Wl,-soname=$@ -Wl,-h -Wl,$@ -shared -L. -lcurl -lprotobuf -lstdc++ -ljansson -Wl,-rpath-link=/usr/local/lib

test.pb.h test.pb.cc: test.proto
	/home/protobuf/ubuntu/bin/protoc --cpp_out=$(shell pwd) test.proto
