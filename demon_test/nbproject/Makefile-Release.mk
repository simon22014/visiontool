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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/3bb8e1a6/feaPoint.o \
	${OBJECTDIR}/_ext/3bb8e1a6/template.o \
	${OBJECTDIR}/_ext/3bb8e1a6/templateMatching.o \
	${OBJECTDIR}/_ext/3bb8e1a6/theClass.o \
	${OBJECTDIR}/ChangeGray.o \
	${OBJECTDIR}/ChangeGrayClass.o \
	${OBJECTDIR}/GeroetryMouse.o \
	${OBJECTDIR}/callPython.o \
	${OBJECTDIR}/cornerDetection.o \
	${OBJECTDIR}/cornerDetectionClass.o \
	${OBJECTDIR}/demarcate.o \
	${OBJECTDIR}/histImage.o \
	${OBJECTDIR}/histImageClass.o \
	${OBJECTDIR}/histImageOperate.o \
	${OBJECTDIR}/imageFindCorner.o \
	${OBJECTDIR}/imageFindCornerClass.o \
	${OBJECTDIR}/imageFindLine.o \
	${OBJECTDIR}/imageFindLineClass.o \
	${OBJECTDIR}/imageGeroetry.o \
	${OBJECTDIR}/imageNoiseClass.o \
	${OBJECTDIR}/imageSamplingClass.o \
	${OBJECTDIR}/imageSmoothness.o \
	${OBJECTDIR}/imagedealwith.o \
	${OBJECTDIR}/imagedealwithclass.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/marginFunctor.o \
	${OBJECTDIR}/marginFunctorClass.o \
	${OBJECTDIR}/marginGeometryClass.o \
	${OBJECTDIR}/marginShapeClass.o \
	${OBJECTDIR}/pthreadLock.o \
	${OBJECTDIR}/showAndWebStorageClass.o \
	${OBJECTDIR}/showStorageClass.o \
	${OBJECTDIR}/webStructClass.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/demon_test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/demon_test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/demon_test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/3bb8e1a6/feaPoint.o: /home/aqq/NetBeansProjects/demon_test/feaPoint.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3bb8e1a6
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3bb8e1a6/feaPoint.o /home/aqq/NetBeansProjects/demon_test/feaPoint.cpp

${OBJECTDIR}/_ext/3bb8e1a6/template.o: /home/aqq/NetBeansProjects/demon_test/template.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3bb8e1a6
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3bb8e1a6/template.o /home/aqq/NetBeansProjects/demon_test/template.cpp

${OBJECTDIR}/_ext/3bb8e1a6/templateMatching.o: /home/aqq/NetBeansProjects/demon_test/templateMatching.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3bb8e1a6
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3bb8e1a6/templateMatching.o /home/aqq/NetBeansProjects/demon_test/templateMatching.cpp

${OBJECTDIR}/_ext/3bb8e1a6/theClass.o: /home/aqq/NetBeansProjects/demon_test/theClass.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3bb8e1a6
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3bb8e1a6/theClass.o /home/aqq/NetBeansProjects/demon_test/theClass.cpp

${OBJECTDIR}/ChangeGray.o: ChangeGray.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ChangeGray.o ChangeGray.cpp

${OBJECTDIR}/ChangeGrayClass.o: ChangeGrayClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ChangeGrayClass.o ChangeGrayClass.cpp

${OBJECTDIR}/GeroetryMouse.o: GeroetryMouse.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GeroetryMouse.o GeroetryMouse.cpp

${OBJECTDIR}/callPython.o: callPython.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/callPython.o callPython.cpp

${OBJECTDIR}/cornerDetection.o: cornerDetection.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cornerDetection.o cornerDetection.cpp

${OBJECTDIR}/cornerDetectionClass.o: cornerDetectionClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cornerDetectionClass.o cornerDetectionClass.cpp

${OBJECTDIR}/demarcate.o: demarcate.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/demarcate.o demarcate.cpp

${OBJECTDIR}/histImage.o: histImage.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/histImage.o histImage.cpp

${OBJECTDIR}/histImageClass.o: histImageClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/histImageClass.o histImageClass.cpp

${OBJECTDIR}/histImageOperate.o: histImageOperate.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/histImageOperate.o histImageOperate.cpp

${OBJECTDIR}/imageFindCorner.o: imageFindCorner.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageFindCorner.o imageFindCorner.cpp

${OBJECTDIR}/imageFindCornerClass.o: imageFindCornerClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageFindCornerClass.o imageFindCornerClass.cpp

${OBJECTDIR}/imageFindLine.o: imageFindLine.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageFindLine.o imageFindLine.cpp

${OBJECTDIR}/imageFindLineClass.o: imageFindLineClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageFindLineClass.o imageFindLineClass.cpp

${OBJECTDIR}/imageGeroetry.o: imageGeroetry.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageGeroetry.o imageGeroetry.cpp

${OBJECTDIR}/imageNoiseClass.o: imageNoiseClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageNoiseClass.o imageNoiseClass.cpp

${OBJECTDIR}/imageSamplingClass.o: imageSamplingClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageSamplingClass.o imageSamplingClass.cpp

${OBJECTDIR}/imageSmoothness.o: imageSmoothness.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageSmoothness.o imageSmoothness.cpp

${OBJECTDIR}/imagedealwith.o: imagedealwith.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imagedealwith.o imagedealwith.cpp

${OBJECTDIR}/imagedealwithclass.o: imagedealwithclass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imagedealwithclass.o imagedealwithclass.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/marginFunctor.o: marginFunctor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/marginFunctor.o marginFunctor.cpp

${OBJECTDIR}/marginFunctorClass.o: marginFunctorClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/marginFunctorClass.o marginFunctorClass.cpp

${OBJECTDIR}/marginGeometryClass.o: marginGeometryClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/marginGeometryClass.o marginGeometryClass.cpp

${OBJECTDIR}/marginShapeClass.o: marginShapeClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/marginShapeClass.o marginShapeClass.cpp

${OBJECTDIR}/pthreadLock.o: pthreadLock.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pthreadLock.o pthreadLock.cpp

${OBJECTDIR}/showAndWebStorageClass.o: showAndWebStorageClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/showAndWebStorageClass.o showAndWebStorageClass.cpp

${OBJECTDIR}/showStorageClass.o: showStorageClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/showStorageClass.o showStorageClass.cpp

${OBJECTDIR}/webStructClass.o: webStructClass.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/webStructClass.o webStructClass.cpp

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
