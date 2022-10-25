CXX := g++
TARGET := jsonHandler_test
CFLAGS = -std=c++17 -I$(IDIR) -Wall -ljsoncpp -lgtest

ODIR := ./obj
SDIR := ./
IDIR := ./

_DEPS := jsonHandler.h
DEPS := $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ := jsonHandler.o
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))

$(TARGET): $(OBJ) $(ODIR)/test.o
	$(CXX) -o $(TARGET) $^ $(CFLAGS) --coverage

$(ODIR)/test.o: $(SDIR)/test.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS) --coverage	

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.* $(TARGET) ./*.info ./html
