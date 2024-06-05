##############################################################################
# Program Name                                                               #
##############################################################################
BINARY=TicTacToe

##############################################################################
# Compiler Flags, Optimisation and Libraries                                 #
##############################################################################
CC=x86_64-w64-mingw32-g++
WRES=x86_64-w64-mingw32-windres
LIB=/usr/x86_64-w64-mingw32/lib/libgdiplus.a /usr/x86_64-w64-mingw32/lib/libgdi32.a
LIBOLD=-libgdiplus.a -libgdi32.a
OPT=-O0
DEPFLAGS=-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
FLAGS=-std=c++14 -Wall -m64 -fexceptions -g -c ${OPT} ${DEPFLAGS}
RESFLAGS=-J rc -O coff -i 
LINKFLAG=-municode

##############################################################################
# Folders                                                                    #
##############################################################################
SRCDIR=src
OBJDIR=.obj
DEPDIR=.dep
INCDIR=include
#COMPILED RESOURCES DIRECTORY EQUIVALENT TO OBJECTS
CRESDIR=.res
RESDIR=resources
##############################################################################
# Files                                                                      #
##############################################################################
SRCEXT=cpp
OBJEXT=o
DEPEXT=d
RESEXT=res
RCEXT=rc
PCH=${INCDIR}/precompiled.h
INC=-include ${PCH}
PCHG=${INCDIR}/precompiled.h.gch
RCFILES=${wildcard ${RESDIR}/*.rc}
RESFILES=${patsubst ${RESDIR}/%,${CRESDIR}/%, $(RCFILES:.${RCEXT}=.${RESEXT})}
SOURCES= ${wildcard ${SRCDIR}/*.cpp}
OBJECTS=${patsubst ${SRCDIR}/%,${OBJDIR}/%, $(SOURCES:.${SRCEXT}=.${OBJEXT})}
DEPFILES=${patsubst ${SRCDIR}/%,${DEPDIR}/%, $(SOURCES:.${SRCEXT}=.${DEPEXT})}

all: ${BINARY}

${BINARY}: ${OBJECTS} ${RESFILES}
	${CC} -o $@ $^ ${LINKFLAG} ${LIB}

${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${SRCEXT}
	${CC} ${FLAGS} -o $@ $<

${CRESDIR}/%.${RESEXT}: ${RESDIR}/%.${RCEXT}
	${WRES} ${RESFLAGS} $< -o $@

${PCHG}:${PCH}
	${CC} $^ ${FLAGS}

clean: 
	rm -rf ${OBJECTS} ${BINARY} ${DEPFILES} ${RESFILES}

run: ${BINARY}
	./${BINARY}

-include ${DEPFILES}

.PHONY: all clean run
