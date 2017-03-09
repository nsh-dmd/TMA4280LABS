CC=mpicc
CFLAGS = -std=c99 -O2 -Wall -g
LDFLAGS=
LNKLIBS= -lm

MPIRUN =mpirun
NPROCS?=1

EXE=exe
EXESRC=main.c
EXEOBJ=$(patsubst %.c, %.o, $(EXESRC))
CLEAN_FILES+=$(EXE) $(EXEOBJ)

LIB=libutil.a
LIBSRC=util.c zeta/zeta1.c utest.c vtest.c reduc/recur.c reduc/allreduce.c zeta/zeta0.c mach/mach0.c mach/mach1.c 
LIBHEADER=util.h zeta/zeta0.h mach/mach0.h
LIBOBJ=$(patsubst %.c, %.o, $(LIBSRC))
CLEAN_FILES+=$(LIB) $(LIBOBJ)

CLEAN_FILES+= utest utest.o
CLEAN_FILES+= vtest vtest.o

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the library
$(LIB): $(LIBOBJ)
	@echo "LIB $@"
	@ar r $@ $^

all:	$(EXE) utest vtest zeta1 recur allreduce

# Program
$(EXE):	$(EXEOBJ) $(LIB)
	@echo "EXE $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LNKLIBS)

run:	$(EXE)
	$(MPIRUN) -n $(NPROCS) ./$< $(X) $(N)

# Unit test
utest:	utest.o $(LIB)
	@echo "EXE $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LNKLIBS)
	./$@

# Verification test
vtest:	vtest.o $(LIB)
	@echo "EXE $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LNKLIBS)
	./$@

# MPI zeta
zeta1:	zeta/zeta1.o $(LIB)
	@echo "EXE $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LNKLIBS)
	./$@

# Recursive doubling sum
recur:	reduc/recur.o $(LIB)
	@echo "EXE $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LNKLIBS)
	./$@

# Allreduce
allreduce: reduc/allreduce.o $(LIB)
	@echo "EXE $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LNKLIBS)
	./$@


clean:
	rm -f $(CLEAN_FILES)
