#!/bin/bash

echo "Compilando..."
gcc main.c -o main -lGL -lGLU -lglut -lm

if [ $? -ne 0 ]; then
  echo "Erro na compilação!"
  exit 1
fi

echo "Compilação bem-sucedida!"
echo "Executando..."
./main
