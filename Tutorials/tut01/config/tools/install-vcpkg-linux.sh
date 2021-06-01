#!/bin/bash

set -e

if [[ ! -d ./vcpkg ]]; then
	git clone https://github.com/Microsoft/vcpkg.git
fi

cd vcpkg
git pull
./bootstrap-vcpkg.sh -disableMetrics
cp /mnt/c/Users/pizza/CLionProjects/COMP6771-Advanced-CPP/Tutorials/tut01/config/cmake/triplets/* triplets/community/.
./vcpkg update
./vcpkg install --clean-after-build abseil
./vcpkg install --clean-after-build benchmark
./vcpkg install --clean-after-build catch2
./vcpkg install --clean-after-build fmt
./vcpkg install --clean-after-build gsl-lite
./vcpkg install --clean-after-build range-v3
cd ..

FILE=/mnt/c/Users/pizza/ClionProjects/COMP6771-Advanced-CPP/Tutorials/tut01/vcpkg
if test -f "$FILE"; then
  sudo rm -rf $FILE
fi
sudo cp -R vcpkg /mnt/c/Users/pizza/ClionProjects/COMP6771-Advanced-CPP/Tutorials/tut01/
echo "all done"
sed -i 's#/import/kamen/1/cs6771#${workspaceFolder}#' /mnt/c/Users/pizza/CLionProjects/COMP6771-Advanced-CPP/Tutorials/tut01/.vscode/cmake-kits.json
rm -rf vcpkg