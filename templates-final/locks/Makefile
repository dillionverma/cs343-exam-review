# Universal makefile for multiple C++ programs and a Java program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependences among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ searcher | searcherJava | phil ]

########## Variables ##########

CXX = u++										# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD		# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = spinlock.o							# object files forming 1st executable
EXEC1 = spinlock								# 1st executable name

OBJECTS2 = lock.o 								# object files forming 2nd executable
EXEC2 = lock									# 2nd executable name

OBJECTS3 = barrier.o 							# object files forming 3rd executable
EXEC3 = barrier									# 3rd executable name

OBJECTS4 = binarySemaphore.o 					# object files forming 4th executable
EXEC4 = binarySemaphore							# 4th executable name

OBJECTS5 = countingSemaphore.o 					# object files forming 4th executable
EXEC5 = countingSemaphore						# 4th executable name

OBJECTS = ${OBJECTS1} ${OBJECTS2} ${OBJECTS3} ${OBJECTS4} ${OBJECTS5}
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2} ${EXEC3} ${EXEC4}	${EXEC5}	# all executables

########## Targets ##########

.PHONY : all clean								# not file names

all : ${EXECS}									# build all executables

${EXEC1} : ${OBJECTS1}							# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@					# additional object files before $^

${EXEC2} : ${OBJECTS2}							# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@					# additional object files before $^

${EXEC3} : ${OBJECTS3}							# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@					# additional object files before $^

${EXEC4} : ${OBJECTS4}							# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@					# additional object files before $^

${EXEC5} : ${OBJECTS5}							# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@					# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}								# include *.d files containing program dependences

clean :											# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}