build:
	gcc-13 -fexec-charset=UTF-8 \
	main.c \
	common.c \
	AoC1/aoc1.c \
	AoC2/aoc2.c \
	AoC3/aoc3.c \
	AoC4/aoc4.c \
	AoC5/aoc5.c \
	AoC6/aoc6.c \
	AoC7/aoc7.c \
	-o aoc
