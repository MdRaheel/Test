#!/bin/bash
#
#Build script by Mohammed Raheel
#
export red=$(tput setaf 1)            
export grn=$(tput setaf 2)             
export blu=$(tput setaf 4)             
export cya=$(tput setaf 6)             
export txtbld=$(tput bold)             
export bldred=${txtbld}$(tput setaf 1) 
export bldgrn=${txtbld}$(tput setaf 2) 
export bldblu=${txtbld}$(tput setaf 4) 
export bldcya=${txtbld}$(tput setaf 6) 

echo "${bldcya}***** Clean up Environment before compile *****${txtrst}";
echo
read -t 5 -p "Make clean source, 5sec timeout (y/n)?";
if [ "$REPLY" == "y" ]; then
./cleanup.sh;
fi;
           
echo
echo "${bldgrn}***** Preparing configuration *****${txtrst}"
echo
export ARCH=arm
export CROSS_COMPILE=/home/raheel/Desktop/Toolchain/Ubertc4.9/bin/arm-eabi-
#export CROSS_COMPILE=/home/raheel/Desktop/Toolchain/HyperX4.9/bin/arm-eabi-
mkdir compiled_files
make -C $(pwd) O=compiled_files msm8916_sec_defconfig VARIANT_DEFCONFIG=msm8916_sec_j53g_eur_defconfig SELINUX_DEFCONFIG=selinux_defconfig

read -t 5 -p "Do you want to use menu configuration?, 5sec timeout (y/n)?";
if [ "$REPLY" == "y" ]; then
make menuconfig;
fi;

echo
echo "${bldgrn}***** Compiling kernel started *****${txtrst}"
make -j12 -C $(pwd) O=compiled_files
cp compiled_files/arch/arm/boot/Image $(pwd)/arch/arm/boot/zImage

echo
echo "${bldgrn}***** Building dt.img *****${txtrst}"
./tools/dtbTool -s 2048 -o ./$BK/$TARGET/dt.img -p ./scripts/dtc/ ./arch/arm/boot/dts/ -v
echo "Kernel is compiled" 

START_TIME=`date +%s`
END_TIME=`date +%s`
let "ELAPSED_TIME=($END_TIME-$START_TIME)/60"
echo "Total compile time is $ELAPSED_TIME minutes"


