CXX = g++
DFLAG = -g
CXXFLAGS = $(DFLAG) -c
RM = rm -f

all: GameInstance

GameInstance: GameInstance.o InputWatcher.o ScoreRecorder.o Renderer.o ConsoleRenderer.o DotMatrixRenderer.o \
		Game.o Pong.o Entity.o Ball.o Paddle.o
	$(CXX) $(DFLAG) GameInstance.o InputWatcher.o ScoreRecorder.o Renderer.o ConsoleRenderer.o DotMatrixRenderer.o \
		Game.o Pong.o Entity.o Ball.o Paddle.o -o GameInstance -pthread

GameInstance.o: src/GameInstance.cpp
	$(CXX) $(CXXFLAGS) src/GameInstance.cpp

InputWatcher.o: src/InputWatcher.cpp src/InputWatcher.h
	$(CXX) $(CXXFLAGS) src/InputWatcher.cpp

ScoreRecorder.o: src/ScoreRecorder.cpp src/ScoreRecorder.h
	$(CXX) $(CXXFLAGS) src/ScoreRecorder.cpp

Renderer.o: src/renderer/Renderer.cpp src/renderer/Renderer.h
	$(CXX) $(CXXFLAGS) src/renderer/Renderer.cpp

ConsoleRenderer.o: src/renderer/ConsoleRenderer.cpp src/renderer/ConsoleRenderer.h
	$(CXX) $(CXXFLAGS) src/renderer/ConsoleRenderer.cpp

DotMatrixRenderer.o: src/renderer/DotMatrixRenderer.cpp src/renderer/DotMatrixRenderer.h
	$(CXX) $(CXXFLAGS) src/renderer/DotMatrixRenderer.cpp

Game.o: src/Game.cpp src/Game.h
	$(CXX) $(CXXFLAGS) src/Game.cpp

Pong.o: src/pong/Pong.cpp src/pong/Pong.h
	$(CXX) $(CXXFLAGS) src/pong/Pong.cpp

Entity.o: src/Entity.cpp src/Entity.h
	$(CXX) $(CXXFLAGS) src/Entity.cpp

Ball.o: src/pong/Ball.cpp src/pong/Ball.h
	$(CXX) $(CXXFLAGS) src/pong/Ball.cpp

Paddle.o: src/pong/Paddle.cpp src/pong/Paddle.h
	$(CXX) $(CXXFLAGS) src/pong/Paddle.cpp


clean:
	$(RM) *.o GameInstance
