module ArduinoPass.Cli
    
open System
open ArduinoPass.Core.DiscoveryProtocol
open ArduinoPass.Arduino

[<EntryPoint>]
let main argv =
    match discover devices with
        | Some device -> Console.WriteLine $"Handshake was successful: {device.identifier()}"
        | None -> Console.WriteLine "No device found!"
    0 // return an integer exit code