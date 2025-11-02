mkdir build && cd build

cmake ../ -DCMAKE_BUILD_TYPE=Release 
make -j8

# Run demo dataset
cd ~/KF-GINS
./bin/KF-GINS ./dataset/kf-gins.yaml

# Wait until the program finish