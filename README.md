# Dogecoin Integration Setup

## Project Structure

1. Place the `.cpp` and `.h` files under the `Dogecoin` folder in your Unreal Engine project.
2. The files located in the `RPDHandler` folder should be run separately from the game client for operations.

## Dogecoin Node

You will need to host a Dogecoin node on your computer or point to an external node in the source.

### Windows Node Configuration

For Windows, the configuration file is located under:
C:\Users\somecooldude\AppData\Roaming\Dogecoin\


Use the following configuration for testnet:

```config
testnet=1
server=1
rpcuser=pooperdinkles
rpcpassword=pooperdinkles
rpcallowip=127.0.0.1
rpcport=18332
