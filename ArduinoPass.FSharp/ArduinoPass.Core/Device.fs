module ArduinoPass.Core.Device

type ConnectionString = string

type IConnection =
    abstract member identifier: unit -> string
    abstract member disconnect: unit -> unit
    abstract member send: string -> unit 
    abstract member receive: unit -> string 

type IConnectable =
    abstract member connect: unit -> Result<IConnection, string>