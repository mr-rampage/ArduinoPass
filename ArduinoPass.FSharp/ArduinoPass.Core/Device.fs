module ArduinoPass.Core.Device

type ConnectionString = string

type Greeting = string

type Acknowledgement = string

type IDisconnectable =
    abstract member disconnect: unit -> unit
    
type IVerifiedDevice =
    inherit IDisconnectable
    abstract member send: string -> unit 
    abstract member receive: unit -> string 

type IUnverfiedDevice =
    inherit IDisconnectable
    abstract member awaitAcknowledgement: Acknowledgement -> Result<IVerifiedDevice, string>

type IQueriableDevice=
    inherit IDisconnectable
    abstract member greet: Greeting -> IUnverfiedDevice 

type IConnectable =
    inherit IDisconnectable
    abstract member connect: unit -> Result<IQueriableDevice, string>
    
    abstract member identifier: unit -> ConnectionString