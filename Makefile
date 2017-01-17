#version
MAJOR_VERSION=0
MINOR_VERSION=1
MICRO_VERSION=0
VERSION=$(MAJOR_VERSION).$(MINOR_VERSION).$(MICRO_VERSION)

BUILD       :=  build
SOURCES     :=  source
DATA        :=  data
INCLUDES    :=  include

#Target name
TARGET      :=  $(notdir $(CURDIR))

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES      :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES    :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))

# Object files
export OFILES   :=   $(addprefix $(BUILD)/,$(CPPFILES:.cpp=.o))         

                    
CPPFILES    :=   $(addprefix $(SOURCES)/,$(CPPFILES))


#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------


# Compiler
export LD   :=  $(CXX)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE  :=  $(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) \
                    -I$(CURDIR)/$(BUILD)
            
# Flags
CPPFLAGS=-Wall -g -W -pedantic -ansi -std=c++0x -lutil 

# Linking flags
LIBS    :=
LDFLAGS= $(LIBS)

$(BUILD)/%.o:$(SOURCES)/%.cpp
    @mkdir -p $(BUILD)
    @echo building $^ ...
    @$(LD) $(CPPFLAGS) -c $^ -o $@ $(INCLUDE)

main:$(OFILES)
    @mkdir -p $(BUILD)
    @echo linking ...
    @$(LD) $(OFILES) $(CPPFLAGS) $(LDFLAGS) -o $(TARGET)
    @echo "$(TARGET)-$(VERSION)"
    @$(MAKE)  tests

tests:
    @$(MAKE) -f $(DATA)/Makefile

# Cleanup
clean:
    @echo clean ...
    @rm -rf $(BUILD)
    @rm -f $(TARGET)
    @$(MAKE) clean -f $(DATA)/Makefile 

install:
    @sudo mkdir -p /opt/$(TARGET)
    @sudo cp -Rf data /opt/$(TARGET)/
    @sudo cp -f $(TARGET) /opt/$(TARGET)/$(TARGET)
    @sudo ln -sf /opt/$(TARGET)/$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
    @sudo rm -rf /opt/$(TARGET)
    @sudo rm -f /usr/local/bin/$(TARGET)