# Netlog (Old) - Network Traffic Logger

Netlog is a high-performance network packet logger written in modern C++ (C++17). This legacy version focuses on capturing live or recorded network traffic and streaming it in real time to external systems like Apache Kafka or to a remote machine using raw packets.

> ✅ This is the old version of Netlog. For the new (fixed) version, refer to [`Netlog-new`](https://github.com/NetLog-IDS/netlog-new).

---

## ✨ Features

- Capture packets from a network interface or PCAP file
- Filter captured packets using Berkeley Packet Filter (BPF) syntax
- Convert packet data to JSON
- Stream data in real-time to:
  - **Apache Kafka** via `librdkafka`
  - **Network host** via `libtins` (raw packet sender)

---

## 🚀 Usage

### Run with Live Network Interface

```bash
sudo ./build/bin/spoofy \
  -i <INTERFACE> \
  -f <FILTER> \
  --live \
  --sender kafka \
  --broker <BROKER_HOST>:<PORT> \
  --topic <TOPIC>
```

### Example:

```bash
sudo ./build/bin/spoofy \
  -i lo \
  -f 'tcp or udp' \
  --live \
  --sender kafka \
  --broker localhost:19092 \
  --topic network-traffic
```

### Run with PCAP File

```bash
sudo ./build/bin/spoofy \
  -i ./path/to/file.pcap \
  -f <FILTER> \
  --sender kafka \
  --broker <BROKER_HOST>:<PORT> \
  --topic <TOPIC>
```

### Example:

```bash
sudo ./build/bin/spoofy \
  -i ./utils/pcap/dos_first_100k.pcap \
  -f 'tcp or udp' \
  --sender kafka \
  --broker localhost:19092 \
  --topic network-traffic
```

## 🐳 Run with Docker

### Build the Docker image

```bash
docker build -t <USERNAME>/netlog-old .
```

### Run the Docker image

```bash
sudo docker run \
  -d \
  -it \
  --rm \
  --name netlog \
  --hostname netlog \
  --network host \
  --entrypoint bash \
  <USERNAME>/netlog-old:latest \
  -c "/usr/local/bin/spoofy \
      -i lo \
      --live \
      -f 'tcp or udp' \
      --sender kafka \
      --broker <IP_BROKER>:<PORT_BROKER> \
      --topic network-traffic"
```

## 🧾 Flag Definitions

| Flag       | Description                                          |
| ---------- | ---------------------------------------------------- |
| `-i`       | Interface name or PCAP file path                     |
| `-f`       | BPF filter expression (e.g., `'tcp or udp'`)         |
| `--live`   | Capture packets from a live network interface        |
| `--sender` | Output mode: `kafka` or `raw`                        |
| `--broker` | Kafka broker address (required if sender is `kafka`) |
| `--topic`  | Kafka topic name to send data to                     |

## 🛠️ Dependencies

- [libpcap](https://www.tcpdump.org/)
- [librdkafka](https://github.com/confluentinc/librdkafka)
- [cmake](https://cmake.org/)
- [libtins](https://github.com/mfontanini/libtins)
- [catch2](https://github.com/catchorg/Catch2)
- [cclap](https://github.com/adriancostin6/cclap)

## ⚙️ Build Instructions

Most of the dependencies are handled during the build process, but some may require prior preparation if not installed.
For this purpose, a configuration script is provided for both Windows and \*NIX based systems.
Do note the possibility of this script failing and requiring manual intervention depending on platform.
Covered ones are: Windows, MacOS, Linux (may fail depending on your package manager, see setup/setup.sh).

### Linux/macOS

```bash
git clone https://github.com/NetLog-IDS/netlog-old.git
cd netlog-old
./configure.sh
make debug
```

### Windows

In order to build on Windows, WinPcap or Npcap is required, along with the WinPcap development pack.
The configuration script tries to provide these using the chocolatey package manager by installing
WinPcap and fetching the development pack automatically.

```bash
git clone https://github.com/NetLog-IDS/netlog-old.git
cd netlog-old
configure.bat
make debug
```

If manually:

- Install WinPcap or Npcap (Npcap is recommended)
- Get [WinPcap developer pack](https://www.winpcap.org/devel.htm) and place it in the `spoofy\ext` folder.
- Run `make debug`
