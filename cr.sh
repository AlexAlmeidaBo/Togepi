#!/bin/bash
echo "Compilando..."
gcc main.c -o main.exe -lfreeglut -lopengl32 -lglu32

if [ $? -ne 0 ]; then
  echo "Erro na compilação!"
  exit 1
fi

echo "Compilação bem-sucedida!"
echo "Executando..."
./main.exe
