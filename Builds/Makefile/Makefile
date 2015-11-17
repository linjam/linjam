# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Release
endif

ifndef DESTDIR
  DESTDIR=
endif

ifndef PREFIX
  PREFIX=/usr
endif

INSTALLDIR=$(DESTDIR)$(PREFIX)

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.31.0" -D "JUCE_APP_VERSION_HEX=0x1f00" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3 `pkg-config ninjam --cflags` -Wall -Wextra $(if $(filter-out x86_64 , $(shell uname -m)) , -malign-double , -fPIC)
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -L/usr/X11R6/lib/ `pkg-config ninjam --libs` `pkg-config ninjam-client --libs`
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.31.0" -D "JUCE_APP_VERSION_HEX=0x1f00" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := linjam
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.31.0" -D "JUCE_APP_VERSION_HEX=0x1f00" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 `pkg-config ninjam --cflags` -Wall -Wextra $(if $(filter-out x86_64 , $(shell uname -m)) , -malign-double , -fPIC)
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -L/usr/X11R6/lib/ `pkg-config ninjam --libs` `pkg-config ninjam-client --libs`
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.31.0" -D "JUCE_APP_VERSION_HEX=0x1f00" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := linjam-dbg
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Debug32)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug32
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -m32
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.31.0" -D "JUCE_APP_VERSION_HEX=0x1f00" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 `pkg-config ninjam --cflags` -Wall -Wextra $(if $(filter-out x86_64 , $(shell uname -m)) , -malign-double , -fPIC)
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -L/usr/X11R6/lib/ `pkg-config ninjam --libs` `pkg-config ninjam-client --libs`
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.31.0" -D "JUCE_APP_VERSION_HEX=0x1f00" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := 
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/Background_ba4a3b7.o \
  $(OBJDIR)/Blacklist_42ebe7fe.o \
  $(OBJDIR)/Channel_14ad93e4.o \
  $(OBJDIR)/Channels_84b8f659.o \
  $(OBJDIR)/Chat_e7196be1.o \
  $(OBJDIR)/Config_5aed31cb.o \
  $(OBJDIR)/ConfigAudio_37708215.o \
  $(OBJDIR)/ConfigBlacklist_73aebedc.o \
  $(OBJDIR)/ConfigChannel_53548a42.o \
  $(OBJDIR)/ConfigClient_9ea4fbb6.o \
  $(OBJDIR)/ConfigGui_8149577a.o \
  $(OBJDIR)/Constants_e698e730.o \
  $(OBJDIR)/License_de20cc22.o \
  $(OBJDIR)/LinJam_a166dece.o \
  $(OBJDIR)/LinJamConfig_8af59670.o \
  $(OBJDIR)/Login_37b1de4a.o \
  $(OBJDIR)/Loop_17fb192d.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/MainContent_6313eee1.o \
  $(OBJDIR)/Mixer_d95e2aea.o \
  $(OBJDIR)/StatusBar_3fb23a2.o \
  $(OBJDIR)/Trace_fd3024bc.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking LinJam
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

install:
	@echo Installing LinJam
	@install -m 755 $(OUTDIR)/$(TARGET) $(INSTALLDIR)/bin/

uninstall:
	@echo Uninstalling LinJam
	@rm $(INSTALLDIR)/bin/$(TARGET) > /dev/null

clean:
	@echo Cleaning LinJam
	@$(CLEANCMD)

strip:
	@echo Stripping LinJam
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/Background_ba4a3b7.o: ../../Source/Background.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Background.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Blacklist_42ebe7fe.o: ../../Source/Blacklist.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Blacklist.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Channel_14ad93e4.o: ../../Source/Channel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Channel.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Channels_84b8f659.o: ../../Source/Channels.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Channels.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Chat_e7196be1.o: ../../Source/Chat.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Chat.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Config_5aed31cb.o: ../../Source/Config.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Config.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigAudio_37708215.o: ../../Source/ConfigAudio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigAudio.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigBlacklist_73aebedc.o: ../../Source/ConfigBlacklist.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigBlacklist.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigChannel_53548a42.o: ../../Source/ConfigChannel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigChannel.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigClient_9ea4fbb6.o: ../../Source/ConfigClient.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigClient.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigGui_8149577a.o: ../../Source/ConfigGui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigGui.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Constants_e698e730.o: ../../Source/Constants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Constants.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/License_de20cc22.o: ../../Source/License.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling License.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LinJam_a166dece.o: ../../Source/LinJam.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LinJam.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LinJamConfig_8af59670.o: ../../Source/LinJamConfig.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LinJamConfig.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Login_37b1de4a.o: ../../Source/Login.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Login.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Loop_17fb192d.o: ../../Source/Loop.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Loop.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainContent_6313eee1.o: ../../Source/MainContent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainContent.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Mixer_d95e2aea.o: ../../Source/Mixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Mixer.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StatusBar_3fb23a2.o: ../../Source/StatusBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StatusBar.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Trace_fd3024bc.o: ../../Source/Trace/Trace.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Trace.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp ($(CONFIG))"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
