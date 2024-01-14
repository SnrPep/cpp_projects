cmake_minimum_required(VERSION 3.25)
project(APolishTranslator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(APolishTranslator
        APolishTranslator.cpp
        APolishTranslator.h
        ASmb.cpp
        ASmb.h
        AStack.cpp
        AStack.h
        main.cpp A2TreeTranslator.h
        A2TreeTranslator.cpp
        NewBinTree.h
)
