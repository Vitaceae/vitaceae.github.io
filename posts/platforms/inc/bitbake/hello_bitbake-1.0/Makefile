all: hello

hello: main.o
	${CC} $? -o $@
install:
	install -d -m 755 ${DESTDIR}/bin
	install -m 755 hello ${DESTDIR}/bin