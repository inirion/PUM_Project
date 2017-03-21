NDK_TOOLCHAIN_VERSION := 4.9
APP_PLATFORM := android-9
APP_STL := c++_shared

APP_CPPFLAGS += -std=c++11
APP_CPPFLAGS += -fexceptions
# all archs: armeabi armeabi-v7a x86 mips
# for faster build APP_ABI can take one eg. x86
#APP_ABI :=  armeabi armeabi-v7a x86 mips
APP_ABI :=  x86
APP_MODULES := sfml-activity earthdefender
