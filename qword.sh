#!/bin/bash
# Build and install echfs-utils (used to build the root fs image)
cd host/echfs-utils
make
# This will install echfs-utils in /usr/local
sudo make install
# Else specify a PREFIX variable if you want to install it elsewhere
#make PREFIX=<myprefix> install
# Now build the toolchain (this step will take a while)
cd ../toolchain
# You can replace the 4 in -j4 with your number of cores + 1
./make_toolchain.sh -j4
# Go back to the root of the tree
cd ../..
# Build the ports distribution
cd root/src
./makeworld.sh -j4
./makeworld.sh clean
# Now to build qword itself
cd ../..
# You might need to use gmake instead of make here on FreeBSD
make clean && make DEBUG=qemu img && sync
