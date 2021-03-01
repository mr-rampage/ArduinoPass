module ArduinoPass.Cli
    
open System
open ArduinoPass.Core.DiscoveryProtocol
open ArduinoPass.Arduino

[<EntryPoint>]
let main argv =
    match discover devices with
        | Some connection -> Console.WriteLine $"Handshake was successful: {connection.identifier()}"
        | None -> Console.WriteLine "No device found!"
    0 // return an integer exit code