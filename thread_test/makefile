SrcFile=$(wildcard *.cc)
TargetFile=$(patsubst %.cc, %, $(SrcFile))

all:$(TargetFile)


%:%.cc
	g++ -I./ -o $@ $< -lpthread


clean:
	rm -f $(TargetFile)