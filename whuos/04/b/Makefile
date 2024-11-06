##################################################
# Makefile of pmtestx.asm (x=[1,2,3...])
##################################################

SRC:=boot.asm
BIN:=$(subst .asm,.com,$(SRC))

.PHONY : everything

everything : $(BIN)
	hdiutil attach pm.img -mountpoint /Volumes/floppy
	sudo cp $(BIN) /Volumes/floppy/
	sudo hdiutil detach /Volumes/floppy

$(BIN) : $(SRC)
	nasm $< -o $@