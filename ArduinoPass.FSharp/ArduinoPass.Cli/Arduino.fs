module ArduinoPass.Arduino

open System.IO.Ports
open ArduinoPass.Core.Device

type Arduino =
    val private serialPort: SerialPort

    new(portName: ConnectionString) = {
        serialPort = new SerialPort(portName)
    }

    interface IDisconnectable with
        member this.disconnect() =
            this.serialPort.Close()

    interface IConnectable with
        member this.connect() =
            if this.serialPort.IsOpen
            then
                Error "Serial port is busy"
            else
                async {
                    this.serialPort.DtrEnable <- true
                    this.serialPort.ReadTimeout <- 1500
                    this.serialPort.Open()
                    do! Async.Sleep 250
                    return this :> IQueriableDevice
                }
                |> Async.RunSynchronously
                |> Ok

        member this.identifier() =
            this.serialPort.PortName

    interface IQueriableDevice with                
        member this.greet(greeting) =
            this.serialPort.WriteLine(greeting)
            this :> IUnverfiedDevice

    interface IUnverfiedDevice with
        member this.awaitAcknowledgement(acknowledgement) =
            let response = this.serialPort.ReadLine().Trim()
            if response.Equals acknowledgement
                then Ok (this :> IVerifiedDevice)
                else Error "Invalid handshake"

    interface IVerifiedDevice with 
        member this.send message =
            this.serialPort.WriteLine(message)
        member this.receive() =
            this.serialPort.ReadLine().Trim()

let devices = SerialPort.GetPortNames()
                |> Seq.map Arduino
                |> Seq.map(fun arduino -> arduino :> IConnectable)
