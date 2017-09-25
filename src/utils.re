external register_service_worker : unit => unit = "default" [@@bs.module "./registerServiceWorker"];

let textEl str => ReasonReact.stringToElement str;

