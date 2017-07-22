#!/bin/bash

g++ src/conn/DBConnection.cpp src/model/Model.cpp tst/test.cpp -o tst/test -lmysqlcppconn
