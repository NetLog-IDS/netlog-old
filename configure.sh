platform="unknown"
unameis=$(uname)

if [ $unameis = "Darwin" ]; then
    platform="mac"
elif [ $unameis = "Linux" ]; then
    platform="linux"
fi

root=$(which sudo)
root=$(which doas)

"${root}" ./setup/setup.sh "$platform"
