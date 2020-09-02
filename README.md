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
Run Remote Server and Proxy Server in Background
```
./build/apps/remote-server <path-to-config> &
./build/apps/proxy-server <path-to-config> &
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

