CXX = g++
CXXFLAGS = -std=c++14

TARGET = gameOflife
HEADF = conway
OUT = game.out

all:
	$(CXX) $(CXXFLAGS) -c $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c $(HEADF).cpp
	$(CXX) $(CXXFLAGS) -o $(OUT) $(TARGET).o $(HEADF).o

.PHONY: clean
clean:
	@-del $(OUT) *.o .depend
	@echo clean done
