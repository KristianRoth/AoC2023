build:
	gcc-13 -fexec-charset=UTF-8 \
	-O3 \
	main.c \
	common.c \
	AoC1/aoc1.c \
	AoC2/aoc2.c \
	AoC3/aoc3.c \
	AoC4/aoc4.c \
	AoC5/aoc5.c \
	AoC6/aoc6.c \
	AoC7/aoc7.c \
	AoC8/aoc8.c \
	AoC9/aoc9.c \
	AoC10/aoc10.c \
	AoC11/aoc11.c \
	AoC12/aoc12.c \
	-o aoc
