root=$(which sudo)
root=$(which doas)

platform="unknown"
unameis=$(uname)

if [ $unameis = "Darwin" ]; then
    platform="mac"
elif [ $unameis = "Linux" ]; then
    platform="linux"
fi

$root ./setup/setup.sh $platform
