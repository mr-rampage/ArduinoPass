module ArduinoPass.Core.ConnectionProtocol

open ArduinoPass.Core.Device
let private HANDSHAKE_GREET = "CONNECT"
let private HANDSHAKE_ACK = "OK"

let private sendHandshake (device: IDevice) =
    device.send(HANDSHAKE_GREET)
    Ok device

let private awaitAcknowledgement (device: IDevice) =
    try 
        let response = device.receive()
        if response.Equals HANDSHAKE_ACK
            then Ok device
            else Error "No acknowledgement"
    with
    | e -> Error e.Message
        
let private tee sideEffect = fun x ->
    sideEffect()
    x

let private discoveryProtocol (device: IDevice) =
    device.connect()
        |> Result.bind sendHandshake
        |> Result.bind awaitAcknowledgement
        |> tee device.disconnect
        
let discover (devices: seq<IDevice>) : Option<IDevice> =
    devices
    |> Seq.tryFind(fun device ->
            match discoveryProtocol device with
            | Ok _ -> true
            | Error _ -> false
        )
