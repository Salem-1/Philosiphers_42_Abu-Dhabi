#!/bin/bash

make re
echo "./philo 1 800 200 200"
sleep 3
./philo 1 800 200 200
echo "---------------------------------"
#sleep  3
echo "shouldn't eat , die\n"
echo ""
echo ""
echo "#################################"
sleep 5
echo "./philo  5 800 200 200"
sleep 3
./philo 5 800 200 200
echo "---------------------------------"
echo "Nobody should die\n"
echo ""
echo ""
echo "#################################"
sleep 5
echo "./philo 4 410 200 200"
sleep 3
./philo 4 410 200 200
echo "---------------------------------"
echo "No one should die\n"
#sleep 5
echo ""
echo ""
echo "#################################"
sleep  5
echo "./philo 4 310 200 100"
sleep 3
./philo 4 310 200 100
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
