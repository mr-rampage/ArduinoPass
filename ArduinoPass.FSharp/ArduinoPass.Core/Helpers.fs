module ArduinoPass.Core.Helpers

let isOk result =
    match result with
    | Ok _ -> true
    | Error _ -> false

let toOption result =
    match result with
    | Ok x -> Some x
    | Error _ -> None

