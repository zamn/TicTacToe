# T3 MakeFile
#
server.o : T3Server.cpp Socket.cpp ProtocolHandler.cpp GameManager.cpp Game.cpp \
	Player.cpp T3Choices.cpp
	g++ -g -Wall T3Server.cpp T3Choices.cpp Socket.cpp ProtocolHandler.cpp GameManager.cpp Game.cpp Player.cpp -lpthread -o server.o
