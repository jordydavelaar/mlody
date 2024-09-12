CC = h5c++ -I$(RAPTOR)/src -I$(RAPTOR)/src/mlody -I$(PWD)
CFLAGS = -fopenmp  -O2 -lm -lgsl -Wall -Wno-unused-but-set-variable -Wno-narrowing
LDFLAGS = -fopenmp -lm -lgsl

VPATH=layers:
CPATH=layers:

OBJDIR=build

TARGET=MLody

SOURCESRT=main.c baseLayer.c tensor.c model-ml.c utils-ml.c mlody.c
SOURCES=$(SOURCESRT) activation.c batchNormalization.c conv1d.c conv2d.c dense.c elu.c embedding.c flatten.c locally1d.c locally2d.c lstm.c maxPooling2d.c
OBJECTS := $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))

all: create_directories $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

create_directories:
	@test -d $(OBJDIR) || mkdir -v $(OBJDIR)


$(OBJECTS): $(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS)  -c $^ -o $@


clean:
	rm -rf $(OBJECTS) $(TARGET)

