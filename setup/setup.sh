# ensure libpcap is installed
PACKAGE = libpcap
if [ '$1' == 'mac' ]; then
  brew install libpcap 
elif [ '$1' == 'linux' ]; then
  APT_CMD = $(which apt-get)    # Debian based distro
  PACMAN_CMD = $(which pacman)  # Arch based distro
  YUM_CMD = $(which yum)        # Red Hat based distro
  ZYPPER_CMD = $(which zypper)  # OpenSuse based distro
  PORTAGE_CMD = $(which emerge) # Gentoo based distro


  if [ ! -z $APT_CMD ]; then
    apt install -y libpcap
  elif [ ! -z $PACMAN_CMD ]; then
    pacman -Sy libpcap --noconfirm
  elif [ ! -z $YUM_CMD ]; then
    yum -y install libpcap
  elif [ ! -z $ZYPPER_CMD ]; then
    zypper --non-interactive install libpcap
  elif [ ! -z $PORTAGE_CMD ]; then
    emerge net-libs/libpcap
  else
    echo "Error installing $PACKAGE. Package manager not supported in setup script, you are on your own! :D"
    exit 1
  fi
else
  echo "OS not supported in setup script yet."
  exit 2
fi

exit 0
