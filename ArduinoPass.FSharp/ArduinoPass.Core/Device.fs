module ArduinoPass.Core.Device

type PortName = string
    
type IDevice =
    abstract member connect: unit -> Result<IDevice, string>
    abstract member disconnect: unit -> unit
    abstract member send: string -> unit
    abstract member receive: unit -> string
    abstract member identifier: unit -> string

