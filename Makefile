build:
	gcc-13 -fexec-charset=UTF-8 \
	main.c \
	common.c \
	AoC1/aoc1.c \
	AoC2/aoc2.c \
	AoC3/aoc3.c \
	-o aoc
