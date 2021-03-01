module ArduinoPass.Core.Test.Devices

open ArduinoPass.Core.Device

type ConnectionFailure () =
    interface IConnectable with
        member this.connect() =
            Error "Connection failure"
            
        member this.identifier() = "Connection Failure"
        member this.disconnect() =
            ()

type InvalidHandshake () =
    interface IDisconnectable with
        member this.disconnect() =
            ()
    interface IConnectable with
        member this.connect() =
            Ok (this :> IQueriableDevice)
        member this.identifier() = "Invalid Handshake"
    interface IQueriableDevice with
        member this.greet(_) =
           (this :> IUnverfiedDevice)

    interface IUnverfiedDevice with
        member this.awaitAcknowledgement(_) =
            Error "Invalid Handshake"
            
type ValidHandshake () =
    interface IDisconnectable with
        member this.disconnect() =
            ()
    interface IConnectable with
        member this.connect() =
            Ok (this :> IQueriableDevice)

        member this.identifier() = "Valid Handshake"
    interface IQueriableDevice with
        member this.greet(_) =
           (this :> IUnverfiedDevice)

    interface IUnverfiedDevice with
        member this.awaitAcknowledgement(_) =
            Ok (this :> IVerifiedDevice)

    interface IVerifiedDevice with
        member this.send(_) = failwith "todo"
        member this.receive() = failwith "todo"