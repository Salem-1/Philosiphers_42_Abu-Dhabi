#!/bin/bash

make re
echo "./philo 1 800 200 200"
./philo 1 800 200 200
valgrind ./philo 1 800 200 200
valgrind --tool=helgrind ./philo 1 800 200 200
echo "shouldn't eat , die\n"




valgrind --tool=helgrind ./philo 4 410 200 200
echo "No one should die\n"

valgrind --tool=helgrind ./philo 4 310 200 100
philosipher should die

valgrind --tool=helgrind ./philo 3 1000 500 600 
philosopher should die

valgrind --tool=helgrind ./philo 5 200 100 60
philosopher should die

valgrind --tool=helgrind ./philo 4 500 400 300
a philosipher should die

valgrind --tool=helgrind ./philo 3 700 200 200
all live

 
a philosipher should die	
echo "---------------------------------"
#sleep  3
echo ""
echo ""
echo "#################################"
sleep 5
echo "./philo  5 800 200 200"
sleep 3
echo ""
echo ""
echo "#################################"
sleep 5
echo "./philo 4 410 200 200"
sleep 3

echo "---------------------------------"

#sleep 5
echo ""
echo ""
echo "#################################"
sleep  5
echo "./philo 4 310 200 100"
sleep 3

echo "---------------------------------"
#sleep  3
echo "A philosipher should die\n"
echo ""
echo ""
echo "#################################"
sleep 5
./philo
echo "---------------------------------"
#sleep  3
echo "shouldn't eat , die"
#sleep 5
echo ""
echo ""
echo "#################################"
##sleep 5
./philo
echo "---------------------------------"
#sleep  3
echo "shouldn't eat , die"
echo ""
echo ""
echo "#################################"
##sleep 5
./philo
echo "---------------------------------"
#sleep  3
echo "shouldn't eat , die"
echo ""
echo ""
echo "#################################"
##sleep 5
./philo
echo "---------------------------------"
##sleep   3
echo "shouldn't eat , die"
echo ""
echo ""
echo "#################################"
