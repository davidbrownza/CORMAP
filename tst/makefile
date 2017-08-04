OBJS = test.cpp Model.o Field.o IntegerField.o FloatField.o CharField.o TextField.o BooleanField.o DBConnection.o
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -std=c++11 -Wall $(DEBUG)

test : $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o test -lmysqlcppconn

DBConnection.o : ../src/conn/DBConnection.h ../src/conn/DBConnection.cpp 
	$(CXX) $(CFLAGS) ../src/conn/DBConnection.cpp

Model.o : ../src/model/Model.h ../src/model/Model.cpp ../src/conn/DBConnection.h ../src/fields/IntegerField.h ../src/fields/FloatField.h ../src/fields/CharField.h ../src/fields/TextField.h ../src/fields/BooleanField.h
	$(CXX) $(CFLAGS) ../src/model/Model.cpp

IntegerField.o : ../src/fields/IntegerField.h ../src/fields/IntegerField.cpp ../src/fields/Field.h
	$(CXX) $(CFLAGS) ../src/fields/IntegerField.cpp

FloatField.o : ../src/fields/FloatField.h ../src/fields/FloatField.cpp ../src/fields/Field.h
	$(CXX) $(CFLAGS) ../src/fields/FloatField.cpp

CharField.o : ../src/fields/CharField.h ../src/fields/CharField.cpp ../src/fields/Field.h
	$(CXX) $(CFLAGS) ../src/fields/CharField.cpp

TextField.o : ../src/fields/TextField.h ../src/fields/TextField.cpp ../src/fields/Field.h
	$(CXX) $(CFLAGS) ../src/fields/TextField.cpp

BooleanField.o : ../src/fields/BooleanField.h ../src/fields/BooleanField.cpp ../src/fields/Field.h
	$(CXX) $(CFLAGS) ../src/fields/BooleanField.cpp

Field.o : ../src/fields/Field.h ../src/fields/Field.cpp
	$(CXX) $(CFLAGS) ../src/fields/Field.cpp

clean:
	\rm *.o test
