CXXFLAGS+=-I./include

SOURCES=schematic.o elements.o

all: libandromeda.so libandromeda.a

libandromeda.so: $(SOURCES)
	$(CXX) $< $(CXXFLAGS) -shared -fPIC -L. -Wl,-soname,$@ -o $@

libandromeda.a: $(SOURCES)
	ar rcs libandromeda.a $(SOURCES)

clean:
	rm -rf libandromeda.* $(SOURCES)
