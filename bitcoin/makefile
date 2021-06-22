# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
CC=gcc -O3
UDLP=/usr/lib/lapack
IMPLIB=-L$(UDLP) -lsha256 -lbase58 -lripemd160 -lsecp256k1 -lgmp
HEADER=bitcoin.h
SOURCE=bitcoin.c
LIBNM=libbitcoin.dll
OBJNM=bitcoin.o
LIBPT=../lib/
OBJPT=../obj/
MAIN=main.c
EXE=main.exe
CP=cp
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
@all:
	@ echo -e "nothing to do :)"

clear:
	@ clear

clean:
	@ rm -rf $(LIBPT)$(LIBNM)
	@ rm -rf $(OBJPT)$(OBJNM)
	@ rm -rf $(EXE)*
	@ rm -rf $(UDLP)$(LIBNM)

exe: clear $(EXE)
	@ echo -e "done"

lib: clear $(LIBPT)$(LIBNM)
	@ echo -e "done"

run: $(EXE)
	@ ./$(EXE)

$(EXE): $(MAIN) $(SOURCE) $(HEADER)
	$(CC) $^ $(IMPLIB) -o $(EXE) 

$(OBJPT)$(OBJNM): $(SOURCE) $(HEADER)
	$(CC) $< -c $(IMPLIB) -o $@

$(LIBPT)$(LIBNM): $(OBJPT)$(OBJNM)
	$(CC) $^ $(IMPLIB) -shared -o $@
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #