# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug
  TARGETDIR  = bin/Debug
  TARGET     = $(TARGETDIR)/raytracer
  DEFINES   += 
  INCLUDES  += -Iinclude -Iinclude/utils -I/usr/local/include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  PCH        = include/pch.hpp
  GCH        = $(OBJDIR)/pch.hpp.gch
  CPPFLAGS  += -I$(OBJDIR) -include $(OBJDIR)/pch.hpp
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g --std=c++11 -Wall
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -framework OpenGL -L/usr/local/lib
  LIBS      += -lSDL2 -lglew
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release
  TARGETDIR  = bin/Release
  TARGET     = $(TARGETDIR)/raytracer
  DEFINES   += 
  INCLUDES  += -Iinclude -Iinclude/utils -I/usr/local/include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  PCH        = include/pch.hpp
  GCH        = $(OBJDIR)/pch.hpp.gch
  CPPFLAGS  += -I$(OBJDIR) -include $(OBJDIR)/pch.hpp
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 --std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x -framework OpenGL -L/usr/local/lib
  LIBS      += -lSDL2 -lglew
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/App.o \
	$(OBJDIR)/Camera.o \
	$(OBJDIR)/Display.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Primitive.o \
	$(OBJDIR)/RayTracer.o \
	$(OBJDIR)/Scene.o \
	$(OBJDIR)/ShaderSrc.o \
	$(OBJDIR)/Shader.o \
	$(OBJDIR)/Surface.o \
	$(OBJDIR)/Texture.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking raytracer
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning raytracer
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/App.o: src/App.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Camera.o: src/Camera.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Display.o: src/Display.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main.o: src/main.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Primitive.o: src/Primitive.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RayTracer.o: src/RayTracer.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Scene.o: src/Scene.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ShaderSrc.o: src/ShaderSrc.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Shader.o: src/utils/Shader.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Surface.o: src/utils/Surface.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Texture.o: src/utils/Texture.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
