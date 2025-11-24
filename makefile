.PHONY: all init build clean run install uninstall

default_target: all
.PHONY : default_target

APP=halo
INIT=haloinit

all: clean init build

init:
	mkdir -p bin
	mkdir -p test
build:
	cd bin && cmake .. && make
	go build -o bin/${INIT} cmd/main.go
clean:
	rm -rf bin
	rm -rf test
run:
	cd bin && ./${APP}
install:
	cp bin/${APP} /usr/local/bin/${APP}
	cp bin/${INIT} /usr/local/bin/${INIT}
uninstall:
	rm /usr/local/bin/${APP}
	rm /usr/local/bin/${INIT}