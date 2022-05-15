#!/bin/sh
# ensure libpcap is installed
package=libpcap
if [ $1 = "mac" ]; then
  brew install libpcap 
elif [ $1 = "linux" ]; then
  apt_cmd=$(which apt-get)    # Debian based distro
  pacman_cmd=$(which pacman)  # Arch based distro
  yum_cmd=$(which yum)        # Red Hat based distro
  zypper_cmd=$(which zypper)  # OpenSuse based distro
  portage_cmd=$(which emerge) # Gentoo based distro

  if [ ! -z $apt_cmd ]; then
    sudo apt install -y libpcap
  elif [ ! -z $pacman_cmd ]; then
    sudo pacman -Sy libpcap --noconfirm
  elif [ ! -z $yum_cmd ]; then
    sudo yum -y install libpcap
  elif [ ! -z $zypper_cmd ]; then
    sudo zypper --non-interactive install libpcap
  elif [ ! -z $portage_cmd ]; then
    sudo emerge net-libs/libpcap
  else
    echo "Error installing $package. Package manager not supported in setup script, you are on your own! Ending build..."
    exit 1
  fi
else
  echo "OS not supported in setup script. Ending build..."
  exit 2
fi

exit 0
