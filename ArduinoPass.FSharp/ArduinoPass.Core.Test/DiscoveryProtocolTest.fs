module ArduinoPass.Core.Test.DiscoveryProtocolTest

open ArduinoPass.Core.Test.Devices
open Microsoft.VisualStudio.TestTools.UnitTesting
open ArduinoPass.Core.DiscoveryProtocol
open ArduinoPass.Core.Device

[<TestClass>]
type DiscoveryProtocolTest () =
    
    [<TestMethod>]
    member this.TestConnectionFailure () =
        (discover (seq { (ConnectionFailure() :> IConnectable) })).IsNone |> Assert.IsTrue

    [<TestMethod>]
    member this.TestHandshakeFailure () =
        (discover (seq { (InvalidHandshake() :> IConnectable) })).IsNone |> Assert.IsTrue
        
    [<TestMethod>]
    member this.TestNoDevices () =
        (discover (Seq.empty)).IsNone |> Assert.IsTrue
        
    [<TestMethod>]
    member this.TestSuccessfulHandshake () =
        (discover (seq { (ValidHandshake() :> IConnectable) })).IsSome |> Assert.IsTrue