@echo off

SET /p file=Nom du fichier a compiler (sans extension)? &;


:while
rm %file%.exe

fpc %file%.pas -Fu"C:/Dev-Pas/units/rtl"

rm %file%.o
%file%.exe

SET /p again=Again ? &;

if %again% == y (goto :while)
