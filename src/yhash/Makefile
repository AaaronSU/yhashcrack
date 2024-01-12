GCC=gcc
CFLAGS=-Ofast
LFLAGS=-fPIC -shared

TESTSTR="Hello"

all : clean md5 sha1 sha224 sha256 sha512 libyhash

md5 :
	$(GCC) $(CFLAGS) common.c md5hash.c md5main.c -o md5hash

sha1 :
	$(GCC) $(CFLAGS) common.c sha1hash.c sha1main.c -o sha1hash

sha224 :
	$(GCC) $(CFLAGS) common.c sha224hash.c sha224main.c -o sha224hash

sha256 :
	$(GCC) $(CFLAGS) common.c sha256hash.c sha256main.c -o sha256hash

sha512 :
	$(GCC) $(CFLAGS) common.c sha512hash.c sha512main.c -o sha512hash

libyhash :
	$(GCC) $(LFLAGS) $(CFLAGS) common.c md5hash.c sha1hash.c sha224hash.c sha256hash.c sha512hash.c -o libyhash.so

test : test_md5 test_sha1 test_sha224 test_sha256 test_sha512

test_md5 :
	@echo "MD5 : "
	@./md5hash    $(TESTSTR)
	@echo -n $(TESTSTR) | md5sum    | cut -d' ' -f1
	@echo

test_sha1 :
	@echo "SHA1 : "
	@./sha1hash   $(TESTSTR)
	@echo -n $(TESTSTR) | sha1sum   | cut -d' ' -f1
	@echo

test_sha224 :
	@echo "SHA224 : "
	@./sha224hash $(TESTSTR)
	@echo -n $(TESTSTR) | sha224sum | cut -d' ' -f1
	@echo

test_sha256 :
	@echo "SHA256 : "
	@./sha256hash $(TESTSTR)
	@echo -n $(TESTSTR) | sha256sum | cut -d' ' -f1
	@echo

test_sha512 :
	@echo "SHA512 : "
	@./sha512hash $(TESTSTR)
	@echo -n $(TESTSTR) | sha512sum | cut -d' ' -f1

clean :
	@rm -rf *~ *.o *.so md5hash sha1hash sha224hash sha256hash sha512hash
