module ArduinoPass.Arduino

open System.IO.Ports
open ArduinoPass.Core.Device

type Arduino =
    val private serialPort: SerialPort

    new(portName: ConnectionString) = {
        serialPort = new SerialPort(portName)
    }
    
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
                    return this :> IConnection
                }
                |> Async.RunSynchronously
                |> Ok


    interface IConnection with
        member this.identifier() =
            this.serialPort.PortName
        member this.send message =
            this.serialPort.WriteLine(message)
        member this.receive() =
            this.serialPort.ReadLine().Trim()
        member this.disconnect() =
            this.serialPort.Close()

let devices = SerialPort.GetPortNames()
                |> Seq.map (Arduino)
                |> Seq.map (fun arduino -> arduino :> IConnectable)
