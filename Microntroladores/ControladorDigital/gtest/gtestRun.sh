# ceder permissão: chmod +x gtestRun.sh
for i in {1..30}
do
    echo ""
done

rm runTests
clear

#cmake -DVAR_TYPE=$1 CMakeLists.txt
cmake CMakeLists.txt
make

valgrind --leak-check=full ./runTests
