CXX = g++
CPPFLAGS += -fno-rtti -fno-exceptions -shared

GECKO_SDK_PATH = /home/alex/xulrunner-sdk

GECKO_CONFIG_INCLUDE = -include mozilla-config.h

GECKO_DEFINES  = -DXPCOM_GLUE -DXPCOM_GLUE_USE_NSPR

GECKO_INCLUDES = -I$(GECKO_SDK_PATH)/include -I$(GECKO_SDK_PATH)/sdk/include `pkg-config --cflags gtk+-2.0` `pkg-config --cflags unity`

GECKO_LDFLAGS =  -L$(GECKO_SDK_PATH)/lib -lxpcomglue_s -lxul -lxpcom -lplds4 -lplc4 -lnspr4 -lpthread -ldl `pkg-config --libs gtk+-2.0` -lunity

FILES = UnityProxy.cpp UnityProxyModule.cpp

TARGET = UnityProxy.so

build:
	$(GECKO_SDK_PATH)/bin/xpidl -m header -I$(GECKO_SDK_PATH)/idl IUnityProxy.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m typelib -I$(GECKO_SDK_PATH)/idl IUnityProxy.idl
	$(CXX) -Wall -O2 -o $(TARGET) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CPPFLAGS) $(CXXFLAGS) $(FILES) $(GECKO_LDFLAGS)
	chmod +x $(TARGET)
	strip $(TARGET)

clean:
	rm -f IUnityProxy.xpt
	rm -f IUnityProxy.h
	rm -f $(TARGET)
