which cmake > nul
if [[ $? -eq 0 ]]
then
    mkdir build
    cmake -B build
    cmake --build build
else
    echo No se pudo encontrar cmake.
fi