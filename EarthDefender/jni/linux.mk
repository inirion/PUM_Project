CC=g++
CFLAGS=-c -Wall -std=c++11 -D NONANDROID 
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio 
SOURCES=main.cpp Game.cpp Textures.cpp MainMenu.cpp MenuView.cpp SimpleButton.cpp Conf.cpp Lang.cpp Sounds.cpp Map.cpp Path.cpp Tower.cpp Gestures.cpp Panel.cpp PanelManager.cpp Enemy.cpp Bullet.cpp GroundShadow.cpp Grass.cpp Animation.cpp Base.cpp AnimatedGround.cpp Gatling.cpp LightCannon.cpp Coil.cpp RocketLauncher.cpp FloatingDamage.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=EarthDefender

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
