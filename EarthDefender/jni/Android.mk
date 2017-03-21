LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := earthdefender

LOCAL_SRC_FILES := main.cpp Game.cpp Textures.cpp MainMenu.cpp MenuView.cpp SimpleButton.cpp Conf.cpp Lang.cpp Sounds.cpp Map.cpp Path.cpp Tower.cpp Gestures.cpp Panel.cpp PanelManager.cpp Enemy.cpp Bullet.cpp GroundShadow.cpp Grass.cpp Animation.cpp Base.cpp AnimatedGround.cpp FloatingDamage.cpp Coil.cpp LightCannon.cpp Gatling.cpp RocketLauncher.cpp 

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
