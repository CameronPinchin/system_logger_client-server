CXX = g++
CXXFLAGS = -Wall -g -std=c++17

CLIENT_SRC = sys_logger.cc sys_logger_client.cc
SERVER_SRC = server.cc 

CLIENT_OBJ = $(CLIENT_SRC:.cc=.o)
SERVER_OBJ = $(SERVER_SRC:.cc=.o)

CLIENT_EXEC = sys_logger_client.exe
SERVER_EXEC = sys_logger_server.exe

all: $(CLIENT_EXEC) $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lws2_32

$(CLIENT_EXEC): sys_logger_client.o sys_logger.o
	$(CXX) $(CXXFLAGS) -o $@ sys_logger_client.o sys_logger.o -lws2_32 -mconsole

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	del /Q $(CLIENT_OBJ) $(SERVER_OBJ) $(CLIENT_EXEC) $(SERVER_EXEC)




