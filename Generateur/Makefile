CFLAGS	=	-std=c18 -Wpedantic -Wall -Wextra -Wconversion -Wwrite-strings -Werror \
 			-Wstrict-prototypes -fstack-protector-all \
			-O2 -g 

LFLAGS	=	-Wl,-z,relro,-z,now -pie -lpthread -lrt

SRC_DIR =	src
INC_DIR =	inc

BIN_DIR =	bin
BLD_DIR =	build

SRCS	=	$(shell find $(SRC_DIR) -type f -name \*.c)
BINS	=	$(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

TARGET	=	word_generator

$(TARGET): $(BLD_DIR) $(BINS)
	$(CC) -o $(BLD_DIR)/$@ $(BINS) $(LFLAGS)

lib$(TARGET).a: $(BLD_DIR) $(BINS)
	ar -r $(BLD_DIR)/lib$(TARGET).a $(BINS)
	ranlib $(BLD_DIR)/lib$(TARGET).a

lib$(TARGET).so: $(BLD_DIR) $(BINS)
	$(CC) -o $(BLD_DIR)/$@ $(BINS) $(LFLAGS) -shared

all: $(TARGET) lib$(TARGET).a lib$(TARGET).so

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(BIN_DIR)
	$(CC) -c $< -o $@ -I$(INC_DIR) $(CFLAGS)

$(BIN_DIR):
	mkdir $@

$(BLD_DIR):
	mkdir $@

clean:
	rm -f $(TARGET)
	rm -rf $(BIN_DIR) $(BLD_DIR)