UDLP=/usr/lib/lapack/
CMP_LIST=$(UDLP)libbase58.dll $(UDLP)libbase64.dll $(UDLP)libripemd160.dll $(UDLP)libsha256.dll $(UDLP)libbitcoin.dll $(UDLP)libsecp256k1.dll $(UDLP)libbioinformatics.dll

@all: $(CMP_LIST)
	@ echo -e "done"

$(UDLP)libbase58.dll: base58/base58.h base58/base58.c
	@ cd base58; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@

$(UDLP)libbase64.dll: base64/base64.h base64/base64.c
	@ cd base64; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@

$(UDLP)libripemd160.dll: ripemd160/ripemd160.h ripemd160/ripemd160.c
	@ cd ripemd160; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@

$(UDLP)libsha256.dll: sha256/sha256.h sha256/sha256.c
	@ cd sha256; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@

$(UDLP)libsecp256k1.dll: secp256k1/secp256k1.c secp256k1/secp256k1.h
	@ cd secp256k1; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@

$(UDLP)libbitcoin.dll: bitcoin/bitcoin.h bitcoin/bitcoin.c
	@ cd bitcoin; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@

$(UDLP)libbioinformatics.dll: bioinformatics/bioinformatics.h bioinformatics/bioinformatics.c
	@ cd bioinformatics; make clean lib; cd ..
	@ echo -e "successfully compiled : "$@