# async-proxy

## build
On linux install boost with: `apt-get install libboost-all-dev`

`make clean`

`make`

## usage
```
./build/apps/remote-server <path-to-config>
./build/apps/proxy-server <path-to-config>
./build/apps/client <path-to-config>
```

# Example
config.toml
```
[server]
protocol = "tcp"
address = "127.0.0.1:3001"
[upstream]
address = "127.0.0.1:5001"
timeout = "10s"
```

Run Remote Server and Proxy Server in Background
```
./build/apps/remote-server config.toml &
./build/apps/proxy-server config.toml &
```

Copy Client File
```
cp ./build/apps/client ./build/apps/client1
cp ./build/apps/client ./build/apps/client2
```

Open New Terminal
```
./build/apps/client1 config.toml
```

Open Another Terminal
```
./build/apps/client2 config.toml
```

