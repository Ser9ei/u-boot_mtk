CFLAGS = -I./ -DUSE_HOSTCC

all: mkimage ncb

clean:
	rm -f mkimage ncb *.o

.c.o:
	$(HOSTCC) $(CFLAGS) -c $^

.depend:

mkimage: mkimage.o crc32.o crc.o
	$(HOSTCC) -o $@ $^

ncb: ncb.o
	$(HOSTCC) -o $@ $^

