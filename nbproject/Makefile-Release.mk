#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/c7c31eb5/Continent.o \
	${OBJECTDIR}/_ext/c7c31eb5/Map.o \
	${OBJECTDIR}/_ext/c7c31eb5/Player.o \
	${OBJECTDIR}/_ext/c7c31eb5/Territory.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/comp345_a1_v0_r00.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/comp345_a1_v0_r00.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/comp345_a1_v0_r00 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/c7c31eb5/Continent.o: /G/netbeans/COMP345_A1_v0_r00/Continent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7c31eb5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7c31eb5/Continent.o /G/netbeans/COMP345_A1_v0_r00/Continent.cpp

${OBJECTDIR}/_ext/c7c31eb5/Map.o: /G/netbeans/COMP345_A1_v0_r00/Map.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7c31eb5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7c31eb5/Map.o /G/netbeans/COMP345_A1_v0_r00/Map.cpp

${OBJECTDIR}/_ext/c7c31eb5/Player.o: /G/netbeans/COMP345_A1_v0_r00/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7c31eb5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7c31eb5/Player.o /G/netbeans/COMP345_A1_v0_r00/Player.cpp

${OBJECTDIR}/_ext/c7c31eb5/Territory.o: /G/netbeans/COMP345_A1_v0_r00/Territory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7c31eb5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7c31eb5/Territory.o /G/netbeans/COMP345_A1_v0_r00/Territory.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
