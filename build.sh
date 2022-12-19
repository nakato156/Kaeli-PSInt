which cmake > nul
if [[ $? -eq 0 ]]
then
    if [ -d "build" ] 
    then
        rm -r "build"
    fi
    mkdir build
    cmake -B build
    cmake --build build
else
    echo No se pudo encontrar cmake.
fi