module ArduinoPass.Arduino

open System.IO.Ports
open ArduinoPass.Core.Device

type Arduino =
    val private serialPort: SerialPort

    new(portName: PortName) = {
        serialPort = new SerialPort(portName)
    }
    
    interface IDevice with
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
                    return this :> IDevice 
                }
                |> Async.RunSynchronously
                |> Ok
                
        member this.disconnect() =
            this.serialPort.Close()

        member this.receive() =
            this.serialPort.ReadLine().Trim()
        
        member this.send(message) =
            this.serialPort.Write(message)

        member this.identifier() =
            this.serialPort.PortName

let devices = SerialPort.GetPortNames()
                |> Seq.map Arduino
                |> Seq.map(fun arduino -> arduino :> IDevice)
