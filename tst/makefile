OBJS = test.cpp Model.o DBConnection.o
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

test : $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o test -lmysqlcppconn

DBConnection.o : ../src/conn/DBConnection.h ../src/conn/DBConnection.cpp 
	$(CXX) $(CFLAGS) ../src/conn/DBConnection.cpp

Model.o : ../src/model/Model.h ../src/model/Model.cpp ../src/conn/DBConnection.h ../src/fields/Field.h
	$(CXX) $(CFLAGS) ../src/model/Model.cpp

clean:
	\rm *.o test
