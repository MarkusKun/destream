all : destream.bin

run :
	./destream.bin
	
destream.o : destream.cc

destream.bin : destream.o
	$(CXX) -o $@ $^

