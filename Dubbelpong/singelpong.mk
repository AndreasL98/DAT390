##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=singelpong
ConfigurationName      :=Debug
WorkspacePath          :=/Users/andreasljung/Desktop/DAT390/Codelite_Labb/ny_labb2_23/ny_labb2_23
ProjectPath            :=/Users/andreasljung/Desktop/DAT390/Codelite_Labb/singelpong
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Andreas Ljung
Date                   :=04/03/2023
CodeLitePath           :="/Users/andreasljung/Library/Application Support/CodeLite"
LinkerName             :=$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-gcc
SharedObjectLinkerName :=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi-g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="singelpong.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostdlib -nostartfiles
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc 
ArLibs                 :=  "gcc" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-ar rcu
CXX      := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++
CC       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-gcc
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
ARM_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp
ARM_GCC_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp
ARM_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/softfp
ARM_GCC_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/softfp
ARM_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/hard
ARM_GCC_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/hard
Objects0=$(IntermediateDirectory)/player_points.c$(ObjectSuffix) $(IntermediateDirectory)/game_logic.c$(ObjectSuffix) $(IntermediateDirectory)/ascii.c$(ObjectSuffix) $(IntermediateDirectory)/delay.c$(ObjectSuffix) $(IntermediateDirectory)/startup.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	/Applications/codelite.app/Contents/SharedSupport//tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  Debug/singelpong Debug/singelpong.s19
	/Applications/codelite.app/Contents/SharedSupport//tools/gcc-arm/bin/arm-none-eabi-objdump -D -S Debug/singelpong > Debug/singelpong.lst
	@echo Done

MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/player_points.c$(ObjectSuffix): player_points.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/player_points.c$(ObjectSuffix) -MF$(IntermediateDirectory)/player_points.c$(DependSuffix) -MM player_points.c
	$(CC) $(SourceSwitch) "/Users/andreasljung/Desktop/DAT390/Codelite_Labb/singelpong/player_points.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/player_points.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/player_points.c$(PreprocessSuffix): player_points.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/player_points.c$(PreprocessSuffix) player_points.c

$(IntermediateDirectory)/game_logic.c$(ObjectSuffix): game_logic.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/game_logic.c$(ObjectSuffix) -MF$(IntermediateDirectory)/game_logic.c$(DependSuffix) -MM game_logic.c
	$(CC) $(SourceSwitch) "/Users/andreasljung/Desktop/DAT390/Codelite_Labb/singelpong/game_logic.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/game_logic.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/game_logic.c$(PreprocessSuffix): game_logic.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/game_logic.c$(PreprocessSuffix) game_logic.c

$(IntermediateDirectory)/ascii.c$(ObjectSuffix): ascii.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ascii.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ascii.c$(DependSuffix) -MM ascii.c
	$(CC) $(SourceSwitch) "/Users/andreasljung/Desktop/DAT390/Codelite_Labb/singelpong/ascii.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ascii.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ascii.c$(PreprocessSuffix): ascii.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ascii.c$(PreprocessSuffix) ascii.c

$(IntermediateDirectory)/delay.c$(ObjectSuffix): delay.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/delay.c$(ObjectSuffix) -MF$(IntermediateDirectory)/delay.c$(DependSuffix) -MM delay.c
	$(CC) $(SourceSwitch) "/Users/andreasljung/Desktop/DAT390/Codelite_Labb/singelpong/delay.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/delay.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/delay.c$(PreprocessSuffix): delay.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/delay.c$(PreprocessSuffix) delay.c

$(IntermediateDirectory)/startup.c$(ObjectSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup.c$(DependSuffix) -MM startup.c
	$(CC) $(SourceSwitch) "/Users/andreasljung/Desktop/DAT390/Codelite_Labb/singelpong/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup.c$(PreprocessSuffix) startup.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


