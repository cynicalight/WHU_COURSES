##################################################
# Makefile of pmtestx.asm (x=[1,2,3...])
##################################################

SRC:=boot.asm
BIN:=$(subst .asm,.bin,$(SRC))

.PHONY : everything

everything : $(BIN)
	dd if=$(BIN) of=a.img bs=512 count=1 conv=notrunc

$(BIN) : $(SRC)
	nasm $< -o $@

##################################################
# Makefile of pmtestx.asm (x=[1,2,3...])
##################################################

# # 默认源文件
# SRC ?= zj1.asm
# BIN := $(SRC:.asm=.com)

# .PHONY: everything clean

# # 主目标
# everything: $(BIN)
# 	hdiutil attach pm.img -mountpoint /Volumes/floppy
# 	sudo cp $(BIN) /Volumes/floppy/
# 	sudo hdiutil detach /Volumes/floppy

# # 从.asm生成.com的规则
# $(BIN): $(SRC)
# 	nasm $< -o $@

# # 清理规则
# clean:
# 	rm -f *.com

# %.asm:
# 	@echo "Setting SRC to $@"
# 	@$(MAKE) everything SRC=$@ --debug=v