SrcFiles=$(wildcard *.cc)
SockFiles=$(wildcard *.socket)
TargetFiles=$(patsubst %.cc, %, $(SrcFiles))

all:$(TargetFiles)

boost:$(TargetFiles)
	


%:%.cc
	g++ -I./  $< -o $@ -g



clean:
	rm -f $(TargetFiles)

clean_sock:
	rm -f $(SockFiles)