
export DISPLAY=:1
cd /code/cartridge
make clean && make
cd /code/firmware
make clean && make 

if [ "$1" -eq 0 ]; then
    # 当第一个参数为0时执行
    /code/runsim.sh
elif [ "$1" -eq 1 ]; then
    # 当第一个参数为1时执行
    /code/runsim.sh -d
else
    # 处理其他情况，可以根据实际需求添加逻辑
    echo "Invalid argument. Please provide 0 or 1 as the first argument."
fi