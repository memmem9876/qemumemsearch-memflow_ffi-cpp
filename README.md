# ubuntu 23.10.1

# qemu install

....

## cargo 1.74.1

sudo apt install curl

curl https://sh.rustup.rs -sSf | sh

1

source "$HOME/.cargo/env"


## libmemflow_win32.so libmemflow_qemu.so
## gcc 13.2 g++ 13.2

sudo apt install gcc

sudo apt install g++

sudo apt install git


## memflow 0.2.0-beta11

cd ~

mkdir memwork

sudo mkdir /usr/local/lib/memflow

cd memwork

git clone https://github.com/memflow/memflow-qemu.git

cd memflow-qemu

cargo build --release --all-features

sudo cp target/release/libmemflow_qemu.so /usr/local/lib/memflow/libmemflow_qemu.so

cd ..

git clone https://github.com/memflow/memflow-win32.git

cd memflow-win32

cargo build --release --all-features

sudo cp target/release/libmemflow_win32.so /usr/local/lib/memflow/libmemflow_win32.so

cd ..

# memflow_ffi

git clone https://github.com/memflow/memflow.git

cd memflow

cargo build --release --all-features --workspace

cd ..


# qemumemsearch-memflow_ffi-cpp

git clone https://github.com/memmem9876/qemumemsearch-memflow_ffi-cpp.git

cp ./memflow/target/release/libmemflow_ffi.a ./qemumemsearch-memflow_ffi-cpp/lib/libmemflow_ffi.a

cp ./memflow/memflow-ffi/memflow.hpp ./qemumemsearch-memflow_ffi-cpp/include/memflow.hpp

cd qemumemsearch-memflow_ffi-cpp

make

sudo ./main.out


