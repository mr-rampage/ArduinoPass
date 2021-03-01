module ArduinoPass.Core.DiscoveryProtocol

open ArduinoPass.Core.Device
open ArduinoPass.Core.Helpers

let private HANDSHAKE_GREET = "CONNECT"
let private HANDSHAKE_ACK = "OK"

let private handshake(connection: IConnection) =
    try
        connection.send(HANDSHAKE_GREET)
        let response = connection.receive()
        if response.Equals HANDSHAKE_ACK
            then Ok connection
            else
                connection.disconnect()
                Error "Invalid handshake"
    with
    | e -> Error e.Message

let private tryConnectDevice (device: IConnectable) =
    device.connect() |> Result.bind handshake
        
let private isConnected = isOk

let private toConnection = toOption

let discover (devices: seq<IConnectable>) =
    devices
    |> Seq.map tryConnectDevice
    |> Seq.tryFind isConnected
    |> Option.bind toConnection