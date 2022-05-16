platform="unknown"
unameis=$(uname)

if [ $unameis = "Darwin" ]; then
    platform="mac"
elif [ $unameis = "Linux" ]; then
    platform="linux"
fi

sudo ./setup/setup.sh $platform
