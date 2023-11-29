# export DISPLAY=:1
cd /code/cartridge
make clean && make
cd /code/firmware
make clean && make 

if [ "$1" -eq 1 ]; then
    # 当第一个参数为1时执行
    /code/runsim.sh -d
else
    /code/runsim.sh
fi