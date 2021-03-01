module ArduinoPass.Core.DiscoveryProtocol

open ArduinoPass.Core.Device
let private HANDSHAKE_GREET = "CONNECT"
let private HANDSHAKE_ACK = "OK"

let private sendHandshake (device: IQueriableDevice) =
    device.greet(HANDSHAKE_GREET)

let private awaitAcknowledgement (device: IUnverfiedDevice) =
    try 
        device.awaitAcknowledgement(HANDSHAKE_ACK)
    with
    | e -> Error e.Message
        
let private tee sideEffect = fun x ->
    sideEffect()
    x

let private discoveryProtocol (device: IConnectable) =
    device.connect()
        |> Result.map sendHandshake
        |> Result.bind awaitAcknowledgement
        |> tee device.disconnect
        
let discover (devices: seq<IConnectable>) : Option<IConnectable> =
    devices
    |> Seq.tryFind(fun device ->
            match discoveryProtocol device with
            | Ok _ -> true
            | Error _ -> false
        )
