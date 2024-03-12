PROJECT_ROOT_DIR=$(pwd)

mkdir -p $PROJECT_ROOT_DIR/build

cd $PROJECT_ROOT_DIR/build

cmake ..

make -j$(nproc)

cd $PROJECT_ROOT_DIR

echo "Build finished successfully."