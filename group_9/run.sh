# export DISPLAY=:1
cd /code/group_9/baseline_cartridge
make clean && make

if [ "$1" -eq 1 ]; then
    # 当第一个参数为1时执行
    /code/runsim.sh -d
else
    /code/runsim.sh
fi