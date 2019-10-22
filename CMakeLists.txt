cmake_minimum_required(VERSION 3.15)
project(project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2 main.cpp deserializador.h serializador.h repositorio.h transaccion.h serializador_transaccion.h deserializador_transaccion.h)