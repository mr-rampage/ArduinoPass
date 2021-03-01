module ArduinoPass.Core.Test.Devices

open ArduinoPass.Core.Device

type ConnectionFailure () =
    
    interface IConnectable with
        member this.connect() =
            Error "Connection failure"

type InvalidHandshake () =
    
    interface IConnectable with
        member this.connect() =
            Ok (this :> IConnection)
            
    interface IConnection with
        member this.identifier() = failwith "todo"
        member this.disconnect() =
            ()
        member this.receive() =
            "Invalid Handshake"
        member this.send _ =
            ()
            
type ValidHandshake () =
    
    interface IConnectable with
        member this.connect() =
            Ok (this :> IConnection)
            
    interface IConnection with
        member this.identifier() = failwith "todo"
        member this.disconnect() =
            ()
        member this.receive() =
            "OK"
        member this.send _ =
            ()