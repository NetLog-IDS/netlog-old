# netlog - network traffic logger

A network packet logger written in C++ 17.

## Features

- capture network packets
- convert them to json strings
- stream network packet data in real time to
    - apache kafka (ksqldb) via librdkafka
    - network location via libtins packet sender

## Usage

### Streaming network packets to Apache kafka

```bash
sudo ./netlog -i INTERFACE -f FILTER --live --sender kafka --broker BROKER_NAME --topic TOPIC_NAME 
# Example
sudo ./netlog -i wlp3s0 --live --sender kafka --broker localhost:9092 --topic network-traffic 
```

### Streaming data using libtins PacketSender (work in progress)

```bash
sudo ./netlog -i INTERFACE -f FILTER --live --sender network
# Example
sudo ./netlog -i wlp3s0 --live --sender network
```

## Dependencies

- libpcap
- [cmake](https://cmake.org/)
- [libtins](https://github.com/mfontanini/libtins)
- [catch2](https://github.com/catchorg/Catch2)
- [cclap](https://github.com/adriancostin6/cclap)

## How-to

### Setup

Most of the dependencies are handled during the build process, but some may require prior preparation if not installed. 
For this purpose, a configuration script is provided for both Windows and *NIX based systems.
Do note the possibility of this script failing and requiring manual intervention depending on platform.
Covered ones are: Windows, MacOS, Linux (may fail depending on your package manager, see setup/setup.sh).

### Building the project

#### Linux, MacOs, other *nix based systems

```bash 
$ git clone https://github.com/adriancostin6/netlog.git
$ cd netlog
$ ./configure.sh 
$ make
```

#### Windows

In order to build on Windows, WinPcap or Npcap is required, along with the WinPcap development pack.
The configuration script tries to provide these using the chocolatey package manager by installing 
WinPcap and fetching the development pack automatically.

```bash 
$ git clone https://github.com/adriancostin6/netlog.git
$ cd netlog
$ configure.bat 
$ make
```

If you wish to install these manually, or don't have the chocolatey package manager and don't wish to bother
installing it, follow the steps below:

- Install WinPcap or Npcap (Npcap is recommended)
- Get [WinPcap developer pack](https://www.winpcap.org/devel.htm) and place it in the `spoofy\ext` folder.
- Run make, and pray.
